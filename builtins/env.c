#include "../included/minishell.h"

void	ft_env(t_var *var)
{
	t_env *tmp;

	tmp = var->env;
	while (tmp)
	{
		printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
	var->status = 0;
}