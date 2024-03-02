#include "../included/minishell.h"

void	ft_pwd(void)
{
	char	s[PATH_MAX];
	getcwd(s, PATH_MAX);
	printf("%s\n", s);
}