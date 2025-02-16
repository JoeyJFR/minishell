
#include "../../minishell.h"

static int check_option(char *av[])
{
	int	option;
	int	i;

	i = 1;
	option = 0;
	if (!ft_strcmp(av[1], "-n"))
		option = 1;
	return (option);
}

int	mini_echo(char *av[])
{
	int	option;
	int	i;

	i = 1;
	option = check_option(av);
	while (av[i + option])
	{
		write(STDOUT_FILENO, av[i + option], ft_strlen(av[i + option]));
		if (av[i + option + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!option)
		write (STDOUT_FILENO, "\n", 1);
	return (1);
}
