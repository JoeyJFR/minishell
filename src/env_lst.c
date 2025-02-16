#include "../minishell.h"

t_env	*env_lstnew(char *str)
{
	t_env	*new_list;

	if (!str)
		return (NULL);
	new_list = malloc(sizeof(t_env));
	if (!new_list)
		return (NULL);
	new_list->str = str;
	new_list->next = NULL;
	return (new_list);
}

int	env_lstsize(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		++i;
		lst = lst->next;
	}
	return (i);
}

void	env_lstadd_front(t_env **lst, t_env *new)
{
	new->next = *lst;
	*lst = new;
}

int	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!new)
		return (-1);
	temp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	return (0);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->str);
		free(tmp);
	}
}
