#include "../../minishell.h"

int	check_syntax(t_token *token)
{
	if (token && token->type == PI)
		return (1);
	while (token && token->next)
	{
		if (token->type > 8 && token->next->type > 8)
			return (1);
		token = token->next;
	}
	if (token && token->type > 8)
		return (1);
	return (0);
}
