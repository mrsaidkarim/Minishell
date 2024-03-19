#include "../included/minishell.h"

int	is_valid(char c, int fisrt)
{
	if (fisrt == 1)
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
	else
		return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || c == '_');
}
int	check_var(char *str)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (str[i] && is_valid(str[i], 1))
	{
		i++;
		len++;
	}
	while (str[i] && is_valid(str[i], 0))
		i++;
	if (!len || (str[i] && !is_valid(str[i], 0)))
	{
		printf("bash: unset: `%s`: not a valid identifier\n", str);
		return (false);
	}
	return (true);
}

void	delete_node(t_var *var, t_env *node, int check)
{
	t_env	*tmp;

	if(!check)
	{
		tmp = var->env;
		var->env = var->env->next;
	}
	else
	{
		tmp = node->next;
		node->next = node->next->next;
	}
	printf("%s\n" , tmp->env);
	(free(tmp->env), free(tmp->var), free(tmp->content));
	(free(tmp), tmp = NULL);
}

void	ft_unset(t_var *var, char **cmd)
{
	char	**tmp;
	t_env	*list;
	int		check;
	t_env	*save = NULL;

	tmp = cmd;
	while (*++tmp)
	{
		if (!check_var(*tmp))
		{
			var->status = 1;
			continue ;
		}
		list = var->env;
		check = 0;
		while (list)
		{
			if (!ft_strcmp(list->var, *tmp))
			{
				delete_node(var, save, check);
				break;
			}
			save = list;
			list = list->next;
			check++;
		}
	}
}
