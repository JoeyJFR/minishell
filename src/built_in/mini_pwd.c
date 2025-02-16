
#include "../../minishell.h"

// check malloc getcwd vs getcwd no find != ?
int	mini_pwd(char *av[])
{
	char	*pwd;

	if (av[1] && av[1][0] == '-')
	{
		write(STDOUT_FILENO, "mini_pwd has no options\n", 24);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return (1);
	}
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
	return (0);
}
