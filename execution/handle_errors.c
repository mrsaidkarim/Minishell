#include "../included/minishell.h"

int	check_pipe(int tab[2])
{
	if (pipe(tab) == -1)
	{
		ft_putstr_fd("bash: faild to creat the pipe!\n", 2);
		return (0);
	}
	return (1);
}

