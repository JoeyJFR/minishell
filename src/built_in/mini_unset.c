#include "../../minishell.h"

static void	edit_env(t_env *env, char *str)
{
	t_env	*tmp;

	if (!ft_strncmp(str, env->str, ft_strlen(str)))
	{
		tmp = env;
		env = env->next;
		free(tmp->str);
		free(tmp);
		return ;
	}
	while (env->next)
	{
		if (!ft_strncmp(str, env->next->str, ft_strlen(str)))
		{
			tmp = env->next;
			env->next = env->next->next;
			free(tmp->str);
			free(tmp);
		}
		env = env->next;
	}
}

void mini_unset(t_env *env, t_token *token)
{
	while (token && token->type <= 2)
	{
		edit_env(env, token->str);	
		token = token->next;
	}
	return ;
}
