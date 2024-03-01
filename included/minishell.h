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

typedef enum s_token
{
    TOKEN_EXPR,
    TOKEN_REDIR_IN,
    TOKEN_REDIR_OUT,
    TOKEN_REDIR_APPEND,
    TOKEN_HEREDOC,
    TOKEN_PIPE,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_SPACE,
    TOKEN_BRKT_OPEN,
    TOKEN_BRKT_CLOSE,
    TOKEN_D_Q,
    TOKEN_S_Q,
    TOKEN_DOLLAR,
}	t_token;

# define malloc(size_t) NULL
typedef struct s_env
{
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	char			*content;
	t_token			tok;
}	t_list;


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
