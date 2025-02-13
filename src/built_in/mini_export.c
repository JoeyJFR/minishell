
#include "../../minishell.h"

static void	add_var(t_env *env, char *str)
{
	t_env	*new_var;
	int		i_env;

	i_env = check_in_env(env, str);
	if (i_env >= 0)
		change_var(env, str, i_env);
	else
	{
		new_var = env_lstnew(str);
		if (!new_var)
			;//ok we got an issue
		env_lstadd_back(&env, new_var);
	}
}

void	mini_export(t_env *env, t_token* token)
{
	if (!token || (token && token->type > 8))
		return (ascii_env(env));
	while (token && token->type <= 8)
	{
		if (token->str[0] == '-')
		{
			print_error("mini_export takes no option\n");
			return ;
		}
		if (check_name(token->str))
		{
			print_error("Invalid identifier");
			return ;
		}
		if (check_def(token->str))
			return ;
		add_var(env, token->str);
		token = token->next;
	}
}
