#include "../included/minishell.h"
// should implement the echo with falg (-n)!!!

bool	option(char *str)
{
	if (!*str)
		return (false);
	if (*str == '-')
	{
		str++;
		while (*str && *str == 'n')
			str++;
	}
	if (*str)
			return (false);
	return (true);
}
void	ft_echo(char **cmd)
{
	int	opt = 0;
	int i = 0;

	while (cmd[++i] && option(cmd[i]))
		opt = 1;
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i++], 1);
		if (cmd[i])
			ft_putstr_fd(" ", 1);
	}
	if (!opt)
		ft_putstr_fd("\n", 1);
	// exit(0);
}