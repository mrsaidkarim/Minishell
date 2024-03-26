#include "../included/minishell.h"

// Print a syntax error message.
int	ft_print_syntax_error(char *msg, char *c, int count)
{
	int	i;

	i = -1;
	if (!c)
	{
		ft_putstr_fd("bash: syntax error ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd("bash: syntax error ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(" `", 2);
		while (++i < count && (c[i] == '&' || c[i] == '|' || c[i] == '>' || c[i] == '<'))
			write(1, &c[i], 1);
		ft_putstr_fd("'\n", 2);
	}
	return (-1);
}

/* Trim leading and trailing spaces from the input string and
condense consecutive spaces to a single space. */
char	*ft_clean_input(char *str)
{
	char	*result;

	result = ft_strtrim(str, " \t");
	free(str);
	return (result);
}

// Check the validity of the starting token in the input string.
int	ft_first_check(char *str)
{
	t_token	tok;

	tok = check_tok(str);
	if (tok == PIPE || tok == OR
		|| tok == AND || tok == BRKT_CLOSE)
	{
		if (tok == PIPE || tok == BRKT_CLOSE)
			ft_print_syntax_error("near unexpected token", str, 1);
		else
			ft_print_syntax_error("near unexpected token", str, 2);
		free(str);
		return (0);
	}
	return (1);
}
