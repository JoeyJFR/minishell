#include "../../minishell.h"

static int	exec_init(t_data *data, t_token *token, t_env *env)
{
	data->pid_nb = count_pid(token);
	data->cmd_i = 0;
	data->open_in_fail = 0;
	data->open_out_fail = 0;
	data->pid = malloc((sizeof(pid_t) * data->pid_nb));
	data->infile = -1;
	data->outfile = -2;
	if (!data->pid)
		return (perror("malloc for pid_nb"), 1);
	data->pid_nb = 0;
	data->stdout_backup = dup(STDOUT_FILENO);
	if (data->stdout_backup == -1)
		return (perror("dup for stdout_backup"), 1);
	data->stdin_backup = dup(STDIN_FILENO);
	if (data->stdin_backup == -1)
		return (perror("dup for stdin_backup"), 1);
	reform_env(env, data->env);
	return (0);
}

static int	last_exec(char *av[], t_data *data, t_alloc *alloc)
{
	pid_t	pid;

	if (data->open_in_fail || data->open_out_fail)
		return (0);
	pid = fork();
	if (pid == -1)
		return (perror("fork in last exec"), 1);
	if (pid == 0)
		exec_cmd(av, data, alloc);
	else
	{
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		(data->pid)[data->pid_nb++] = pid;
	}
	return (0);
}

int	parse_token(t_data *data, t_token **token, char *av[], t_alloc *alloc)
{
	if ((*token)->type == ARG)
		av[(data->cmd_i)++] = (*token)->str;
	else if ((*token)->type == ABS)
		av[(data->cmd_i)++] = (*token)->str;
	else if (check_ope(*token))
	{
		if (check_inter_ope(*token))
			open_file(data, token);
		else
		{
			if (redirect_file(data, token))
				return (1);
		}
	}
	else if ((*token)->type == PI)
	{
		av[data->cmd_i] = NULL;
		data->cmd_i = 0;
		if (handle_pipe(*token, av, data, alloc))
			return (1);
	}
	else
		av[(data->cmd_i)++] = (*token)->str;
	return (0);
}

int	exec(t_alloc *alloc, t_env *env, t_token *token)
{
	char	*av[BUFFER_SIZE];
	t_data	data;

	av[0] = NULL;
	if (exec_init(&data, token, env))
	{
		if (data.pid)
			free(data.pid);
		return (close(data.stdin_backup), close(data.stdout_backup), get_error_code());
	}
	while (token)
	{
		if (parse_token(&data, &token, av, alloc))
			return (wait_free(&data, alloc), get_error_code());
		token = token->next;
	}
	if (data.cmd_i > 0)
	{
		av[data.cmd_i] = NULL;
		if (check_only_builtin(av, alloc))
		{
			alloc->exit_status = built_in(av, &data, alloc);
			wait_free(&data, alloc);
			return (alloc->exit_status);
		}
		else
		{
			if (last_exec(av, &data, alloc))
			{
				wait_free(&data, alloc);
				return (get_error_code());
			}
		}
	}
	wait_free(&data, alloc);
	return (alloc->exit_status);
}
