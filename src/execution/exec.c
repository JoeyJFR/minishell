#include "../../minishell.h"

static int	exec_init(t_data *data, \
					char *av[], t_parse *parse_result)
{
	data->cmd_index = 0;
	av[0] = NULL;
	data->pid_nb = 0;
	data->open_in_fail = 0;
	data->open_out_fail = 0;
	data->pid_nb = count_pid(parse_result);
	data->pid = malloc((sizeof(pid_t) * data->pid_nb));
	if (!data->pid)
		return (perror("malloc for pid_nb"), 1);
	data->pid_nb = 0;
	return (0);
}

static int	mid_exec(t_parse **p_result, char *av[], t_data *data, t_env *env_head)
{
	if ((*p_result)->type == ARG)
		av[(data->cmd_index)++] = (*p_result)->str;
	else if ((*p_result)->type == SL || (*p_result)->type == DL \
			|| (*p_result)->type == SR || (*p_result)->type == DR)
	{
		if (data->open_in_fail)
			return (0);
		if (ft_ope(p_result, data, av, data->cmd_index))
			return (1);
		return (0);
	}
	else if ((*p_result)->type == PI)
	{
		av[data->cmd_index] = NULL;
		if (handle_pipe(av, data, env_head))
			return (1);
		data->cmd_index = 0;
	}
	else if ((*p_result)->type == ABS)
		av[(data->cmd_index)++] = (*p_result)->str;
	else
		av[(data->cmd_index)++] = (*p_result)->str;
	return (0);
}

static int	last_exec(char *av[], t_data *data, t_env *env_head)
{
	pid_t	pid;

	if (data->open_in_fail || data->open_out_fail)
		return (0);
	av[data->cmd_index] = NULL;
	pid = fork();
	if (pid == -1)
	{
		free(data->pid);
		free_env(env_head);
		free_parse(data->p_head);
		return (perror("fork in last exec"), 1);
	}
	if (pid == 0)
	{
		exec_cmd(av, data, env_head);
		return (0);
	}
	else
	{
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		(data->pid)[(data->pid_nb)++] = pid;
		return (0);
	}
}

int	exec(t_parse *parse_result, t_data *data, t_env *env_head)
{
	char	*av[BUFFER_SIZE];

	data->p_head = parse_result;
	if (exec_init(data, av, parse_result))
	{
		free_parse(parse_result);
		free_env(env_head);
		return (get_error_code());
	}
	while (parse_result)
	{
		if (mid_exec(&parse_result, av, data, env_head))
			return (free(data->pid), free_env(env_head), free_parse(data->p_head), get_error_code());
		parse_result = parse_result->next;
	}
	if (data->cmd_index > 0)
	{
		if (last_exec(av, data, env_head))
			return (get_error_code());
	}
	return (wait_dup_free(data, env_head));
}
