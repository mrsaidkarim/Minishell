#include "../included/minishell.h"

int	is_builting(char **cmd, t_var *var)
{
	if (!ft_strcmp("env",cmd[0]))
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

char	**get_paths(t_var *var)
{
	t_env *tmp;

	tmp = var->env;
	while (tmp)
	{
		if (!ft_strcmp("PATH",tmp->var))
			return (ft_split(tmp->content, ':'));
		tmp = tmp->next;
	}
	return (NULL);
}
char	*get_path(char *cmd, t_var *var)
{
	char	**paths;
	char	*path;
	char	*part_path;
	int		i;

	if (cmd[0] == '/')
		return (ft_strdup(cmd));
	paths = get_paths(var);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		if (access(path, F_OK) == 0)
			return (free_matrix(paths), free(part_path) ,path);
		free(path);
		free(part_path);
	}
	return (free_matrix(paths), NULL);
}

int	ft_size_list(t_env *env)
{
	t_env	*tmp;
	int		size;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**env_list_to_tab(t_env *env)
{
	int		size;
	int 	i;
	t_env	*tmp;
	char	**tab;

	size = ft_size_list(env);
	tab = (char **)malloc(sizeof(char *) * (size + 1));
	if (!env)
		allocate_error("faild to allocate memory");
	i = 0;
	tmp = env;
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->env);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	error_execve(char *path, int error)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	if (error == ENOENT)
	{
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else if(error == EACCES)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		exit(126);
	}
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
		execve(path, cmd, env);
		error_execve(path, errno);
	}
	waitpid(pid, &status, 0);
	var->status = status >> 8;
	free_matrix(env);
	// var->status = WEXITSTATUS(status);
}

// void	redirct_output(t_redir *redirect, char c)
// {
// 	if (c == 'o')
// 	{
// 		dup2(redirect->fd, STDOUT_FILENO);
// 		close(redirect->fd);
// 	}
// 	else if (c == 'i')
// 	{
// 		dup2(redirect->fd, STDIN_FILENO);
// 		close(redirect->fd);
// 	}
// }

// int	_open_f(t_node *node, char c, t_var *var)
// {
// 	int fd;
// 	static int	keep;

// 	if (c != 'r')
// 	{
// 		if (node->redirection->tok == IN)
// 			fd = open(node->redirection->file, O_RDONLY);
// 		else if (node->redirection->tok == OUT)
// 			fd = open(node->redirection->file, O_CREAT | O_RDWR | O_TRUNC, 0664);
// 		if (fd < 0)
// 		{
// 			printf("faild to open the file!\n");
// 			var->status = 1;
// 			return (-1);
// 		}
// 		node->redirection->fd = fd;
// 		if (node->redirection->tok == OUT)
// 		{
// 			keep = dup(STDOUT_FILENO);
// 			redirct_output(node->redirection, 'o');
// 		}
// 		else if (node->redirection->tok == IN)
// 		{
// 			keep = dup(STDIN_FILENO);
// 			redirct_output(node->redirection, 'i');
// 		}
// 	}
// 	else
// 	{
// 		if (node->redirection->tok == OUT)
// 		{
// 			dup2(keep, STDOUT_FILENO);
// 			close(keep);
// 		}
// 		else if (node->redirection->tok == IN)
// 		{
// 			dup2(keep, STDIN_FILENO);
// 			close(keep);
// 		}
// 	}
// 	return (1);
// }
/////////////////////////////////////////////////////////////////////////////////////////

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
	// char	*input;
	int		save_fd;
	// char	*str;

	if (!check_pipe(tab))
		return (var->status = 1, -1);
	ft_start_with(node->file, &node->flg);
	node->file = expand_file(node->file);
	if (!isatty(STDOUT_FILENO))
	{
		save_fd = dup(STDOUT_FILENO);
		dup2(var->fd_output, STDOUT_FILENO);
	}
	while (1)
	{
		if (start_herdoc(node, var, tab))
			break;
		// if (!isatty(STDOUT_FILENO))
		// {
		// 	save_fd = dup(STDOUT_FILENO);
		// 	dup2(var->fd_output, STDOUT_FILENO);
		// }
		// input = readline("\033[1;31mheredoc> \033[0m");
		// if (!input || !ft_strcmp(input, node->file))
		// {
		// 	free(input);
		// 	break;
		// }
		// if (node->flg)
		// 	input = expand_herdoc(input, var);
		// str = ft_strjoin(input, "\n");
		// write(tab[1], str, ft_strlen(str));
		// free(str);
		// free(input);
	}
	dup2(save_fd, STDOUT_FILENO);
	return (close(tab[1]), tab[0]);
}

