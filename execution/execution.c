#include "../included/minishell.h"

void	ft_and(t_node *root, t_var *var)
{
	execution(root->lchild, var);
	if (!var->status)
		return (execution(root->rchild, var));
}

void	ft_or(t_node *root, t_var *var)
{
	execution(root->lchild, var);
	if (var->status)
		return (execution(root->rchild, var));
}

pid_t	child_write(t_node *node, int tab[2], t_var *var)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("bash: faild to creat child\n", 2);
		return (var->status = 1, -1);
	}
	if (pid == 0)
	{
		close(tab[0]);
		dup2(tab[1], STDOUT_FILENO);
		close(tab[1]);
		execution(node, var);
		exit(var->status);
	}
	return (pid);
}

pid_t	child_read(t_node *node, int tab[2], t_var *var)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("bash: faild to creat child\n", 2);
		return (var->status = 1, -1);
	}
	if (pid == 0)
	{
		close(tab[1]);
		dup2(tab[0], STDIN_FILENO);
		close(tab[0]);
		execution(node, var);
		exit(var->status);
	}
	return (pid);
}

void	ft_pipe(t_node *root, t_var *var)
{
	int		tab[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		status;

	if (!check_pipe(tab))
	{
		var->status = 1;
		return ;
	}
	pid_1 = child_write(root->lchild, tab, var);
	if (pid_1 < 0)
		return ;
	pid_2 = child_read(root->rchild, tab, var);
	if (pid_2 < 0)
		return ;
	close(tab[1]);
	close(tab[0]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
	var->status = update_status(status);
}

void	execution(t_node *root, t_var *var)
{
	if (!root)
		return ;
	if (root->tok == AND)
		return (ft_and(root, var));
	else if (root->tok == OR)
		return (ft_or(root, var));
	else if (root->tok == PIPE)
		return (ft_pipe(root, var));
	else if (root->tok == EXPR)
		return (exec_cmd(root, var));
}
