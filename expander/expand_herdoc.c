#include "../included/minishell.h"

void	ft_start_with(char *s, bool *flag)
{
	if (*s == '"' || *s == '\'')
		*flag = false;
	else
		*flag = true;
}

void	init_var_exp_her(t_exp_herdoc *exp_her)
{
	exp_her->i = 0;
	exp_her->buffer1 = NULL;
	exp_her->buffer2 = NULL;
}

void	handle_expande_herdoc(char *str , t_var *var, t_exp_herdoc *exp_her)
{
	if (str[exp_her->i] == '$')
	{
		exp_her->buffer2 = ft_chartostr(str[exp_her->i]);
		exp_her->i++;
		while (str[exp_her->i] && !is_del(str[exp_her->i]))
		{
			exp_her->buffer2 = ft_strjoin_2(exp_her->buffer2, ft_chartostr(str[exp_her->i]));
			exp_her->i++;
		}
		if(str[exp_her->i] == '?' && (str[exp_her->i + 1] == ' ' || !str[exp_her->i + 1]))
			exp_her->buffer1 = ft_strjoin_2(exp_her->buffer1, ft_itoa(var->status));
		else
			exp_her->buffer1 = ft_strjoin_2(exp_her->buffer1, ft_search_var(exp_her->buffer2 + 1, var));
		if (str[exp_her->i] != '?')
			exp_her->buffer1 = ft_strjoin_2(exp_her->buffer1, ft_chartostr(str[exp_her->i]));
	}
	else
		exp_her->buffer1 = ft_strjoin_2(exp_her->buffer1, ft_chartostr(str[exp_her->i]));
}

char	*expand_herdoc(char *str, t_var *var)
{
	t_exp_herdoc exp_her;

	init_var_exp_her(&exp_her);
	while (str[exp_her.i])
	{
		handle_expande_herdoc(str, var, &exp_her);
		// if (str[exp_her.i] == '$')
		// {
		// 	exp_her.buffer2 = ft_chartostr(str[exp_her.i]);
		// 	exp_her.i++;
		// 	while (str[exp_her.i] && !is_del(str[exp_her.i]))
		// 	{
		// 		exp_her.buffer2 = ft_strjoin_2(exp_her.buffer2, ft_chartostr(str[exp_her.i]));
		// 		exp_her.i++;
		// 	}
		// 	if(str[exp_her.i] == '?' && (str[exp_her.i + 1] == ' ' || !str[exp_her.i + 1]))
		// 		exp_her.buffer1 = ft_strjoin_2(exp_her.buffer1, ft_itoa(var->status));
		// 	else
		// 		exp_her.buffer1 = ft_strjoin_2(exp_her.buffer1, ft_search_var(exp_her.buffer2 + 1, var));
		// 	if (str[exp_her.i] != '?')
		// 		exp_her.buffer1 = ft_strjoin_2(exp_her.buffer1, ft_chartostr(str[exp_her.i]));
		// }
		// else
		// 	exp_her.buffer1 = ft_strjoin_2(exp_her.buffer1, ft_chartostr(str[exp_her.i]));
		if(!str[exp_her.i])
			break;
		exp_her.i++;
	}
	return (free(str), exp_her.buffer1);
}