int open_file(char *path, int flag, mode_t mode)
{
	int fd;

	fd = open(path, flag, mode);
	if (fd == - 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(path, 2);
		if (errno == ENOENT)
			ft_putstr_fd(": No such file or directory\n", 2);
		if (errno == EACCES)
			ft_putstr_fd(": Permission denied\n", 2);
		return (-1);
	}
	return (fd);
}

int	handle_fd_in(t_node *node)
{
	t_redir	*tmp;
	int		fd_in;

	tmp = node->redirections;
	fd_in = 0;
	while (tmp)
	{
		if (tmp->tok == REDIR_IN)
		{
			if (fd_in)
				close(fd_in);
			tmp->file = expand_file(tmp->file); 
			// fd_in = open(tmp->file, O_RDONLY, 0644);
			fd_in = open_file(tmp->file, O_RDONLY, 0644);
			if (fd_in < 0)
				return (-1);
		}
		else if (tmp->tok == HEREDOC)
		{
			if (fd_in)
				close(fd_in);
			fd_in = tmp->fd;
		}
		tmp = tmp->rchild;
	}
	// node->fd[0] = fd_in;
	return (node->fd[0] = fd_in, 1);
}

int	handle_fd_out(t_node *node)
{
	t_redir	*tmp;
	int		fd_out;

	tmp = node->redirections;
	fd_out = 0;
	while (tmp)
	{
		if (tmp->tok == REDIR_OUT)
		{
			if (fd_out)
				close(fd_out);
			tmp->file = expand_file(tmp->file);
			fd_out = open_file(tmp->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		}
		else if (tmp->tok == REDIR_APPEND)
		{
			if (fd_out)
				close(fd_out);
			fd_out = open_file(tmp->file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		if (fd_out < 0)
			return (-1);
		tmp = tmp->rchild;
	}
	// node->fd[1] = fd_out;
	return (node->fd[1] = fd_out, 1);
}

int	handle_in_out_file(t_node *node, t_var *var)
{
	if (handle_fd_in(node) < 0)
		return (var->status = 1, -1);
	if (handle_fd_out(node) < 0)
		return (var->status = 1, -1);
	if (node->fd[0] != 0)
	{
		dup2(node->fd[0], STDIN_FILENO);
		close(node->fd[0]);
	}
	if (node->fd[1] != 0)
	{
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
	}
	return (1);
}


int	handle_rederction(t_node *node, t_var *var)
{
	t_redir	*tmp;

	if (node->redirections)
	{
		tmp = node->redirections;
		while (tmp)
		{
			if (tmp->tok == HEREDOC)
			{
				tmp->fd = ft_heredoc(tmp, var);
				if (tmp->fd == -1)
					return (var->status = 1, -1);
			}
			tmp = tmp->rchild;
		}
		if (handle_in_out_file(node, var) < 0)
			return (-1);
		// if (handle_fd_in(node) < 0)
		// 	return (var->status = 1, -1);
		// if (handle_fd_out(node) < 0)
		// 	return (var->status = 1, -1);
		// if (node->fd[0] != 0)
		// {
		// 	dup2(node->fd[0], STDIN_FILENO);
		// 	close(node->fd[0]);
		// }
		// if (node->fd[1] != 0)
		// {
		// 	dup2(node->fd[1], STDOUT_FILENO);
		// 	close(node->fd[1]);
		// }
	}
	return (1);
}

void	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	exec_cmd(t_node *node,t_var *var)
{
	char *path;

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
				error_cmd_not_found(node->cmd[0]);
				var->status = 127;
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
