#include "../included/minishell.h"

void	return_in_out_fd(t_var *var)
{
	dup2(var->fd_input, STDIN_FILENO);
	dup2(var->fd_output, STDOUT_FILENO);
}

void	init_g_var(t_var *var)
{
	var->env = NULL;
	var->status = 0;
	var->fd_input = dup(STDIN_FILENO);
	var->fd_output = dup(STDOUT_FILENO);
}

int	find_char(char *env, char c)
{
	int i;

	i = -1;
	while (env[++i])
	{
		if (env[i] == c)
			return (i);
	}
	return (-1);
}

void	initialization(t_var *var,char **env)
{
	int	i;

	if (!env || !(*env))
		return(printf("there's no env !"), exit(0));
	// var->env = malloc(sizeof(t_env));
	// if (!var->env)
	// 	(write(2, "Error: Allocation failed\n", 25), exit(1));
	init_g_var(var);
	while (*env)
	{
		i = find_char(*env, '=');
		ft_add_env(&var->env, ft_creat_env(*env, ft_substr(*env, 0, i), ft_strdup(*env + i + 1)));
		env++;
	}
}