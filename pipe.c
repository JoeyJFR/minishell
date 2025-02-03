#include "mini_exec.h"

void	child(char *av[], t_data *data, int fd[])
{
	close(fd[0]);
	if (data->infile != 0)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
			perror("dup2");
		close(data->infile);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(av, data);
}

void	handle_pipe(char *av[], t_data *data, int fd[])
{
	pid_t	pid;
	int		fd2[2];

	pipe(fd2);
	pid = fork();
	if (pid == 0)
		child(av, data, fd2);
	else if (pid > 0)
	{
		close(fd2[1]);
		if (data->outfile != 1)
			close(data->outfile);
		data->infile = fd2[0];
		(data->pid)[data->pid_nb++] = pid;
	}
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
