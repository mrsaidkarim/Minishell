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

// Searches for an environment variable by its key and returns a pointer to its node.
t_env	*ft_env_search(t_env *env, char *key)
{
	while (env)
	{
		if (!strcmp(env->var, key))
			return (env);
		env = env->next;
	}
	return (NULL);
}

// Replaces the value of an environment variable with a new value.
int	ft_env_replace(t_env *env, char *key, char *value)
{
    char    *new_env;
    char    *tmp;

	if (!env)
		return (-1);
    tmp = ft_strjoin(key, "=");
    new_env = ft_strjoin(tmp, value);
    free(tmp);
    free(env->content);
    free(env->env);
    env->env = new_env;
	env->content = ft_strdup(value);
	return (0);
}
