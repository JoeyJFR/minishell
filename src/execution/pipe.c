#include "../../minishell.h"

void	child(char *av[], t_data *data, int fd[], t_env *env_head)
{
	close(fd[0]);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 in child process");
		close(fd[1]);
		free(data->pid);
		free_env(env_head);
		exit(get_error_code());
	}
	close(fd[1]);
	exec_cmd(av, data, env_head);
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

int	handle_pipe(char *av[], t_data *data, t_env *env_head)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (perror ("pipe"), 1);
	if (data->open_in_fail)
		return (handle_open_fail(fd, data));
	pid = fork();
	if (pid == 0)
		return (child(av, data, fd, env_head), 0);
	else
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2 in handle pipe");
			close(fd[0]);
			return (1);
		}
		close (fd[0]);
		(data->pid)[data->pid_nb++] = pid;
		return (0);
	}
}
