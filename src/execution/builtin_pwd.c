#include "../../minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("pwd");
		return ;
	}
	write(STDOUT_FILENO, pwd, ft_strlen(pwd));
	write(STDOUT_FILENO, "\n", 1);
	free(pwd);
}

void	check_b_pwd(char *av[])
{
	if (!av[1])
		ft_pwd();
	else
	{
		write(STDERR_FILENO, "wrong input, use: pwd with no options.\n", 40);
		return ;
	}
}
