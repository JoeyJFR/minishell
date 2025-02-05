#include "../../minishell.h"

void	cd_exp_un_ex(t_parse *parse_result, t_env *env_head)
{
	if (!ft_strcmp(parse_result->str, "cd"))
		check_b_cd(parse_result);
	else if (!ft_strcmp(parse_result->str, "exit"))
		check_b_exit(parse_result, env_head);
	else if (!ft_strcmp(parse_result->str, "export"))
		check_b_export(parse_result, env_head);
}

int	check_cd_exp_un_ex(t_parse *parse_result)
{
	if (!ft_strcmp(parse_result->str, "cd"))
		return (1);
	if (!ft_strcmp(parse_result->str, "export"))
		return (1);
	if (!ft_strcmp(parse_result->str, "unset"))
		return (1);
	if (!ft_strcmp(parse_result->str, "exit"))
		return (1);
	return (0);
}
