#include "../../minishell.h"

char *fill_var_def(char *def, t_alloc *data, char *old_str, int buffer_len)
{
	char	*var;
	int		var_len;

	var_len = ft_strlen(old_str) + ft_strlen(def) + buffer_len + 3;
	var = ft_calloc(sizeof(char), var_len);
	if (!var)
		exit_parsing("Malloc", data, 1);
	var = ft_strcat(var, old_str);
	var = ft_strcat(var, "\"");
	var = ft_strcat(var, def);
	var = ft_strcat(var, "\"");
	free(old_str);
	return (var);
}

char	*add_env_var(char *str, t_alloc *data, int var_i, int buf_len)
{
	t_env	*env;
	int		i;
	int		j;

	i = 0;
	env = data->env_head;
	while (var_i--)
		env = env->next;
	while (env->str[i] && env->str[i] != '=')
		++i;
	++i;
	j = i;
	while (env->str[j])
		if (env->str[j++] == '"')
			return (free(str), print_error("Backslash case"), NULL);
	str = fill_var_def(&env->str[i], data, str, buf_len);
	return (str);
}
