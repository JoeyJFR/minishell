#include "../minishell.h"

void	mini_error(char *str, int status)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd(str, 2);
	exit(status);
}
