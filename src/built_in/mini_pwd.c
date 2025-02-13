
#include "../../minishell.h"

// check malloc getcwd vs getcwd no find != ?
void	mini_pwd(t_token *token)
{
	char	*pwd;

	if (token && token->str[0] == '-')
	{
		write(2, "mini_pwd has no options\n", 24);
		return ;
	}
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
