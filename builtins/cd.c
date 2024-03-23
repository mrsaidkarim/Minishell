#include "../included/minishell.h"

char	*ft_get_envvar(t_var var, char *env_var)
{
	t_env	*env;

	env = var.env;
	while (env)
	{
		if (!ft_strcmp(env->var, env_var))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	ft_oldpwd(t_env *env, char *oldpwd)
{
	char	*env_var;
	char	*tmp;

	if (!ft_env_search(env, "OLDPWD"))
		return (ft_env_replace(env, "OLDPWD", oldpwd));
	tmp = ft_strjoin("OLDPWD", "=");
	env_var = ft_strjoin(tmp, oldpwd);
	ft_add_env(&env, ft_creat_env(env_var, "OLDPWD", oldpwd));
	free(tmp);
	free(env);
	return (0);
}

void	ft(t_var *var, char *pwd, char *oldpwd)
{
	if (chdir(pwd) != 0)
	{
		printf("bash: cd: %s: %s", pwd, strerror(errno));
		return ;
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (ft_putstr_fd(strerror(errno), 2));
	if (ft_env_replace(ft_env_search(var->env, "PWD"), "PWD", pwd) || ft_oldpwd(var->env, oldpwd))
		ft_putstr_fd("Error updating environment variables\n", 2);
	free(pwd);
	free(oldpwd);
	return ;
}

void	ft_cd(t_var *var, char **cmd)
{
	char	*pwd;
	char	*oldpwd;

	if (!cmd[1])
	{
		pwd = ft_get_envvar(*var, "HOME");
		if (!pwd)
			return (ft_putstr_fd("HOME environment variable is not set", 2));
	}
	else
		pwd = cmd[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ft_putstr_fd(strerror(errno), 2));
	ft(var, pwd, oldpwd);
	// if (chdir(pwd) != 0)
	// {
	// 	printf("bash: cd: %s: %s", pwd, strerror(errno));
	// 	return ;
	// }
	// pwd = getcwd(NULL, 0);
	// if (!pwd)
	// 	return (ft_putstr_fd(strerror(errno), 2));
	// if (ft_env_replace(ft_env_search(var->env, "PWD"), "PWD", pwd) || ft_oldpwd(var->env, oldpwd))
	// 	ft_putstr_fd("Error updating environment variables\n", 2);
	// return;
}
