#include "../../minishell.h"

int	mini_cd(char *av[], t_data *data)
{
	int	i;

	i = 0;
	if (av[2])
		return (print_error("cd: too many arguments"), 1);
	else if (!av[1])
	{
		while (data->env[i])
		{
			if (!ft_strncmp("HOME=", data->env[i], 5))
			{
				chdir(data->env[i] + 5);
				return (0);
			}
			i++;
		}
		return (print_error("no HOME variable"), 1);
	}
	else
	{
		if (chdir(av[1]) == -1)
			return (print_error("Incorrect path / no right to go there\n"), 1);
	}
	return (0);
}
