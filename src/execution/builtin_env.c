#include "../../minishell.h"

void	ft_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		write(STDOUT_FILENO, data->env[i], ft_strlen(data->env[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	check_b_env(char *av[], t_data *data)
{
	if (!av[1])
		ft_env(data);
	else
		write(STDOUT_FILENO, \
		"wrong input, use: export with no options or arguments.\n", 56);
}