#include "mini_exec.h"

void	cd_exp_un_ex(t_parse *parse_result)
{
	if (!ft_strcmp(parse_result->str, "cd"))
		check_b_cd(parse_result);
}