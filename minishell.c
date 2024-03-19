#include "included/minishell.h"

int main(int ac, char **av, char **env)
{
   char *input;
//    char **cmd;
    t_var g_var;
    t_node *root = NULL;
    (void)ac;
    (void)av;
   initialization(&g_var, env);
    while (1)
    {
        input = readline("\033[1;32m->Prompt: \033[0m");
        if (input && input[0])
        {
            add_history(input);
            root = parsing(input);
            if (!root)
                continue;
            execution(root, &g_var);
        }
    }
    rl_clear_history();
    return (0);
}