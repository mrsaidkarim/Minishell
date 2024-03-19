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