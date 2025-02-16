#include "../../minishell.h"

int	check_name(char *str)
{
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		++str;
	}
	return (0);
}

int	check_def(char *str)
{
	while (*str && *str != '=')
		++str;
	while (*str)
	{
		if (*str == '(' || *str == ')')
			return (1);
		++str;
	}
	return (0);
}

void	change_var(t_env *env, char *str, int i, t_alloc *alloc)
{
	while (i--)
		env = env->next;
	free(env->str);
	env->str = ft_strdup(str);
	if (!env->str)
		exit_parsing("Alloc", alloc, 1);
}

int	check_in_env(t_env *env, char *str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		++i;
	while (env)
	{
		k = 0;
		if (!ft_strncmp(env->str, str, i))
		{
			while (env->str[k] && env->str[k] != '=')
				k++;
			if (i == k)
				return (j);
		}
		env = env->next;
		++j;
	}
	return (-1);
}
