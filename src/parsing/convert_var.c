#include "../../minishell.h"

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
	while (ft_isalnum((*buffer)[i]) || (*buffer)[i] == '_')
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

char	*handle_var(char *str, char **buf, t_alloc *data)
{
	char	*var;
	int		var_index;

	var = fill_var(buf);
	if (!var)
	{
		free(str);
		exit_parsing("Malloc", data, 1);
	}
	var_index = check_var(var, data->env_head);
	free(var);
	if (var_index == -1)
		return (str);
	str = add_env_var(str, data, var_index, ft_strlen(*buf));
	return (str);
}

char	*convert_var(char *buf, t_alloc *data)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(buf) + 1));
	if (!str)
		exit_parsing("Malloc", data, 1);
	*str = '\0';
	while (*buf)
	{
		if (*buf == '$' && !is_in_squote(str))
		{
			str = handle_var(str, &buf, data);
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
