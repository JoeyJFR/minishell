#include "../../minishell.h"

void	handle_rel_sfail(t_data *data, char *s, t_alloc *alloc)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	close_all_fd(data);
	free_alloc_pid(alloc, data);
	rl_clear_history();
	exit (2);
}

void	handle_rel_fail(t_data *data, char *path, char *s, t_alloc *alloc)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	close_all_fd(data);
	free_alloc_pid(alloc, data);
	if (path)
		free(path);
	rl_clear_history();
	exit (127);
}
