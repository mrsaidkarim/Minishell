/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:27:53 by zelabbas          #+#    #+#             */
/*   Updated: 2024/03/30 00:27:54 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../included/minishell.h"

/* display the error if there's to many or non numeric arguments*/
void	errors_exit(char *str, int c)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("bash: exit: ", 2);
	if (c == 1)
		ft_putstr_fd("too many arguments\n", 2);
	if (c == 2)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
	}
}

// check  argument by argument if is digit 
int	is_digit(char **cmd)
{
	int	i;
	int	j;
	int	check;

	check = 0;
	i = 0;
	while (cmd[++i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '-')
				j++;
			if (!(cmd[i][j] >= '0' && cmd[i][j] <= '9'))
				return (0);
			j++;
		}
	}
	ft_atoll(cmd[1], &check);
	if (check != 0)
		return (0);
	return (1);
}

// calculate the nombre of argument
int	nbr_arg(char **av)
{
	int	i;

	i = 0;
	while (*av)
	{
		i++;
		av++;
	}
	return (i);
}

// is used to minimizing function ft_exit
void	handle_d_arg(t_var *var, char **cmd)
{
	int	nbr;

	nbr = nbr_arg(cmd);
	if (nbr == 1)
	{
		printf("exit\n");
		exit (0);
	}
	else if (nbr > 2 && is_digit(cmd))
	{
		errors_exit(cmd[1], 1);
		var->status = 1;
		return ;
	}
	else if (nbr == 2 && is_digit(cmd))
		exit (ft_atoll(cmd[1], &nbr));
	else
	{
		errors_exit(cmd[1], 2);
		exit(-1);
	}
}

// exit function 
void	ft_exit(t_var *var, char **cmd)
{
	handle_d_arg(var, cmd);
}
