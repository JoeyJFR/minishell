#include "../../minishell.h"

static int	error_int(char *str)
{
	print_error(str);
	return (1);
}

int	mini_cd(char *av[], t_data *data, t_alloc *alloc)
{
	int	i;

	i = -1;
	(void)alloc;
	if (av[2])
		return (error_int("cd: too many arguments"));
	else if (!av[1])
	{
		while (data->env[++i])
		{
			if (!ft_strncmp("HOME=", data->env[i], 5))
			{
				chdir(data->env[i] + 5);
				return (0);
			}
		}
		return (error_int("no HOME variable"));
	}
	else if (chdir(av[1]) == -1)
		return (error_int("Incorrect path / no right to go there"));
	return (0);
}
