#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>

#define UNEXPECTED_TOK "syntax error near unexpected token"

typedef struct s_node t_node;

typedef enum s_token
{
    EXPR,
    IN,
    OUT,
    APPEND,
    HEREDOC,
    PIPE,
    AND,
    OR,
    BRKT_OPEN,
    BRKT_CLOSE,
    DOLLAR,
}	t_token;

typedef struct s_env
{
    char            *env;
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
    t_token				tok;
    char				*file;
    bool				flg;
    int					fd;
    struct s_redir		*lchild;
    struct s_redir		*rchild;
}t_redir;

typedef struct s_node
{
	char			*pre_cmd;
    char            **cmd;
	t_token			tok;
    t_redir         *redirection;
    int             fd[2];
    int             precedence;
    t_node          *rchild;
    t_node          *lchild;
}	t_node;

typedef struct s_var
{
    t_env   *env;
    int 	status;
    int     fd_input;
    int     fd_output;
}   t_var;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;


typedef struct s_exp
{
    char    *buffer1;
    char    *buffer2;
    int     open;
    int     i;
    t_list  *head;
    int     flag;
}   t_exp;

int		ft_strcmp(const char *s1, const char *s2);
void	initialization(t_var *var,char **env);
char	**ft_split(char const *str, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_echo(char **cmd, t_var *var);
size_t	ft_strlen(const char *s);
void	ft_pwd(t_var *var);
size_t	ft_strlen(const char *s);
char	*parsing(char *input);
char	*function_one_space(char *str);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);
void	allocate_error(char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
t_node	*ft_create_cmd(char *str, size_t len, t_token tok);
void	ft_add_back(t_node **head, t_node *new);
t_env	*ft_creat_env(char *env, char *var, char *content);
void	ft_add_env(t_env **head, t_env *new);
void	ft_env(t_var *var);
int     ft_atoi(const char *str);
void	ft_exit(t_var *var, char **cmd);
void	execution(t_node *root, t_var *var);
void	exec_cmd(t_node *node,t_var *var);
void	free_matrix(char **tab);
char	*ft_strjoin(char const *s1, char const *s2);
void	return_in_out_fd(t_var *var);
void	ft_unset(t_var *var, char **cmd);
char	*ft_itoa(int n);


// expand;
char	*ft_search_var(char *key, t_var *var);
// t_list *ft_expand(char *promt, t_var *var);
char    **ft_expand(char *promt, t_var *var);
char	*ft_chartostr(char c);
void	ft_echo2(t_list *head, t_var *var);

//// handle errors in execution !
int	check_pipe(int tab[2]);
#endif
