#include "../minishell.h"

t_token	*mini_lstnew(char *str)
{
	t_token	*new_list;

	new_list = malloc(sizeof(t_token));
	if (!new_list)
		return (NULL);
	new_list->str = str;
	new_list->type = -1;
	new_list->next = NULL;
	new_list->prev = NULL;
	return (new_list);
}

int	mini_lstsize(t_token *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		++i;
		lst = lst->next;
	}
	return (i);
}

void	mini_lstadd_front(t_token **lst, t_token *new)
{
	new->next = *lst;
	(*lst)->prev = new;
	*lst = new;
}

void	mini_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*temp;

	temp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
}

void	free_token(t_token *parse)
{
	t_token	*tmp;

	while (parse)
	{
		tmp = parse;
		parse = parse->next;
		free(tmp->str);
		free(tmp);
	}
}
