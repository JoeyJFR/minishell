#include "../../minishell.h"

void	check_b_cd(t_token *parse_result)
{
	if (!(parse_result->next) || parse_result->next->next \
	|| (parse_result->next->str)[0] == '-')
	{
		write(STDERR_FILENO, "wrong input, use: cd with a path only.\n", 40);
		free_token(parse_result);
		return ;
	}
	if (chdir(parse_result->next->str) == -1)
		perror("cd");
	free_token(parse_result);
}
