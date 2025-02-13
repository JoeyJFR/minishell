#include "../../minishell.h"

void	mini_env(t_env *env)
{
	while (env)
	{
		write(STDOUT_FILENO, env->str, ft_strlen(env->str));
		write(STDOUT_FILENO, "\n", 1);
		env = env->next;
	}
}
