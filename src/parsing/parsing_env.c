#include "../../minishell.h"

t_env	*parse_env(char **env)
{
	t_env *env_list;
	int	i;

	i = 1;
	env_list = env_lstnew(ft_strdup(env[0]));
	if (!env_list)
		return (NULL);
	while (env[i])
	{
		if (env_lstadd_back(&env_list, env_lstnew(ft_strdup(env[i]))))
			return (/*free stack*/NULL);
		++i;
	}
	return (env_list);
}
