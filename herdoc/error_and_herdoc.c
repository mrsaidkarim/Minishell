#include "../included/minishell.h"

bool	error_start_herdoc(t_redir *node, int tab[2])
{
	char	*str;
	char	*input;

	input = readline("\033[1;31mheredoc> \033[0m");
	if (!input || !ft_strcmp(input, node->file))
	{
		free(input);
		return (true);
	}
	str = ft_strjoin(input, "\n");
	write(tab[1], str, ft_strlen(str));
	free(str);
	free(input);
	return (false);
}
void	error_heredoc(t_redir *node)
{
	int		tab[2];

	if (!check_pipe(tab))
		return ;
	node->file = expand_file(node->file);
	while (1)
	{
		if (error_start_herdoc(node, tab))
			break ;
	}
	close(tab[0]);
	close(tab[1]);
}