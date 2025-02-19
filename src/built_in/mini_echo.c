#include "../../minishell.h"

static int check_option(char **av, int *i)
{
	int	option;
	int	j;

	j = 1;
	option = 0;
	while (av[*i] && av[*i][0] == '-')
	{
		while (av[*i][j] && av[*i][j] == 'n')
			++j;
		if (av[*i][j])
			break ;
		else
		{
			j = 1;
			option = 1;
		}
		++(*i);
	}
	return (option);
}

int	mini_echo(char *av[], t_alloc *alloc, t_data *data)
{
	int	option;
	int	i;

	(void)alloc;
	(void)data;
	i = 1;
	option = check_option(av, &i);
	while (av[i])
	{
		write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (!option)
		write (STDOUT_FILENO, "\n", 1);
	if (g_sigint == 1)
		g_sigint = 0;
	return (0);
}
