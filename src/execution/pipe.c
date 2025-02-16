#include "../../minishell.h"

void	child(char *av[], t_data *data, int fd[], t_alloc *alloc)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 in child process");
		close(fd[1]);
		free(data->pid);
		close_all_fd(data);
		exit(get_error_code());
	}
	close(fd[1]);
	exec_cmd(av, data, alloc);
}

int	handle_open_fail(int fd[], t_data *data)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 in handle open fail");
		close(fd[0]);
		return (1);
	}
	close (fd[0]);
	data->open_in_fail = 0;
	return (0);
}

void	child_special(char *av[], t_data *data, int fd[], t_alloc *alloc)
{
	close(fd[0]);
	close(fd[1]);
	exec_cmd(av, data, alloc);
}

int	handle_pipe(t_token *token, char *av[], t_data *data, t_alloc *alloc)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror ("pipe"), 1);
	if (data->open_in_fail)
		return (handle_open_fail(fd, data));
	pid = fork();
	if (pid == 0)
	{
		if ((token->prev->prev && token->prev->prev->type == SR) \
		|| (token->prev->prev && token->prev->prev->type == DR))
			child_special(av, data, fd, alloc);
		else
			child(av, data, fd, alloc);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (perror("dup2 in handle pipe"), close(fd[0]), 1);
	close (fd[0]);
	(data->pid)[data->pid_nb++] = pid;
	// if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
	// 	return (perror("dup2 for stdout_backup after pipe"), 1);
	return (0);
}
