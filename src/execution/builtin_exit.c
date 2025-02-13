
#include "../../minishell.h"

void	check_b_exit(t_token *parse_result, t_env *env_head)
{
	if (parse_result->next)
	{
		write(STDERR_FILENO, "wrong input, use: exit with no option.\n", 40);
		free_token(parse_result);
		return ;
	}
	free_token(parse_result);
	free_env(env_head);
	rl_clear_history();
	exit (0);
}
