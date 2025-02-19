#include "../../minishell.h"

int	handle_open_fail(int fd[], t_data *data)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
	data->no_permission = 0;
	if (data->stdout_backup != STDOUT_FILENO)
		dup2(data->stdout_backup, STDOUT_FILENO);
	return (0);
}

void	pipe_pid_fail(int fd[], t_data *data, t_alloc *alloc)
{
	close(fd[0]);
	close(fd[1]);
	close_all_fd(data);
	free(data->pid);
	data->pid = NULL;
	exit_parsing("fork", alloc, 1);
}

int	check_special(t_token *token)
{
	token = token->prev;
	while (token && token->type != PI)
	{
		if (token->type == SR)
			return (1);
		if (token->type == DR)
			return (1);
		token = token->prev;
	}
	return (0);
}
