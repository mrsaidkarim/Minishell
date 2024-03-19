#include "../included/minishell.h"

void	ft_and(t_node *root, t_var *var)
{
	execution(root->lchild, var);
	if (!var->status)
		return (execution(root->rchild, var));
}

void	ft_or(t_node *root,t_var *var)
{
	execution(root->lchild, var);
	if (var->status)
		return (execution(root->rchild, var));
}

pid_t	child_write(t_node *node, int tab[2], t_var *var)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		close(tab[0]);
		dup2(tab[1], STDOUT_FILENO);
		close(tab[1]);
		execution(node,var);
		exit(var->status);
	}
	return(pid);
}

pid_t	child_read(t_node *node, int tab[2], t_var *var)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		close(tab[1]);
		dup2(tab[0], STDIN_FILENO);
		close(tab[0]);
		execution(node,var);
		exit(var->status);
	}
	return (pid);
}
void	ft_pipe(t_node *root,t_var *var)
{
	int		tab[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		status;

	if (pipe(tab) == -1)
	{
		printf("faild to creat pipe\n");
		var->status = 1;
		return ;
	}
	pid_1 = child_write(root->lchild, tab, var);
	pid_2 = child_read(root->rchild, tab, var);
	close(tab[1]);
	close(tab[0]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
	var->status = status;
}

void	execution(t_node *root, t_var *var)
{
	if (!root)
		return ;
	if (root->tok == AND)
		return (ft_and(root, var));
	else if (root->tok == OR)
		return (ft_or(root,var));
	else if (root->tok == PIPE)
		return (ft_pipe(root,var));
	else if (root->tok == EXPR)
		return (exec_cmd(root, var));
}