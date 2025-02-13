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

void	change_var(t_env *env, char *str, int i)
{
	while (i--)
		env = env->next;
	free(env->str);
	env->str = ft_strdup(str);
	if (!env->str)
		write(STDOUT_FILENO, "Malloc\n", 7);
		//exit
}

int	check_in_env(t_env *env, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		++i;
	while (env)
	{
		if (!ft_strncmp(env->str, str, i))
			return (j);
		env = env->next;
		++j;
	}
	return (-1);
}
