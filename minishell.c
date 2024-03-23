#include "included/minishell.h"


void sigint_handler(int sig) {
    (void)sig;
    ft_putstr_fd("\n", STDOUT_FILENO);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int main(int ac, char **av, char **env)
{
   char *input;
//    char **cmd;
    t_var g_var;
    t_node *root = NULL;
    (void)ac;
    (void)av;
   initialization(&g_var, env);
   rl_catch_signals = 0;
    while (1)
    {
        signal(SIGINT, sigint_handler);
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