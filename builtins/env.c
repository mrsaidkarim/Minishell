#include "../included/minishell.h"

int	check_path(char **tab)
{
	int i;

	i = -1;
	while (tab[++i])
	{
		if (!ft_strcmp(tab[i], "/usr/bin"))
			return (1);
	}
	return (0);
}
void	ft_env(t_var *var)
{
	t_env	*tmp;
	char	**tab;

	tab = get_paths(var);
	if (!tab || !check_path(tab))
	{
		printf("bash: env: is a directory\n");
		if (tab)
			free_matrix(tab);
		return ;
	}
	tmp = var->env;
	while (tmp)
	{
		printf("%s\n", tmp->env);
		tmp = tmp->next;
	}
	free_matrix(tab);
	var->status = 0;
}
