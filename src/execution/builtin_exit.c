
#include "../../minishell.h"

void	check_b_exit(t_parse *parse_result, t_env *env_head)
{
	if (parse_result->next)
	{
		write(STDERR_FILENO, "wrong input, use: exit with no option.\n", 40);
		free_parse(parse_result);
		return ;
	}
	while (parse_result->prev)
		parse_result = parse_result->prev;
	free_parse(parse_result);
	free_env(env_head);
	rl_clear_history();
	exit (0);
}
