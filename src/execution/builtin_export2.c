#include "../../minishell.h"

void	print_equal(char *s, char *pos)
{
	write(STDOUT_FILENO, "declare -x ", 12);
	write(STDOUT_FILENO, s, (pos - s) / sizeof(char));
	write(STDOUT_FILENO, "=\"", 2);
	write(STDOUT_FILENO, pos + 1, ft_strlen(pos) - 1);
	write(STDOUT_FILENO, "\"\n", 2);
}

void	print_space(char *s)
{
	write(STDOUT_FILENO, "declare -x ", 12);
	write(STDOUT_FILENO, s , ft_strlen(s));
	write(STDOUT_FILENO, "\"\n", 2);
}

int	cal_env_nb(t_env *env_head)
{
	t_env	*temp;
	int		n;

	n = 0;
	temp = env_head;
	while (temp)
	{
		n++;
		temp = temp->next;
	}
	return (n);
}
