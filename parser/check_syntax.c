#include "../included/minishell.h"

/* Return the index of the closing bracket ')' in the string,
starting from the given index 'i'. */
int	ft_find_bclose(char *line, int i)
{
	while (*line)
	{
		if (*line == ')')
			return (i);
		i++;
		line++;
	}
	return (-1);
}

// Check the syntax combination and validate the string after a delimiter.
int	ft_check_syntax_combination(char *line, int *index, int *bclose, t_token tok)
{
	*index += ft_check_delim(line, *index);

	if (tok == BRKT_OPEN)
	{
		*bclose = ft_find_bclose(line + (*index), *index);
		if (*bclose == -1)
			return (ft_print_syntax_error("unclosed parentheses", NULL, -1));
	}
	else if (tok == BRKT_CLOSE)
	{
		if (*index - 1 > *bclose)
			return (ft_print_syntax_error("near unexpected token", ")", 1));
	}
	while (ft_isspace(line[*index]))
		(*index)++;
	if (tok == BRKT_CLOSE)
		return (0);
	if (ft_check_delim(line, *index)|| !line[*index])
	{
		if (ft_check_delim(line, *index))
			return (ft_print_syntax_error("near unexpected token", &line[*index], 1), -1);
		return (ft_print_syntax_error("near unexpected token `newline'", NULL, -1));
	}
	return (0);
}

/* Check and find the length of a word (file name or command)
 when it is enclosed in double or single quotes.*/
int	ft_protected_word(char *line, int *i, int *len, char c)
{
	(*i)++;
	(*len)++;
	while (line[*i])
	{
		if (line[*i] == c)
			return (1);
		(*i)++;
		(*len)++;
	}
	return (-1);
}
