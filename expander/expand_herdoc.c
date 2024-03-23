#include "../included/minishell.h"

void	ft_start_with(char *s, bool *flag)
{
	if (*s == '"' || *s == '\'')
		*flag = false;
	else
		*flag = true;
}
char	*expand_herdoc(char *str, t_var *var)
{
	char	*buffer1;
	char	*buffer2;
	int i;

	i = 0;
	buffer1 = NULL;
	buffer2 = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			buffer2 = ft_chartostr(str[i]);
			i++;
			while (str[i] && !is_del(str[i]))
			{
				buffer2 = ft_strjoin_2(buffer2, ft_chartostr(str[i]));
				i++;
			}
			buffer1 = ft_strjoin_2(buffer1, ft_search_var(buffer2 + 1, var));
			buffer1 = ft_strjoin_2(buffer1, ft_chartostr(str[i]));
		}
		else
			buffer1 = ft_strjoin_2(buffer1, ft_chartostr(str[i]));
		if(!str[i])
			break;
		i++;
	}
	return (free(str), buffer1);
}
