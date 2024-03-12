#include "../included/minishell.h"

// Return the operand file's name or the command string based on the flag 'red'.
char	*ft_wordred(char *line, int i, char red)
{
	int		word_size;
	int		start;
	char	*str;

	word_size = 0;
	start = i;
	while (line[i] && check_tok(line + i) == EXPR && line[i] != red)
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (ft_protected_word(line, &i, &word_size, line[i]) == -1)
				return (ft_print_syntax_error("unclosed quotes", NULL, -1), NULL);
			word_size++;
			i++;
		}
		else
		{
			i++;
			word_size++;
		}
	}
	str = ft_substr(line, start, word_size);
	while (red == ' ' && start < i)
		line[start++] = 127;
	return (str);
}

/* main redirection function: check for errors syntax
and return redirection node; */
t_redir	*ft_create_red(char *line, int *i, t_token tok)
{
	char	*file_name;

	line[*i] = 127;
	(*i)++;
	if (tok == REDIR_APPEND || tok == HEREDOC)
		line[(*i)++] = 127;
	while (ft_isspace(line[*i]))
		line[(*i)++] = 127;
	if (!line[*i] || (check_tok(line + (*i)) != EXPR))
	{
		if (!line[*i])
			ft_print_syntax_error("near unexpected token `newline'", NULL, -1);
		else
			ft_print_syntax_error("near unexpected token", &line[*i], 2);
		return (NULL);
	}
	file_name = ft_wordred(line, *i, ' ');
	if (!file_name)
		return (NULL);
	return (ft_create_rednode(file_name, tok));
}

// prepare the node command and add it to the linked list
int	ft_prepare_cmd(char *line, int *i, t_node **head)
{
	int		j;
	char	*cmd;
	t_redir	*red;

	j = *i;
	red = NULL;
	while (line[*i] && !ft_skip_for_quotes(line, i))
	{
		if (check_tok(line + (*i)) != EXPR)
		{
			if (ft_add_red(&red, ft_create_red(line, i,
						check_tok(line + (*i)))) == -1)
				return (-1);
		}
		else
			(*i)++;
	}
	cmd = ft_wordred(line, j, '\0');
	if (!cmd)
		return (-1);
	if (ft_add_back(head, ft_create_cmd(cmd, ft_strlen(cmd), EXPR, red)) == -1)
		return (-1);
	return (1);
}

// Tokenizes the input line and builds a linked list of commands with associated tokens and redirections.
int	ft_build_cmds(char *line, t_node **head)
{
	int	i;
	int	last_brkt_close;
	int	prev_i;

	i = 0;
	last_brkt_close = 0;
	while (line[i])
	{
		prev_i = i;
		if (ft_check_delim(line, i))
		{
			if (ft_check_syntax_combination(line, &i, &last_brkt_close,
					check_tok(line + i)) == -1)
				return (-1);
			ft_add_back(head, ft_create_cmd(NULL, prev_i - i,
					check_tok(line + prev_i), NULL));
		}
		else
		{
			if (ft_prepare_cmd(line, &i, head) == -1)
				return (-1);
		}
	}
	return (0);
}

char	*parsing(char *input)
{
	t_node	*head;
	char	*str;
	t_token	tok;

	head = NULL;
	str = ft_clean_input(input);
	if (!ft_first_check(str))
		return (NULL);
	if (ft_build_cmds(str, &head) == -1)
		return (NULL);
	while (head)
	{
		printf("|%s|, red:", head->pre_cmd);
		while (head->redirections)
		{
			printf("%s|,", head->redirections->file);
			head->redirections = head->redirections->rchild;
		}
		printf("\n");
		head = head->rchild;
	}
	return (str);
}
