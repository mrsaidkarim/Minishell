#include "../included/minishell.h"

void	ft_pwd(t_var *var)
{
	char	s[PATH_MAX];
	getcwd(s, PATH_MAX);
	printf("%s\n", s);
	var->status = 0;
}