#include "../../minishell.h"

int	check_name(char *str)
{
	if (!ft_isalpha(*str) || *str == '_')
		return (1);
	while (*str && *str != '=')
	{
		if (!ft_isualnum(*str))
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

int	change_var(t_env *env, char *str, int i)
{
	while (i--)
		env = env->next;
	free(env->str);
	env->str = ft_strdup(str);
	if (!env->str)
		return (1);
	return (0);
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
