
#include "../../minishell.h"

static int check_option(t_token **token)
{
	int	option;
	int	i;

	i = 1;
	option = 0;
	while (*token && (*token)->str[0] == '-')
	{
		while ((*token)->str[i] && (*token)->str[i] == 'n')
			++i;
		if ((*token)->str[i])
			break ;
		else
		{
			i = 1;
			option = 1;
		}
		*token = (*token)->next;
	}
	return (option);
}

void	mini_echo(t_token *token)
{
	int	option;

	option = check_option(&token);
	while (token && token->type <= 2)
	{
		write(STDOUT_FILENO, token->str, ft_strlen(token->str));
		if (token->next && token->next->type <= 2)
			write(STDOUT_FILENO, " ", 1);
		token = token->next;
	}
	if (!option)
		write (STDOUT_FILENO, "\n", 1);
}
