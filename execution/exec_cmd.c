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
	ft_putstr_fd(" :", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	if (error == ENOENT)
		exit(127);
	if (error == EACCES)
		exit(126);
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
	// var->status = WEXITSTATUS(status);
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
	// var->status = WEXITSTATUS(status);
}


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
			break;
	}
	if (save_fd != -1)
	{
		dup2(save_fd, STDOUT_FILENO);
		close(save_fd);
	}
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
			fd_in = open_file(tmp->file, O_RDONLY, 0644);
		}
		else if (tmp->tok == HEREDOC)
		{
			if (fd_in)
				close(fd_in);
			fd_in = tmp->fd;
		}
		if (fd_in < 0)
				return (-1);
		tmp = tmp->rchild;
	}
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
	if (node->redirections)
	{
		if (handle_in_out_file(node, var) < 0)
			return (-1);
	}
	return (1);
}

void	error_cmd_not_found(char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}


int	check_slach(char *s, t_var *var)
{
	if (find_char(s, '/') == -1)
	{
		error_cmd_not_found(s);
		var->status = 127;
		return (1);
	}
	return (0);
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
