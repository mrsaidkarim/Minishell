#include "../included/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	char	*origin;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	origin = ptr;
	while (*s1)
		*ptr++ = *s1++;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (origin);
}
