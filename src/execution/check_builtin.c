#include "../../minishell.h"

int	built_in(t_token *token, t_env *env)
{
	int r_val;

	r_val = 0;
	if (token->type == CD && ++r_val)
		mini_cd(token, env);
	// else if (!ft_strcmp(token->str, "exit"))
	// 	mini_exit(token, env);
	else if (token->type == EXPORT && ++r_val)
	 	mini_export(env, token->next);
	else if (token->type == UNSET && ++r_val)
		mini_unset(env, token->next);
	else if (token->type == PWD && ++r_val)
		mini_pwd(token->next);
	else if (token->type == ENV && ++r_val)
		mini_env(env);
	else if (token->type == ECHO && ++r_val)
		mini_echo(token->next);
	return (r_val);
}
