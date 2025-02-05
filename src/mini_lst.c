#include "../minishell.h"

t_parse	*mini_lstnew(char *str)
{
	t_parse	*new_list;

	new_list = malloc(sizeof(t_parse));
	if (!new_list)
		return (NULL);
	new_list->str = str;
	new_list->type = -1;
	new_list->next = NULL;
	new_list->prev = NULL;
	return (new_list);
}

int	mini_lstsize(t_parse *lst)
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

void	mini_lstadd_front(t_parse **lst, t_parse *new)
{
	new->next = *lst;
	(*lst)->prev = new;
	*lst = new;
}

void	mini_lstadd_back(t_parse **lst, t_parse *new)
{
	t_parse	*temp;

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

void	free_parse(t_parse *parse)
{
	t_parse	*tmp;

	while (parse)
	{
		tmp = parse;
		parse = parse->next;
		free(tmp->str);
		free(tmp);
	}
}
