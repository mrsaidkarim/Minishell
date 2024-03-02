#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>

#define UNEXPECTED_TOK "syntax error near unexpected token"

typedef struct s_node t_node;

typedef enum s_token
{
    EXPR,
    REDIR_IN,
    REDIR_OUT,
    REDIR_APPEND,
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

typedef struct s_node
{
	char			*pre_cmd;
    char            **cmd;
	t_token			tok;
    t_node          *rchild;
    t_node          *lchild;
}	t_node;


int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(char const *str, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_echo(char **cmd);
size_t	ft_strlen(const char *s);
void	ft_pwd(void);
size_t	ft_strlen(const char *s);
char	*parsing(char *input);
char	*function_one_space(char *str);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s1);

#endif
