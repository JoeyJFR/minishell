#include "../../minishell.h"

char	*fill_var_def(char *def, t_env *env, char *old_str, int buffer_len)
{
	char	*var;
	int		var_len;

	var_len = ft_strlen(old_str) + ft_strlen(def) + buffer_len + 3;
	var = ft_calloc(sizeof(char), var_len);
	if (!var)
	{
		free(old_str);
		free_env(env);
		exit_with_msg("Alloc", 1);
	}
	var = ft_strcat(var, old_str);
	var = ft_strcat(var, "\"");
	var = ft_strcat(var, def);
	var = ft_strcat(var, "\"");
	free(old_str);
	return (var);
}

char	*add_env_var(char *str, t_env *env, int var_i, int buf_len)
{
	int		i;
	int		j;

	i = 0;
	while (var_i--)
		env = env->next;
	while (env->str[i] && env->str[i] != '=')
		++i;
	++i;
	j = i;
	while (env->str[j])
	{
		if (env->str[j++] == '"')
		{
			free(str);
			print_error("Backslash case");
			return (NULL);
		}
	}
	str = fill_var_def(&env->str[i], env, str, buf_len);
	return (str);
}
