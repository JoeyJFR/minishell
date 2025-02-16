#include "../minishell.h"

void	exit_parsing(char *str, t_alloc *data, int status)
{
	if (data)
	{
		if (data->env_head)
		{
			free_env(data->env_head);
			data->env_head = NULL;
		}
		if (data->token_head)
		{
			free_token(data->token_head);
			data->token_head = NULL;
		}
		if (data->str)
		{
			free(data->str);
			data->str = NULL;
		}
	}
	if (str)
		print_error(str);
	exit(status);
}

void	exit_with_msg(char *str, int status)
{
	print_error(str);
	exit(status);
}

void	print_error(char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
}
