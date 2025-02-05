#include "../../minishell.h"

char	*add_var(char *str, t_env *env, int var_index, int len_buf)
{
	char	*tmp;
	int		i;

	i = 0;
	if (var_index < 0)
		return (str);
	while (var_index--)
		env = env->next;
	while (env->str[i] && env->str[i] != '=')
		++i;
	++i;
	tmp = ft_strjoin(str, &env->str[i]);
	free(str);
	if (!tmp)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(tmp) + len_buf + 1));
	if (str)
		str = ft_strcpy(str, tmp);
	free(tmp);
	return (str);
}

int	check_var(char *var, t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (!ft_strncmp(var, env->str, ft_strlen(var)))
			return (i);
		++i;	
		env = env->next;
	}
	return (-1);
}

char *fill_var(char **buffer)
{
	char	*var;
	int		i;

	i = 0;
	++(*buffer);
	while (ft_isalnum((*buffer)[i]))
		++i;
	var = malloc(sizeof(char) * (i + 1));	
	if (!var)
		return (NULL);
	i = 0;
	while (ft_isalnum(**buffer))
		var[i++] = *(*buffer)++;
	var[i] = '\0';
	return (var);
}

char	*handle_var(char *str, char **buf, t_env *env)
{
	char	*var;
	int		var_index;

	var = fill_var(buf);
	if (!var)
		return (free(str), NULL);
	var_index = check_var(var, env);
	free(var);
	str = add_var(str, env, var_index, ft_strlen(*buf));
	return (str);
}

char	*convert_var(char *buf, t_env *env)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(buf) + 1));
	if (!str)
		return (NULL);
	*str = '\0';
	while (*buf)
	{
		if (*buf == '$' && !is_in_squote(str))
		{
			str = handle_var(str, &buf, env);
			if (!str)
				return (NULL);
			i = ft_strlen(str);
		}
		if (*buf)
			str[i++] = *buf++;
		str[i] = '\0';
	}
	return (str);
}
