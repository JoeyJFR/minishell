#include "mini_exec.h"

static int	exec_init(int *cmd_index, t_data *data, char *av[], t_parse *parse_result)
{
	*cmd_index = 0;
	av[0] = NULL;
	data->pid_nb = 0;
	data->stdin_backup = dup(STDIN_FILENO);
	data->open_in_fail = 0;
	data->open_out_fail = 0;
	if (data->stdin_backup < 0)
		return (perror("dup"), 1);
	data->stdout_backup = dup(STDOUT_FILENO);
	if (data->stdout_backup < 0)
		return (perror("dup"), 1);
	data->pid_nb = count_pid(parse_result);
	data->pid = malloc((sizeof(pid_t) * data->pid_nb));
	if (!data->pid)
		return (perror("malloc"), 1);
	return (0);
}

static int	mid_exec(t_parse **p_result, int *cmd_i, char *av[], t_data *data)
{
	if ((*p_result)->type == ARG)
		av[(*cmd_i)++] = (*p_result)->str;
	else if ((*p_result)->type == SL || (*p_result)->type == DL \
			|| (*p_result)->type == SR || (*p_result)->type == DR)
	{
		if (data->open_in_fail)
			return (0);
		if (ft_ope(p_result, data, av, *cmd_i))
			return (1);
		return (0);
	}
	else if ((*p_result)->type == PIPE)
	{
		av[*cmd_i] = NULL;
		handle_pipe(av, data);
		*cmd_i = 0;
	}
	else if ((*p_result)->type == ABS_PATH)
		av[(*cmd_i)++] = (*p_result)->str;
	else
		av[(*cmd_i)++] = (*p_result)->str;
	return (0);
}

static int	last_exec(char *av[], int cmd_index, t_data *data)
{
	pid_t	pid;

	if (data->open_in_fail || data->open_out_fail)
		return (0);
	av[cmd_index] = NULL;
	pid = fork();
	if (pid == 0)
	{
		if (exec_cmd(av, data) == -1)
		{
			perror("execute");
			return (1);
		}
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	(data->pid)[data->pid_nb++] = pid;
	return (0);
}

int	exec(t_parse *parse_result, t_data *data)
{
	char	*av[BUFFER_SIZE];
	int		cmd_index;

	if (exec_init(&cmd_index, data, av, parse_result))
		return (-1);
	while (parse_result)
	{
		if (mid_exec(&parse_result, &cmd_index, av, data))
			return (-1);
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
	return (wait_dup_free(data));
}
