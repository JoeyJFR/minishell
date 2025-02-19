#include "../../minishell.h"

int	mini_env(t_alloc *alloc)
{
	t_env	*temp;

	temp = alloc->env_head;
	while (temp)
	{
		write(STDOUT_FILENO, temp->str, ft_strlen(temp->str));
		write(STDOUT_FILENO, "\n", 1);
		temp = temp->next;
	}
	return (0);
}
