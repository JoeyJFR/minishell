#include "../../minishell.h"

void	mini_cd(t_token *pr, t_env *env)
{
	if (!pr->next)
	{
		while (env)
		{
			if (!ft_strncmp("HOME=", env->str, 5))
				chdir(&env->str[5]);
			env = env->next;
		}
		return ;
	}
	else if (pr->next->next)
		return ;
	else if (chdir(pr->next->str) == -1)
		printf("path incorrect/no right to go there\n");
}
