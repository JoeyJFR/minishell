#include "../../minishell.h"

static int	check_exit_code(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			i++;
		else if (s[i] == '+' || s[i] == '-')
		{
			if (i != 0)
				return (1);
			else
			{
				i++;
				continue ;
			}

		}
		else
			return (1);
	}
	return (0);
}

void	mini_exit(char *av[], t_alloc *alloc, t_data *data)
{
	if (!av[1])
	{
		write(STDOUT_FILENO, "exit\n", 6);
		free(data->pid);
		close_all_fd(data);
		exit_parsing(NULL, alloc, alloc->exit_status);
	}
	else if (av[2])
		print_error("too many arguments");
	else
	{
		if (check_exit_code(av[1]))
		{
			free(data->pid);
			close_all_fd(data);
			exit_parsing("numeric argument required", alloc, 2);
		}
		alloc->exit_status = ft_atoi(av[1]) % 256;
		free(data->pid);
		close_all_fd(data);
		exit_parsing(NULL, alloc, alloc->exit_status);
	}
}
