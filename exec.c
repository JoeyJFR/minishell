#include "mini_exec.h"

static void	exec_init(int *cmd_index, t_data *data, char *av[])
{
	*cmd_index = 0;
	data->infile = 0;
	data->outfile = 1;
	av[0] = NULL;
}

static int	last_exec(char *av[], int cmd_index, t_data *data)
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
	if (exec_cmd(av, data) == -1)
	{
		perror("execute");
		return (1);
	}
	return (0);
}

// static void	mid_exec(t_parse *p_result, int *cmd_i, char *av[], t_data *data, int fd[])
// {
// 	if (p_result->type == ARG)
// 		av[(*cmd_i)++] = p_result->str;
// 	else if (p_result->type == SL || p_result->type == DL \
// 			|| p_result->type == SR || p_result->type == DR)
// 		ft_ope(&p_result, data, av, cmd_i);
// 	else if (p_result->type == PIPE)
// 	{
// 		av[*cmd_i] = NULL;
// 		handle_pipe(av, data, fd);
// 		*cmd_i = 0;
// 		close(fd[1]);
// 		data->infile = fd[0];
// 	}
// 	else if (p_result->type == ABS_PATH)
// 		av[(*cmd_i)++] = p_result->str;
// 	else
// 		av[(*cmd_i)++] = p_result->str;
// }

int	exec(t_parse *parse_result, t_data *data)
{
	char	*av[BUFFER_SIZE];
	int		cmd_index;
	int		result;
	int		fd[2];

	exec_init(&cmd_index, data, av);
	while (parse_result)
	{
		if (parse_result->type == ARG)
			av[(cmd_index)++] = parse_result->str;
		else if (parse_result->type == SL || parse_result->type == DL \
				|| parse_result->type == SR || parse_result->type == DR)
			ft_ope(&parse_result, data, av, cmd_index);
		else if (parse_result->type == PIPE)
		{
			av[cmd_index] = NULL;
			handle_pipe(av, data, fd);
			cmd_index = 0;
			close(fd[1]);
			data->infile = fd[0];
		}
		else if (parse_result->type == ABS_PATH)
			av[(cmd_index)++] = parse_result->str;
		else
			av[(cmd_index)++] = parse_result->str;
		parse_result = parse_result->next;
	}
	if (cmd_index > 0)
	{
		if (last_exec(av, cmd_index, data) == 1)
		{
			perror("execute");
			return (1);
		}
	}
	if (data->infile != 0)
		close(data->infile);
	if (data->outfile != 1)
		close(data->outfile);
	return (0);
}
