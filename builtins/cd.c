#include "../included/minishell.h"

int cherche_path(char **env)
{
    int i = -1;
    while (env[++i])
    {
        if (!strncmp(env[i], "PWD=", 4))
        	return (i);
    }
    return (-1);
}

void ft_cd(char **cmd, char **env)
{
    int i = -1;
    char *path = malloc(PATH_MAX);
    char cur_path[PATH_MAX];

    i = cherche_path(env);
    if (cmd[1] == NULL) {
        // If no argument is provided, change to the user's home directory
        char *home_dir = getenv("HOME");
        if (home_dir != NULL) {
            if (chdir(home_dir) != 0) {
                perror("chdir() error");
            }
        } else {
            fprintf(stderr, "HOME environment variable not set\n");
        }
        env[i] = ft_strjoin("PWD=", home_dir);
    } else {
        // Change to the specified directory
        // cmd[1] = ft_strjoin()
        if (chdir(cmd[1]) != 0) {
            perror("chdir() error");
        }
        // getcwd(path, sizeof(char *));
        env[i] = ft_strjoin("PWD=", cmd[1]);
    }
}