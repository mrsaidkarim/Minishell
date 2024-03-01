#include "../included/minishell.h"


t_token	check_tok(char *str)
{
	if (str[0] == '|' && str[1] == '|')
		return (TOKEN_OR);
	if (str[0] == '&' && str[1] == '&')
		return (TOKEN_AND);
	if (str[0] == '>' && str[1] == '>')
		return (TOKEN_REDIR_APPEND);
	if (str[0] == '<' && str[1] == '<')
		return (TOKEN_HEREDOC);
	if (str[0] == '|')
		return (TOKEN_PIPE);
	if (str[0] == ')')
		return (TOKEN_BRKT_CLOSE);
	if (str[0] == '(')
		return (TOKEN_BRKT_OPEN);
	if (str[0] == '"')
		return (TOKEN_D_Q);
	if (str[0] == '\'')
		return (TOKEN_S_Q);
	return (TOKEN_EXPR);
}
void	print_error_syntax(char *str, t_token tok)
{
	if (tok == TOKEN_OR || tok == TOKEN_AND)
		printf("bash: %s `%c%c'\n", UNEXPECTED_TOK, str[0], str[1]);
	else
		printf("bash: %s `%c'\n", UNEXPECTED_TOK, str[0]);
}
int	check_syntax(char *str)
{
	t_token tok;

	tok = check_tok(str);
	if (tok == TOKEN_PIPE || tok == TOKEN_OR
		|| tok == TOKEN_AND || tok == TOKEN_BRKT_CLOSE)
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