#include "../included/minishell.h"


t_env	*ft_creat_env(char *env, char *var, char *content)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (!node)
		allocate_error(strerror(errno));
	node->env = ft_strdup(env);
	node->var = var;
	node->content = content;
	node->next = NULL;
	return (node);
}

void	ft_add_env(t_env **head, t_env *new)
{
	t_env *tmp;

	if (!head)
		return ;
	if (!(*head))
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}