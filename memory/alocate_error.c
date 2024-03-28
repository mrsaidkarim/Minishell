#include "../included/minishell.h"

void	allocate_error(char *str)
{
	ft_putstr_fd("bash : malloc: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
