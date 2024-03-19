#include "../included/minishell.h"

int	is_digit(char **cmd)
{
	int	i;
	int j;

	i = 0;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (!(cmd[i][j] >= '0' && cmd[i][j] <= '9'))
				return (0);
			j++;
		}
	}
	
	return (1);
}

int	nbr_arg(char **av)
{
	int i;

	i = 0;
	while (*av)
	{
		i++;
		av++;
	}
	return (i);
}

void	handle_d_arg(t_var *var,char **cmd)
{
	int nbr;

	nbr = nbr_arg(cmd);
	if (nbr == 1)
	{
		printf("exit\n");
		exit (0);
	}
	else if (nbr > 2 && is_digit(cmd))
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: too many arguments\n", 2);
		var->status = 1;
		return ;
	}
	else if (nbr == 2 && is_digit(cmd))
		exit (ft_atoi(cmd[1]));
	else
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("bash: exit: numeric argument required\n", 2);
		exit(-1);
	}
}

void	ft_exit(t_var *var,char **cmd)
{
	handle_d_arg(var, cmd);
}