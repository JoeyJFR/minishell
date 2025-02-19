#include "../../minishell.h"

int	check_var(char *var, t_env *env)
{
	int	i;
	int	var_len;

	i = 0;
	var_len = ft_strlen(var);
	if (!var_len)
		return (-1);
	while (env)
	{
		if (!ft_strncmp(var, env->str, var_len) \
			&& (env->str[var_len] == '=' || !env->str[var_len]))
			return (i);
		++i;
		env = env->next;
	}
	return (-1);
}

char	*add_code(char *old_str, t_env *env, int exit_code, int buf_len)
{
	char	*var;
	char	*str;
	int		var_len;

	var = ft_itoa(exit_code);
	if (!var)
	{
		free(old_str);
		free_env(env);
		exit_with_msg("Alloc", 1);
	}
	var_len = ft_strlen(old_str) + ft_strlen(var) + buf_len + 1;
	str = ft_calloc(sizeof(char), var_len);
	if (!str)
	{
		free(var);
		free(old_str);
		free_env(env);
		exit_with_msg("Alloc", 1);
	}
	str = ft_strcpy(str, old_str);
	str = ft_strcat(str, var);
	free(old_str);
	free(var);
	return (str);
}

char	*fill_var(char **buffer)
{
	char	*var;
	int		i;

	i = 0;
	while (ft_isualnum((*buffer)[i]))
		++i;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (NULL);
	i = 0;
	while (ft_isalnum(**buffer) || **buffer == '_')
		var[i++] = *(*buffer)++;
	var[i] = '\0';
	return (var);
}

char	*handle_var(char *str, char **buf, t_env *env, int exit_code)
{
	char	*var;
	int		var_index;

	if (ft_isualnum(*(*buf + 1)) || *(*buf + 1) == '?')
		++(*buf);
	if (**buf == '?')
		str = add_code(str, env, exit_code, ft_strlen(++(*buf)));
	else
	{
		var = fill_var(buf);
		if (!var)
		{
			free(str);
			free_env(env);
			exit_with_msg("Alloc", 1);
		}
		var_index = check_var(var, env);
		free(var);
		if (var_index == -1)
			return (str);
		str = add_env_var(str, env, var_index, ft_strlen(*buf));
	}
	return (str);
}

char	*convert_var(char *buf, t_env *env, int exit_code)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc(sizeof(char), ft_strlen(buf) + 1);
	if (!str)
	{
		free_env(env);
		exit_with_msg("Alloc", 1);
	}
	while (*buf)
	{
		if (*buf == '$' && !is_in_squote(str) && *(buf + 1))
		{
			str = handle_var(str, &buf, env, exit_code);
			if (str == NULL)
				return (NULL);
			i = ft_strlen(str);
		}
		if (*buf)
			str[i++] = *buf++;
		str[i] = '\0';
	}
	return (str);
}
