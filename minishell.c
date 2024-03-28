#include "included/minishell.h"


int check_signel  = 0;

int main(int ac, char **av, char **env)
{
    char *input;
    t_var g_var;
    t_node *root = NULL;
    (void)ac;
    (void)av;
    t_redir *herdoc_error;
    // check_signel = 0;
   initialization(&g_var, env);
    while (1)
    {
        ft_signal();
        input = readline("\033[1;32m->Prompt: \033[0m");
        if (!input)
        {
            ft_putstr_fd("exit\n", 1);
            break ;
        }
        check_signel = 1;
        add_history(input);
        root = parsing(input, &g_var);
        if (!root)
        {
            if (g_var.error_herdoc == NULL)
                continue;
            else
            {
                printf("\nherdoc ta3 l9lawi\n");
                herdoc_error = g_var.error_herdoc;
                while (herdoc_error)
                {
                    printf("|%s|\t", herdoc_error->file);
                    herdoc_error = herdoc_error->rchild;
                }
                printf("\n");
                ft_free_red(g_var.error_herdoc);
                g_var.error_herdoc = NULL;
                continue;
            }
        }
        ft_free_red(g_var.error_herdoc);
        g_var.error_herdoc = NULL;
        handle_herdoc(root, &g_var);
        execution(root, &g_var);
        check_signel = 0;
        return_in_out_fd(&g_var);
        freeTree(root);
    }
    rl_clear_history();
    return (0);
}
