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

	pipe(fd);
	pid = fork();
	if (pid == 0)
		child(av, data, fd);
	else if (pid > 0)
	{
		if (data->outfile != 1)
			close(data->outfile);
		waitpid(pid, NULL, 0);
	}
}
