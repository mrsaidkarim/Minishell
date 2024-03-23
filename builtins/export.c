#include "../included/minishell.h"

t_env *copy(t_var *var)
{
	t_env *tmp;
	t_env  *list_env;

	list_env = NULL;
	tmp = var->env;
	while (tmp)
	{
		ft_add_env(&list_env, ft_creat_env(tmp->env, ft_strdup(tmp->var), ft_strdup(tmp->content)));
		tmp = tmp->next;
	}
	return (list_env);
}

void	ft_switch(t_env *trav, t_env *env)
{
	char	*str;

	str = env->env;
	env->env = trav->env;
	trav->env = str;
	str = env->var;
	env->var = trav->var;
	trav->var = str;
	str = env->content;
	env->content = trav->content;
	trav->content = str;
}

void	sort_env(t_env *env)
{
	t_env	*trav;

	while (env)
	{
		trav = env->next;
		while (trav)
		{
			if (ft_strcmp(trav->var, env->var) < 0)
				ft_switch(trav, env);
			trav = trav->next;
		}
		env = env->next;
	}
	
}

void	free_env(t_env *env)
{
	t_env *tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->content);
		free(tmp->var);
		free(tmp->env);
		free(tmp);
		tmp = NULL;
	}
}

void	displaye_env(t_var *var)
{
	t_env	*copy_env;
	t_env	*tmp;

	copy_env = copy(var);
	sort_env(copy_env);
	tmp = copy_env;
	while (tmp)
	{
		if (find_char(tmp->env, '=') < 0)
			printf("declare -x %s\n", tmp->env);
		else
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->content);
		tmp = tmp->next;
	}
	free_env(copy_env);
	var->status = 0;
}
void	errors_export(char *s)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("` :not a valid identifier\n", 2);
}
bool	check_str_exp(char *s, t_var *var, int *index)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (s[i] && is_valid(s[i], 1))
	{
		i++;
		len++;
	}
	while (s[i] && is_valid(s[i], 0))
		i++;
	if (!len || (s[i] && s[i] != '=' && (s[i] != '+' || s[i + 1] != '=')))
	{
		// printf("bash: export: `%s`: not a valid identifier\n", s);
		errors_export(s);
		var->status = 1;
		return (false);
	}
	*index = i;
	return (true);
}

void	handle_list_env(t_env *env, char *str, int i)
{
	char	*save_join;
	char	*save;

	if (str[i] == '+')
	{
		free(env->env);
		save = env->content;
		env->content = ft_strjoin(save, str + (i + 2));
		save_join = ft_strjoin(env->var, "=");
		env->env = ft_strjoin(save_join, env->content);
		(free(save), free(save_join));
	}
	else if (str[i] == '=')
	{
		free(env->content);
		free(env->env);
		env->content = ft_strdup(str + (i + 1));
		save_join = ft_strjoin(env->var, "=");
		env->env = ft_strjoin(save_join, env->content);
		free(save_join);
	}
}

int	is_existe(t_env *env, char *var_env, char *str, int i)
{
	// char	*save_join;
	// char	*save;

	while (env)
	{
		if (!ft_strcmp(env->var, var_env))
		{
			// if (str[i] == '+')
			// {
			// 	free(env->env);
			// 	save = env->content;
			// 	env->content = ft_strjoin(save, str + (i + 2));
			// 	save_join = ft_strjoin(env->var, "=");
			// 	env->env = ft_strjoin(save_join, env->content);
			// 	(free(save), free(save_join));
			// }
			// else if (str[i] == '=')
			// {
			// 	free(env->content);
			// 	free(env->env);
			// 	env->content = ft_strdup(str + (i + 1));
			// 	save_join = ft_strjoin(env->var, "=");
			// 	env->env = ft_strjoin(save_join, env->content);
			// 	free(save_join);
			// }
			handle_list_env(env, str, i);
			return (1);
		}
		env = env->next;
	}
	return (0);
}

void	add_var_to_list(t_env *env, char *var_env, char *str, int i)
{
	char	*env_join;
	char	*content;
	char	*save;

	if (!str[i])
	{
		free(var_env);
		return ;
	}
	if (str[i] == '+')
	{
		content = ft_strdup(str + (i + 2));
		save = ft_strjoin(var_env, "=");
		env_join = ft_strjoin(save, content);
		ft_add_env(&env, ft_creat_env(env_join,var_env, content));
		(free(save), free(env_join));
	}
	else if (str[i] == '=')
	{
		content = ft_strdup(str + (i + 1));
		save = ft_strjoin(var_env, "=");
		env_join = ft_strjoin(save, content);
		ft_add_env(&env, ft_creat_env(env_join,var_env, content));
		(free(save), free(env_join));
	}
}

void	ft_export(t_var *var, char **cmd)
{
	int		i;
	char	*var_env;

	if (!cmd[1])
		displaye_env(var);
	else
	{
		while (*++cmd)
		{
			if (!check_str_exp(*cmd, var, &i))
				continue ;
			printf("|%c|\n", (*cmd)[i]);
			var_env = ft_substr(*cmd, 0, i);
			if (is_existe(var->env, var_env, *cmd, i))
				free(var_env);
			else
				add_var_to_list(var->env, var_env, *cmd, i);
			var->status = 0;
		}
	}
}
