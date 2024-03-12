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
#include <errno.h>


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

typedef struct s_redir
{
	t_token			tok;
	char			*file;
	// bool			flg;
	// int				fd;
	struct s_redir	*lchild;
	struct s_redir	*rchild;
}t_redir;

typedef struct s_node
{
	char			*pre_cmd;
    char            **cmd;
	t_token			tok;
    int				precedence;
	t_redir			*redirections;
    t_node          *rchild;
    t_node          *lchild;
}	t_node;

// int		ft_strcmp(const char *s1, const char *s2);
// char	**ft_split(char const *str, char c);
// void	ft_putstr_fd(char *s, int fd);
// void	ft_echo(char **cmd);
// char	*ft_strjoin(char *s1, char *s2);
// void	ft_pwd(void);
// char	*ft_strdup(const char *s1);

char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
int	    ft_print_syntax_error(char *msg, char *c, int count);
char    *ft_clean_input(char *str);
int	    ft_first_check(char *str);
void	allocate_error(char *str);
t_token	check_tok(char *str);
int	    ft_check_delim(char *str, int i);
int	    ft_isspace(char c);
int	    ft_is_bracket(char c);
int	    ft_precedence(t_token token);
t_redir	*ft_create_rednode(char *file_name, t_token tok);
int	    ft_add_red(t_redir **redhead, t_redir *rednode);
int	    ft_protected_word(char *line, int *i, int *len, char c);
int	    ft_skip_for_quotes(char *line, int *i);
int	    ft_find_bclose(char *line, int i);
int	    ft_check_syntax_combination(char *line, int *index, int *bclose, t_token tok);
t_node	*ft_create_cmd(char *str, int len, t_token tok, t_redir *redlist);
int	    ft_add_back(t_node **head, t_node *new);
char    *parsing(char *input);

#endif
