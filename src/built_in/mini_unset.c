#include "../../minishell.h"

size_t	len_before(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	return (i);
}

static void	edit_env(t_env **env, char *str)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = *env;
	if (!ft_strncmp(str, (*env)->str, ft_strlen(str)) \
	&& (ft_strlen(str) == len_before((*env)->str)))
	{
		*env = (*env)->next;
		return (free(tmp->str), free(tmp));
	}
	tmp = (*env)->next;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->str, ft_strlen(str)) \
		&& (ft_strlen(str) == len_before(tmp->str)))
		{
			prev->next = tmp->next;
			return (free(tmp->str), free(tmp));
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	mini_unset(t_env *env, char *av[])
{
	int	i;

	i = 1;
	while (av[i])
	{
		edit_env(&env, av[i]);
		i++;
	}
	return (0);
}
