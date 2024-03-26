#include "../included/minishell.h"

void	free_matrix(char **tab)
{
	int i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

// free the double linked list of redirections.
void	ft_free_red(t_redir *reds)
{
	t_redir	*tmp;

	while (reds)
	{
		if (reds->file)
			free(reds->file);
		tmp = reds;
		reds = reds->rchild;
		free(tmp);
	}
}

// free the double linked list of commands.
void	ft_free(t_node **head)
{
	t_node	*tmp;
	t_node	*tmp_node;

	tmp = *head;
	while (tmp)
	{
		ft_free_red(tmp->redirections);
		if (tmp->pre_cmd)
			free(tmp->pre_cmd);
		tmp_node = tmp;
		tmp = tmp->rchild;
		free(tmp_node);
	}
	*head = NULL;
}

// free the tree that contain the commands.
void	freeTree(t_node *root)
{
	t_node	*tmp;

	if (root != NULL)
	{
		ft_free_red(root->redirections);
		if (root->pre_cmd)
			free(root->pre_cmd);
		if (root->cmd)
			free_matrix(root->cmd);
        tmp = root;
		freeTree(root->lchild);
		freeTree(root->rchild);
		free(tmp);
	}
}
