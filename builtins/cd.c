#include "../included/minishell.h"

char	*get_env(char *var_env)
{
    t_env *tmp;

    tmp = var->env;
    while (tmp)
    {
        if (!ft_strcmp(tmp->var, var_env))
			return (tmp->content);
		tmp = tmp->next;
    }
	return (NULL);
}

char	*get_path(char *var)
{
	char *path;

	path = get_env(var);
	if (!path)
	{
		ft_putstr_fd("bash: cd: HOME not set\n",2);
		// exit_status(1);
		return (NULL);
	}
	return (path);
}
void    ft_cd(char **cmd)
{
    char    *path;
    char    str[PATH_MAX];
    if (cmd[1])
        path = cmd[1];
    else
        path = get_path("HOME");
	if (!path)
		return ;
}