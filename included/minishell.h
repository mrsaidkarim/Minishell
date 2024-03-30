/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zelabbas <zelabbas@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 00:32:45 by skarim            #+#    #+#             */
/*   Updated: 2024/03/30 17:33:51 by zelabbas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>

typedef struct s_node	t_node;

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
	char			*env;
	char			*var;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_redir
{
	t_token			tok;
	char			*file;
	bool			flg;
	int				fd;
	int				s_fd;
	struct s_redir	*lchild;
	struct s_redir	*rchild;
}	t_redir;

typedef struct s_node
{
	char			*pre_cmd;
	char			**cmd;
	t_token			tok;
	int				precedence;
	int				fd[2];
	t_redir			*redirections;
	t_node			*rchild;
	t_node			*lchild;
}	t_node;

typedef struct s_var
{
	t_env	*env;
	int		status;
	int		fd_input;
	int		fd_output;
	int		flag;
	t_redir	*error_herdoc;
}	t_var;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_exp
{
	char	*bf1;
	char	*bf2;
	int		open;
	int		i;
	t_list	*head;
	int		flag;
}	t_exp;

typedef struct s_exp_herdoc
{
	char	*bf1;
	char	*bf2;
	int		i;
}	t_exp_herdoc;

char		*ft_strtrim(char const *s1, char const *set);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_print_syntax_error(char *msg, char *c, int count);
char		*ft_clean_input(char *str);
int			ft_first_check(char *str);
t_token		check_tok(char *str);
int			ft_check_delim(char *str, int i);
int			ft_isspace(char c);
int			ft_is_bracket(char c);
int			ft_precedence(t_token token);
t_redir		*ft_create_rednode(char *file_name, t_token tok);
int			ft_add_red(t_redir **redhead, t_redir *rednode);
int			ft_protected_word(char *line, int *i, int *len, char c);
int			ft_skip_for_quotes(char *line, int *i);
int			ft_find_bclose(char *line, int i);
int			ft_check_syntax_combination(char *line, int *index, int *bclose,
				t_token tok);
t_node		*ft_create_cmd(char *str, int len, t_token tok, t_redir *redlist);
int			ft_add_back(t_node **head, t_node *new);
t_node		*parsing(char *input, t_var *var);
t_node		*ft_infix_postfix(t_node **head);
void		ft_build_tree(t_node *head);
void		ft_heredoc_syntax(t_redir *red, t_var *var);
int			check_parentheses_error(char *line, t_var *var, t_redir *red);
// function for exec;
int			ft_strcmp(const char *s1, const char *s2);
void		initialization(t_var *var, char **env);
char		**ft_split(char const *str, char c);
void		ft_putstr_fd(char *s, int fd);
void		ft_echo(char **cmd, t_var *var);
void		ft_pwd(t_var *var);
size_t		ft_strlen(const char *s);
void		ft_cd(t_var *var, char **cmd);
char		*ft_strdup(const char *s1);
void		allocate_error(char *str);
t_env		*ft_creat_env(char *env, char *var, char *content);
t_env		*ft_creat_env_exp(char *env, char *var, char *content);
void		ft_add_env(t_env **head, t_env *new);
void		ft_env(t_var *var);
t_env		*ft_env_search(t_env *env, char *key);
int			ft_env_replace(t_env *env, char *key, char *value);
int			ft_atoi(const char *str);
void		ft_exit(t_var *var, char **cmd);
void		execution(t_node *root, t_var *var);
void		exec_cmd(t_node *node, t_var *var);
void		free_matrix(char **tab);
char		*ft_strjoin(char const *s1, char const *s2);
void		return_in_out_fd(t_var *var);
void		ft_unset(t_var *var, char **cmd);
char		*ft_itoa(int n);
void		ft_export(t_var *var, char **cmd);
t_env		*copy(t_var *var);
void		displaye_env(t_var *var);
void		ft_switch(t_env *trav, t_env *env);
void		sort_env(t_env *env);
int			check_var(char *str);
void		delete_node(t_var *var, t_env *node, int check);
pid_t		child_write(t_node *node, int tab[2], t_var *var);
pid_t		child_read(t_node *node, int tab[2], t_var *var);
char		*get_path(char *cmd, t_var *var);
char		**env_list_to_tab(t_env *env);
int			check_slach(char *s, t_var *var);
void		error_heredoc(t_redir *node, t_var *var);
// redirection :
int			handle_rederction(t_node *node, t_var *var);
// expand;
char		*expand_herdoc(char *str, t_var *var);
char		*expand_file(char *file);
bool		start_herdoc(t_redir *node, t_var *var, int tab[2]);
void		ft_init(t_exp *expand);
int			is_del(char c);
int			is_white_space(char c);
int			check_etoile(char *str);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *new);
int			size_list_exp(t_list *head);
char		**ft_list_to_2d(t_list *head);
char		*ft_search_var(char *key, t_var *var);
void		ft_list_cwd(t_list **head);
char		*ft_strjoin_2(char *s1, char *s2);
char		**ft_expand(char *promt, t_var *var);
char		*ft_chartostr(char c);
int			find_char(char *env, char c);
int			is_valid(char c, int fisrt);
char		**get_paths(t_var *var);
int			ft_isalnum(int c);
int			ft_isdigit(int c);
long long	ft_atoll(const char *str, int *i);
void		ft_check_expand(char *s, bool *flag);
//// handle errors in execution !
int			check_pipe(int tab[2]);
int			ft_heredoc(t_redir *node, t_var *var);
void		handle_herdoc(t_node *root, t_var *var);
void		errors_export(char *s);
void		errors_unset(char *s);
void		error_cmd_not_found(char *cmd);
void		error_execve(char *path, int error);
///////////////////////////////////////// signals;
void		signal_midl_exec(void);
int			update_status(int status);
void		ft_signal(void);
// free allocated data
void		ft_free_red(t_redir *reds);
void		ft_free(t_node **head);
void		free_tree(t_node *root);
void		free_env(t_env *env);
void		free_list(t_list **head);
void		free_list_env(t_var *var);
void		free_all(t_var *var);

extern int				g_signel;
#endif