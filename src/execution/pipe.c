#include "../../minishell.h"

void	child(char *av[], t_data *data, int fd[], t_alloc *alloc)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_IGN);
	if (!av[0])
	{
		if (STDIN_FILENO != 0)
			close(STDIN_FILENO);
		if (STDOUT_FILENO != 1)
			close(STDOUT_FILENO);
		close_all_fd(data);
		free_alloc_pid(alloc, data);
		rl_clear_history();
		exit (0);
	}
	exec_cmd(av, data, alloc);
}

void	child_special(char *av[], t_data *data, int fd[], t_alloc *alloc)
{
	close(fd[0]);
	close(fd[1]);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_IGN);
	if (!av[0])
	{
		if (STDIN_FILENO != 0)
			close(STDIN_FILENO);
		if (STDOUT_FILENO != 1)
			close(STDOUT_FILENO);
		close_all_fd(data);
		free_alloc_pid(alloc, data);
		rl_clear_history();
		exit (0);
	}
	exec_cmd(av, data, alloc);
}

int	handle_pipe(t_token *token, char *av[], t_data *data, t_alloc *alloc)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror ("pipe"), 1);
	if (data->no_permission)
		return (handle_open_fail(fd, data));
	pid = fork();
	if (pid == -1)
		pipe_pid_fail(fd, data, alloc);
	if (pid == 0)
	{
		if (check_special(token))
			child_special(av, data, fd, alloc);
		else
			child(av, data, fd, alloc);
	}
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close (fd[0]);
	(data->pid)[(data->pid_nb)++] = pid;
	if (data->stdout_backup != STDOUT_FILENO)
		dup2(data->stdout_backup, STDOUT_FILENO);
	return (0);
}
