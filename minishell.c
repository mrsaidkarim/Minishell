#include "included/minishell.h"

int	g_signel = 0;

void	start_handle(char *input, t_node *root, t_var *g_var)
{
	// t_redir	*tmp;
	g_signel = 1;
	add_history(input);
	root = parsing(input, g_var);
	if (!root)
	{
		// if (g_var->error_herdoc)
		// {
		// 	tmp = g_var->error_herdoc;
		// 	while (tmp)
		// 	{
		// 		error_heredoc(tmp);
		// 		tmp = tmp->rchild;
		// 	}
		// }
		g_signel = 0;
        ft_free_red(g_var.error_herdoc);
        g_var.error_herdoc = NULL;
		return ;
	}
    ft_free_red(g_var.error_herdoc);
    g_var.error_herdoc = NULL;
	handle_herdoc(root, g_var);
	execution(root, g_var);
	g_signel = 0;
	return_in_out_fd(g_var);
	free_tree(root);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_var	g_var;
	t_node	*root;

	((void)ac, (void)av);
	initialization(&g_var, env);
	root = NULL;
	while (1)
	{
		ft_signal();
		input = readline("\033[1;32m->Prompt: \033[0m");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		start_handle(input, root, &g_var);
	}
	free_all(&g_var);
	return (0);
}
