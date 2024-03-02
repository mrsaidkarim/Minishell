#include "../included/minishell.h"

t_token	check_tok(char *str)
{
	if (str[0] == '|' && str[1] == '|')
		return (OR);
	if (str[0] == '&' && str[1] == '&')
		return (AND);
	if (str[0] == '>' && str[1] == '>')
		return (REDIR_APPEND);
	if (str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	if (str[0] == '|')
		return (PIPE);
	if (str[0] == ')')
		return (BRKT_CLOSE);
	if (str[0] == '(')
		return (BRKT_OPEN);
	if (str[0] == '>')
		return (REDIR_OUT);
	if (str[0] == '<')
		return (REDIR_IN);
	return (EXPR);
}
void	print_error_syntax(char *str, t_token tok)
{
	if (tok == OR || tok == AND)
		printf("bash: %s `%c%c'\n", UNEXPECTED_TOK, str[0], str[1]);
	else
		printf("bash: %s `%c'\n", UNEXPECTED_TOK, str[0]);
}

int	check_syntax(char *str)
{
	t_token tok;

	tok = check_tok(str);
	if (tok == PIPE || tok == OR
		|| tok == AND || tok == BRKT_CLOSE)
	{
		print_error_syntax(str, tok);
		return (0);
	}
	return (1);
}

char *parsing(char *input)
{
	char *str;
	t_token tok;

	str = function_one_space(input);
	if (!check_syntax(str))
		return (NULL);
	return (str);
}

int	ft_check_delim(char *str, int i)
{
	if (str[i] == '|' && str[i + 1] == '|')
		return (2);
	else if (str[i] == '&' && str[i + 1] == '&')
		return (2);
	else if (str[i] == '|')
		return (1);
	else
		return (0);
}

t_node	*init(char *line)
{
	int		index;
	t_node	*head;
	t_node	*tmp;
	int		len;

	index = 0;
	while (line[index])
	{
		if (ft_check_delim(line, index))
		{
			tmp = ft_create_cmd(line + index, ft_check_delim(line, index), check_tok(line + index));
			ft_add_back(&head, tmp);
			index += ft_check_delim(line, index);
		}
		else
		{
			len = index;
			while (line[len] && ft_check_delim(line, len) == 0)
				len++;
			tmp = ft_create_cmd(line + index, len, check_tok(line + index));
			ft_add_back(&head, tmp);
			index += len;
		}
	}
	return (head);
}
