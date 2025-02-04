#include "mini_exec.h"

void	ft_echo_n(char *av[], t_data *data)
{
	int	i;

	i = 2;
	while (av[i])
	{
		write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	free(data->pid);
	exit(0);
}

void	ft_echo_l(char *av[], t_data *data)
{
	int	i;

	i = 1;
	while (av[i])
	{
		write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	write(STDOUT_FILENO, "\n", 1);
	free(data->pid);
	exit(0);
}

void	ft_echo(char *av[], t_data *data)
{
	if (!ft_strcmp(av[1], "-n"))
		ft_echo_n(av, data);
	else
		ft_echo_l(av, data);
}
