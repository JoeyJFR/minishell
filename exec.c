#include "mini_exec.h"

static void	exec_init(int *cmd_index, t_data *data, char *av[])
{
	*cmd_index = 0;
	data->infile = 0;
	data->outfile = 1;
	av[0] = NULL;
	data->here_doc = 0;
	data->pid_nb = 0;
}

static int	last_cmd(int fd[], t_data *data, char *av[])
{
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (exec_cmd(av, data) == -1)
		{
			perror("execute");
			return (1);
		}
	}
	close(fd[1]);
	if (data->outfile != 1)
		close(data->outfile);
	data->infile = fd[0];
	(data->pid)[data->pid_nb++] = pid;
	return (0);
}

static int	last_exec(char *av[], int cmd_index, t_data *data, int fd[])
{
	av[cmd_index] = NULL;
	if (data->outfile != STDOUT_FILENO)
	{
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		close(data->outfile);
	}
	if (data->infile != STDIN_FILENO)
	{
		if (dup2(data->infile, STDIN_FILENO) == -1)
		{
			perror("dup2");
			return (1);
		}
		close(data->infile);
	}
	return (last_cmd(data->fd, data, av));
}

static void	mid_exec(t_parse **p_result, int *cmd_i, char *av[], t_data *data)
{
	if ((*p_result)->type == ARG)
		av[(*cmd_i)++] = (*p_result)->str;
	else if ((*p_result)->type == SL || (*p_result)->type == DL \
			|| (*p_result)->type == SR || (*p_result)->type == DR)
		ft_ope(p_result, data, av, *cmd_i);
	else if ((*p_result)->type == PIPE)
	{
		av[*cmd_i] = NULL;
		handle_pipe(av, data, data->fd);
		*cmd_i = 0;
	}
	else if ((*p_result)->type == ABS_PATH)
		av[(*cmd_i)++] = (*p_result)->str;
	else
		av[(*cmd_i)++] = (*p_result)->str;
}

int	exec(t_parse *parse_result, t_data *data)
{
	char	*av[BUFFER_SIZE];
	int		cmd_index;
	int		stdin_bckup;
	int		stdout_bckup;

	stdin_bckup = dup(STDIN_FILENO);
	stdout_bckup = dup(STDOUT_FILENO);

	data->pid_nb = count_pid(parse_result);
	data->pid = malloc(sizeof(pid_t) * data->pid_nb);

	exec_init(&cmd_index, data, av);
	while (parse_result)
	{
		mid_exec(&parse_result, &cmd_index, av, data);
		parse_result = parse_result->next;
	}
	if (cmd_index > 0)
	{
		if (last_exec(av, cmd_index, data, data->fd) == 1)
		{
			perror("execute");
			return (1);
		}
	}
	while (--data->pid_nb >= 0)
	{
		waitpid(data->pid[data->pid_nb], NULL, 0);
	}
	dup2(stdin_bckup, STDIN_FILENO);
	dup2(stdout_bckup, STDOUT_FILENO);
	if (data->infile != 0)
		close(data->infile);
	if (data->outfile != 1)
		close(data->outfile);
	return (0);
}
