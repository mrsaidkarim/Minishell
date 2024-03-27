#include "../included/minishell.h"

int	is_builting(char **cmd, t_var *var)
{
	if (!ft_strcmp("env", cmd[0]))
		ft_env(var);
	else if (!ft_strcmp("pwd", cmd[0]))
		ft_pwd(var);
	else if (!ft_strcmp("echo", cmd[0]))
		ft_echo(cmd, var);
	else if (!ft_strcmp("exit", cmd[0]))
		ft_exit(var, cmd);
	else if (!ft_strcmp("cd", cmd[0]))
		ft_cd(var, cmd);
	else if (!ft_strcmp("unset", cmd[0]))
		ft_unset(var, cmd);
	else if (!ft_strcmp("export", cmd[0]))
		ft_export(var, cmd);
	else
		return (0);
	return (1);
}

void	chdild_exec(char *path, char **cmd, t_var *var)
{
	pid_t	pid;
	int		status;
	char	**env;

	env = env_list_to_tab(var->env);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("faild to creat a child\n", 2);
		var->status = 1;
		free_matrix(env);
		return ;
	}
	if (pid == 0)
	{
		signal_midl_exec();
		execve(path, cmd, env);
		error_execve(path, errno);
	}
	waitpid(pid, &status, 0);
	var->status = update_status(status);
	free_matrix(env);
}

void	chdild_exec_2(char *path, char **cmd, t_var *var)
{
	pid_t	pid;
	int		status;
	char	**env;

	env = env_list_to_tab(var->env);
	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("faild to creat a child\n", 2);
		var->status = 1;
		free_matrix(env);
		return ;
	}
	if (pid == 0)
	{
		execve(path, cmd, env);
		error_execve(path, errno);
	}
	waitpid(pid, &status, 0);
	var->status = update_status(status);
	free_matrix(env);
}

void	exec_cmd(t_node *node, t_var *var)
{
	char	*path;

	if (handle_rederction(node, var) < 0)
	{
		return_in_out_fd(var);
		return ;
	}
	node->cmd = ft_expand(node->pre_cmd, var);
	if (node->cmd && node->cmd[0])
	{
		if (!is_builting(node->cmd, var))
		{
			path = get_path(node->cmd[0], var);
			if (!path)
			{
				if (!check_slach(node->cmd[0], var))
					chdild_exec_2(node->cmd[0], node->cmd, var);
				return_in_out_fd(var);
				return ;
			}
			else
			{
				chdild_exec(path, node->cmd, var);
				free(path);
			}
		}
	}
	return_in_out_fd(var);
}
