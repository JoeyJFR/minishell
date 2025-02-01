#include "mini_exec.h"


void	child(char *av[], t_data *data, int fd[])
{
	close(fd[0]);
	if (data->infile != 0)
	{
		dup2(data->infile, STDIN_FILENO);
		close(data->infile);
	}
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	exec_cmd(av, data);
}

void	handle_pipe(char *av[], t_data *data, int fd[])
{
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
		child(av, data, fd);
	else if (pid > 0)
	{
		if (data->infile != 0)
			close(data->infile);
		waitpid(pid, NULL, 0);
	}
}
