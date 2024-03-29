#include "../included/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;
	size_t	i;

	if (!s1)
		return (NULL);
	ptr = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!ptr)
		allocate_error(strerror(errno));
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	ptr[i] = '\0';
	return (ptr);
}
