#include "../included/minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = -1;
	if (!s)
		return (i);
	while (s[++i])
		;
	return (i);
}