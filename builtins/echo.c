#include "../included/minishell.h"

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
void	ft_echo(char **cmd, t_var *var)
{
	int	opt;
	int i;

	i = 0;
	opt = 0;
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
	var->status = 0;
}
