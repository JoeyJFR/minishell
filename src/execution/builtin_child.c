#include "../../minishell.h"

void	ft_built(char *av[], t_data *data)
{
	if (!ft_strcmp(av[0], "echo"))
		ft_echo(av, data);
	else if (!ft_strcmp(av[0], "pwd"))
		check_b_pwd(av);
	else if (!ft_strcmp(av[0], "env"))
		check_b_env(av, data);
}
