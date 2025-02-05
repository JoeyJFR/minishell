#include "../../minishell.h"

void	ft_echo_n(char *av[])
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
}

void	ft_echo_l(char *av[])
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
}

void	ft_echo(char *av[])
{
	if (!ft_strcmp(av[1], "-n"))
		ft_echo_n(av);
	else
		ft_echo_l(av);
}
