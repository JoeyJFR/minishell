#include "mini_exec.h"

void	child(char *av[], t_data *data, int fd[])
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(av, data);
}

int	handle_open_fail(int fd[], t_data *data)
{
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		return (1);
	}
	close (fd[0]);
	data->open_in_fail = 0;
	return (0);
}

int	handle_pipe(char *av[], t_data *data)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror ("pipe");
		return (1);
	}
	if (data->open_in_fail)
		return (handle_open_fail(fd, data));
	pid = fork();
	if (pid == 0)
		child(av, data, fd);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd[0]);
		return (1);
	}
	close (fd[0]);
	(data->pid)[data->pid_nb++] = pid;
	return (0);
}

int	count_pid(t_parse *parse_result)
{
	int	i;

	i = 1;
	while (parse_result)
	{
		if (parse_result->type == PIPE)
			i++;
		parse_result = parse_result->next;
	}
	return (i);
}
