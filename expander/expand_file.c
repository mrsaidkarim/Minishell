#include "../included/minishell.h"


char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ptr = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
		(1) && (ptr[i] = s1[i], i++);
	while (s2[j])
		(1) && (ptr[i] = s2[j], i++, j++);
	ptr[i] = '\0';
	(free(s1), free(s2));
	return (ptr);
}

char *expand_file(char *file)
{
	int open;
	char *buffer;
	int i;

	open = 0;
	buffer = NULL;
	i = -1;
	while (file[++i])
	{
		if (file[i] == '"' || file[i] == '\'')
		{
			if (open == 0)
				open = file[i];
			else if (open == file[i])
				open = 0;
			else
				buffer = ft_strjoin_2(buffer, ft_chartostr(file[i]));
		}
		else
			buffer = ft_strjoin_2(buffer, ft_chartostr(file[i]));
	}
	return (free(file), buffer);
}
