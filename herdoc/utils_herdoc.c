#include "../included/minishell.h"

bool	start_herdoc(t_redir *node, t_var *var, int tab[2])
{
	char	*str;
	char	*input;

	input = readline("\033[1;31mheredoc> \033[0m");
	if (!input || !ft_strcmp(input, node->file))
	{
		free(input);
		return (true);
	}
	if (node->flg)
		input = expand_herdoc(input, var);
	str = ft_strjoin(input, "\n");
	write(tab[1], str, ft_strlen(str));
	free(str);
	free(input);
	return (false);
}

int	ft_heredoc(t_redir *node, t_var *var)
{
	int		tab[2];
	int		save_fd;

	save_fd = -1;
	if (!check_pipe(tab))
		return (var->status = 1, -1);
	ft_check_expand(node->file, &node->flg);
	node->file = expand_file(node->file);
	if (!isatty(STDOUT_FILENO))
	{
		save_fd = dup(STDOUT_FILENO);
		dup2(var->fd_output, STDOUT_FILENO);
	}
	while (1)
	{
		if (start_herdoc(node, var, tab))
			break ;
	}
	if (save_fd != -1)
	{
		dup2(save_fd, STDOUT_FILENO);
		close(save_fd);
	}
	return (close(tab[1]), tab[0]);
}
