#include "../included/minishell.h"

char	*ft_one_space(char *str)
{
	int result_index = 0;
    int consecutive_spaces = 0;
	int len = ft_strlen(str);
    char *result = malloc(len + 1);
	int i = -1;

    while (++i < len)
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
            consecutive_spaces++;
            if (consecutive_spaces <= 1)
                result[result_index++] = ' ';
        }
		else
		{
            result[result_index++] = str[i];
            consecutive_spaces = 0;
        }
    }
    result[result_index] = '\0';
	free(str);
	return (result);
}
char *function_one_space(char *str)
{
    char *result;
	result = ft_strtrim(str, " ");
	result = ft_one_space(result);
	free(str);
	return (result);
}
