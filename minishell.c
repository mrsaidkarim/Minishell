#include "included/minishell.h"


int check_signel  = 0;

int main(int ac, char **av, char **env)
{
    char *input;
    t_var g_var;
    t_node *root = NULL;
    (void)ac;
    (void)av;
    // check_signel = 0;
   initialization(&g_var, env);
    while (1)
    {
        ft_signal();
        input = readline("\033[1;32m->Prompt: \033[0m");
        if (input && input[0])
        {
            check_signel = 1;
            add_history(input);
            root = parsing(input, &g_var);
            if (!root)
                continue;
            handle_herdoc(root, &g_var);
            execution(root, &g_var);
            check_signel = 0;
            return_in_out_fd(&g_var);
            freeTree(root);
        }
        else
            break ;
    }
    rl_clear_history();
    return (0);
}