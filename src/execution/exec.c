#include "../../minishell.h"

static int	exec_init(t_data *data, t_token *token, t_env *env)
{
	data->pid_nb = count_pid(token);
	data->cmd_i = 0;
	data->infile = -1;
	data->outfile = -2;
	data->no_permission = 0;
	(data->av)[0] = NULL;
	data->pid = malloc((sizeof(pid_t) * data->pid_nb));
	if (!data->pid)
	{
		write(STDERR_FILENO, "Error: malloc for pid_nb\n", 26);
		return (1);
	}
	data->pid_nb = 0;
	data->stdout_backup = dup(STDOUT_FILENO);
	data->stdin_backup = dup(STDIN_FILENO);
	reform_env(env, data->env);
	return (0);
}

static int	last_exec(char *av[], t_data *data, t_alloc *alloc)
{
	pid_t	pid;

	if (data->no_permission)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		perror("fork in last exec");
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		exec_cmd(av, data, alloc);
	}
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
	t_data	data;

	if (exec_init(&data, token, env))
		exit_parsing(NULL, alloc, 1);
	while (token)
	{
		if (parse_token(&data, &token, data.av, alloc))
			waitfree_get_error_code(&data, alloc);
		token = token->next;
	}
	if (data.cmd_i > 0)
	{
		(data.av)[data.cmd_i] = NULL;
		if (check_only_builtin(data.av, alloc))
		{
			alloc->exit_status = built_in(data.av, &data, alloc);
			wait_free(&data, alloc);
			return (alloc->exit_status);
		}
		else if (last_exec(data.av, &data, alloc))
			waitfree_get_error_code(&data, alloc);
	}
	wait_free(&data, alloc);
	return (alloc->exit_status);
}
