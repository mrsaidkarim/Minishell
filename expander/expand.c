#include "../included/minishell.h"

int	size_list(t_list *head)
{
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**ft_list_to_2d(t_list *head)
{
	t_list	*tmp;
	char	**tab;
	int		size;
	int		i;

	if (!head)
		return (NULL);
	size = size_list(head);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		allocate_error(strerror(errno));
	i = 0;
	tmp = head;
	while (tmp)
	{
		tab[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	*ft_strjoin_2(char *s1, char *s2)
{
	char	*ptr;
	int		i;
	int		j;

	(1) && (i = 0, j = 0);
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ptr = (char *)malloc(((ft_strlen(s1) + ft_strlen(s2)) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
		(1) && (ptr[i] = s1[i], i++);
	while (s2[j])
		(1) && (ptr[i] = s2[j], i++, j++);
	ptr[i] = '\0';
	(free(s1), free(s2));
	return (ptr);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	temp = *lst;
	if (*lst)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

char	*ft_search_var(char *key, t_var *var)
{
	t_env	*tmp;

	tmp = var->env;
	while (tmp)
	{
		if (!ft_strcmp(key, tmp->var))
			return (ft_strdup(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_list(t_list **head)
{
	t_list	*tmp;

	while (*head)
	{
		tmp = *head;
		(*head) = (*head)->next;
		free(tmp->content);
		free(tmp);
	}
	(*head) = NULL;
}

int	is_del(char c)
{
	if (ft_isalnum(c))
		return (0);
	return (1);
}

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13) || c == 127)
		return (1);
	return (0);
}

char	*ft_chartostr(char c)
{
	char	str[2];

	str[0] = c;
	str[1] = 0;
	return (ft_strdup(str));
}

void	ft_print_lst(t_list *head)
{
	while (head)
	{
		printf("{%s}\n", head->content);
		head = head->next;
	}
}

void	ft_list_cwd(t_list **head)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.')
			ft_lstadd_back(head, ft_lstnew(ft_strdup(entry->d_name)));
		entry = readdir(dir);
	}
	closedir(dir);
	return ;
}

void	ft_init(t_exp *expand)
{
	expand->bf1 = NULL;
	expand->bf2 = NULL;
	expand->head = NULL;
	expand->open = 0;
	expand->i = 0;
	expand->flag = 0;
}

int	check_etoile(char *str)
{
	int	i;

	if (!*str)
		return (1);
	i = -1;
	while (str[++i] && str[i] == '*')
		;
	if (!str[i])
		return (0);
	return (1);
}

void	ft_add(t_exp *exp)
{
	if (exp->bf1)
	{
		if (!check_etoile(exp->bf1) && !exp->flag)
		{
			ft_list_cwd(&exp->head);
			free(exp->bf1);
		}
		else
		{
			if (!ft_strcmp("~", exp->bf1))
			{
				free(exp->bf1);
				exp->bf1 = ft_strdup(getenv("HOME"));
			}
			ft_lstadd_back(&exp->head, ft_lstnew(exp->bf1));
		}
		exp->bf1 = NULL;
		exp->flag = 0;
	}
}

void	ft_join(t_exp *exp, char *prompt)
{
	if (exp->open == 0)
	{
		exp->open = prompt[exp->i];
		exp->flag = 1;
	}
	else if (exp->open == prompt[exp->i])
	{
		if (!exp->bf1 && (prompt[exp->i + 1] == ' ' || !prompt[exp->i + 1]))
			exp->bf1 = ft_strdup("");
		exp->open = 0;
		if (!exp->bf1 || (prompt[exp->i] == prompt[exp->i - 1]
				&& !check_etoile(exp->bf1)))
			exp->flag = 0;
	}
	else
		exp->bf1 = ft_strjoin_2(exp->bf1, ft_chartostr(prompt[exp->i]));
}

void	ft_dollar(t_exp *exp, char *s, t_var *var)
{
	while (s[exp->i] && s[exp->i] == '$')
	{
		exp->bf2 = ft_chartostr(s[exp->i]);
		exp->i++;
		while (s[exp->i] && !is_del(s[exp->i]))
		{
			exp->bf2 = ft_strjoin_2(exp->bf2, ft_chartostr(s[exp->i]));
			if (ft_isdigit(exp->bf2[1]))
				break ;
			exp->i++;
		}
		if (!ft_strcmp(exp->bf2, "$") && s[exp->i] != '?')
			exp->bf1 = ft_strjoin_2(exp->bf1, exp->bf2);
		else
		{
			exp->bf1 = ft_strjoin_2(exp->bf1, ft_search_var(exp->bf2 + 1, var));
			free(exp->bf2);
		}
		if (s[exp->i] == '?' && (s[exp->i + 1] == ' ' || !s[exp->i + 1]))
			exp->bf1 = ft_strjoin_2(exp->bf1, ft_itoa(var->status));
		else if (s[exp->i] && is_del(s[exp->i]) && s[exp->i] != '$'
			&& (s[exp->i + 1] != '\0' && s[exp->i + 1] != ' '))
			exp->bf1 = ft_strjoin_2(exp->bf1, ft_chartostr(s[exp->i]));
		exp->bf2 = NULL;
	}
}

char	**ft_expand(char *prompt, t_var *var)
{
	t_exp	exp;
	char	**tab;

	ft_init(&exp);
	tab = NULL;
	while (prompt[exp.i])
	{
		if ((is_white_space(prompt[exp.i])) && exp.open == 0)
			ft_add(&exp);
		else if (prompt[exp.i] == '"' || prompt[exp.i] == '\'')
			ft_join(&exp, prompt);
		else if (prompt[exp.i] == '$' && exp.open != '\'')
			ft_dollar(&exp, prompt, var);
		else
			exp.bf1 = ft_strjoin_2(exp.bf1, ft_chartostr(prompt[exp.i]));
		if (!prompt[exp.i])
			break ;
		exp.i++;
	}
	ft_add(&exp);
	tab = ft_list_to_2d(exp.head);
	free_list(&exp.head);
	return (tab);
}
