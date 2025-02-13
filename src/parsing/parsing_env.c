#include "../../minishell.h"

/*
copy the env into a chained-list
*/
t_env	*parse_env(char **env)
{
	t_env *env_list;
	int	i;

	i = 1;
	if (!env)
		return (NULL);
	env_list = env_lstnew(ft_strdup(env[0]));
	if (!env_list)
		return (NULL);
	while (env[i])
	{
		if (env_lstadd_back(&env_list, env_lstnew(ft_strdup(env[i]))))
		{
			free_env(env_list);
			print_error("Malloc");
			exit(1);
		}
		++i;
	}
	return (env_list);
}
