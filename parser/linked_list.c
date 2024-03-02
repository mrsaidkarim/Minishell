#include "../included/minishell.h"

t_node	*ft_creat_node_cmd(char *str, t_token tok)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		allocate_error(strerror(errno));
	new->pre_cmd = str;
	new->cmd = NULL;
	new->cmd = tok;
	new->rchild = NULL;
	new->lchild = NULL;
	return (new);
}

void	ft_add_to_back(t_node **head, t_node *new)
{
	t_node	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->rchild)
			tmp->rchild;
		tmp->rchild = new;
		new->lchild = tmp;
	}
}