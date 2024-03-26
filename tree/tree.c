#include "../included/minishell.h"

t_node    *ft_create_node(char *data, int index, int    type)
{
    t_node    *new_node;

    new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        return (NULL);
    new_node->pre_cmd = data;
    new_node->index = index;
    new_node->tok = type;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
	new_node->redirections = NULL;
	new_node->cmd  = NULL;
    return (new_node);
}

t_node    *ft_insert_node(t_node *root, char *data, int index, int type)
{
    if (!root)
        root = ft_create_node(data, index, type);
    else
    {
        if (root->index >= index)
            root->lchild = ft_insert_node(root->lchild, data, index, type);
        else
            root->rchild = ft_insert_node(root->rchild, data, index, type);
    }
    return (root);
}

void    ft_inorder_traversal(t_node *root)
{
    if (root)
    {
        ft_inorder_traversal(root->lchild);
        printf("index (%d) type (", root->index);
        if (root->tok == EXPR)
            printf("CMD");
        else if (root->tok == PIPE)
            printf("PIPE");
        else if (root->tok == AND)
            printf("AND");
        else if (root->tok == OR)
            printf("OR");
        else if (root->tok == REDIR_OUT)
            printf("REDIRECT_OUTPUT");
        else if (root->tok == REDIR_APPEND)
            printf("REDIRECT_OUTPUT_APPEND");
        else if (root->tok == REDIR_IN)
            printf("REDIRECT_INPUT");
        else if (root->tok == HEREDOC)
            printf("HEREDOC");
        printf(") --> `%s`\n", root->pre_cmd);
        ft_inorder_traversal(root->rchild);
    }
}

// t_node    *ft_build_tree1(void)
// {
//     t_node    *root;

//     root = NULL;
//     root = ft_insert_node(root, ft_strdup("|"), 2, PIPE);
//     root = ft_insert_node(root, ft_strdup("cat"), 1, EXPR);
//     root = ft_insert_node(root, ft_strdup("|"), 4, PIPE);
//     root = ft_insert_node(root, ft_strdup("ls"), 3, EXPR);
//     root = ft_insert_node(root, ft_strdup("wc"), 5, EXPR);
//     return (root);
// }

// t_node    *ft_build_tree1(void)
// {
//     t_node    *root;

//     root = NULL;
//     root = ft_insert_node(root, ft_strdup("|"), 2, PIPE);
//     root = ft_insert_node(root, ft_strdup("cat"), 1, EXPR);
//     root = ft_insert_node(root, ft_strdup("|"), 4, PIPE);
//     root = ft_insert_node(root, ft_strdup("cat"), 3, EXPR);
//     root = ft_insert_node(root, ft_strdup("|"), 6, PIPE);
//     root = ft_insert_node(root, ft_strdup("cat"), 5, EXPR);
//     root = ft_insert_node(root, ft_strdup("ls"), 7, EXPR);
//     return (root);
// }
t_node    *ft_build_tree1(void)
{
    t_node    *root;

    root = NULL;
    root = ft_insert_node(root, ft_strdup("|"), 2, PIPE);
    root = ft_insert_node(root, ft_strdup("ls"), 1, EXPR);
    root = ft_insert_node(root, ft_strdup("|"), 4, PIPE);
    root = ft_insert_node(root, ft_strdup("ls"), 3, EXPR);
    root = ft_insert_node(root, ft_strdup("|"), 6, PIPE);
    root = ft_insert_node(root, ft_strdup("ls"), 5, EXPR);
    root = ft_insert_node(root, ft_strdup("ls"), 7, EXPR);
    return (root);
}


/*
give me the tree of this command :  ls | ks | wc
ChatGPT
To represent the command ls | ks | wc as a tree structure, we can break down the command into its components and arrange them hierarchically. Each component of the command will be represented as a node in the tree, with the pipes indicating the flow of data between the nodes.

Here's the tree structure for the command ls | ks | wc:

markdown
Copy code
         PIPE
        /    \
      LS     PIPE
            /    \
          KS     WC
LS: Represents the ls command, which lists directory contents.
KS: Represents the ks command.
WC: Represents the wc command, which counts lines, words, and characters in the input.
The nodes are connected by the pipe symbol (|), indicating that the output of the command on the left side of the pipe is used as input for the command on the right side of the pipe.
*/