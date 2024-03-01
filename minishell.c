#include "included/minishell.h"

int main(int ac, char **av, char **env)
{
   char *input;
   char **cmd;

    while (1)
    {
        input = readline("\033[1;32m->Prompt: \033[0m");
        if (input && input[0])
        {
            add_history(input);
            input = parsing(input);
            if (!input)
                continue;
            // printf("-----%s------\n", input);
            // cmd = ft_split(input, ' ');
            // if (!ft_strcmp("exit", cmd[0]))
            // {
            //     printf("exit\n");
            //     break;
            // }
            // if (!ft_strcmp("echo", cmd[0]))
            //     ft_echo(cmd);
            // if (!ft_strcmp("pwd", cmd[0]))
            //     ft_pwd();
            // free(input);
        }
    }
    rl_clear_history();
    return (0);
}