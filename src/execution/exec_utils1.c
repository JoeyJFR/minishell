#include "../../minishell.h"

int	check_path(t_env *env_head)
{
	while (env_head)
	{
		if (!ft_strncmp(env_head->str, "PATH=", 5) && env_head->str[6])
			return (0);
		env_head = env_head->next;
	}
	print_error("Env edited case");
	return (1);
}

int	count_pid(t_token *parse_result)
{
	int	i;

	i = 1;
	while (parse_result)
	{
		if (parse_result->type == PI)
			i++;
		parse_result = parse_result->next;
	}
	return (i);
}

void	reform_env(t_env *env, char *environ[])
{
	int	i;

	i = 0;
	while (env)
	{
		environ[i] = env->str;
		i++;
		env = env->next;
	}
	environ[i] = NULL;
}

void	handle_execve_fail(t_data *data, char *path)
{
	perror("execve failed");
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	if (data->pid)
		free(data->pid);
	if (path)
		free(path);
	exit (127);
}

void	wait_free(t_data *data, t_alloc *alloc)
{
	int		i;
	int		status;

	i = 0;
	while (i < data->pid_nb)
	{
		waitpid(data->pid[i++], &status, 0);
		if (WIFEXITED(status))
			alloc->exit_status = WEXITSTATUS(status);
		else
			alloc->exit_status = WTERMSIG(status) + 128;
	}
	if (data->pid)
		free(data->pid);
	if (data->stdin_backup != STDIN_FILENO)
	{
		if (dup2(data->stdin_backup, STDIN_FILENO) == -1)
			return (close(data->stdout_backup), close(data->stdin_backup), perror("dup2 for STDIN"));
	}
	if (data->stdout_backup != STDOUT_FILENO)
	{
		if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
			return (close(data->stdout_backup), close(data->stdin_backup), perror("dup2 for STDOUT"));
	}
	close_all_fd(data);
}

int	get_error_code(void)
{
	int	error_code;

	error_code = errno;
	return (error_code);
}

int	check_ope(t_token *token)
{
	if (token->type == SL)
		return (1);
	if (token->type == DL)
		return (1);
	if (token->type == SR)
		return (1);
	if (token->type == DR)
		return (1);
	return (0);
}

int	check_inter_ope(t_token *token)
{
	if (token->type == SR && token->next->next && token->next->next->type == SR)
		return (1);
	if (token->type == SR && token->next->next && token->next->next->type == DR)
		return (1);
	if (token->type == DR && token->next->next && token->next->next->type == SR)
		return (1);
	if (token->type == DR && token->next->next && token->next->next->type == DR)
		return (1);
	if (token->type == SL && token->next->next && token->next->next->type == SL)
		return (1);
	if (token->type == SL && token->next->next && token->next->next->type == DL)
		return (1);
	if (token->type == DL && token->next->next && token->next->next->type == SL)
		return (1);
	if (token->type == DL && token->next->next && token->next->next->type == DL)
		return (1);
	return (0);
}

void	close_all_fd(t_data *data)
{
	close(103);
	close(43);
	if (data->infile > 2)
		close(data->infile);
	if (data->outfile > 2)
		close(data->outfile);
	close(data->stdin_backup);
	close(data->stdout_backup);
}

int	check_only_builtin(char *av[], t_alloc *alloc)
{
	t_token	*temp;

	temp = alloc->token_head;
	if (check_built(av[0]))
	{
		while (temp)
		{
			if (temp->type == PI)
				return (0);
			else
				temp = temp->next;
		}
		return (1);
	}
	else
		return (0);
}

int	check_built(char *s)
{
	if (!ft_strcmp(s, "cd"))
		return (1);
	else if (!ft_strcmp(s, "echo"))
		return (1);
	else if (!ft_strcmp(s, "env"))
		return (1);
	else if (!ft_strcmp(s, "exit"))
		return (1);
	else if (!ft_strcmp(s, "export"))
		return (1);
	else if (!ft_strcmp(s, "pwd"))
		return (1);
	else if (!ft_strcmp(s, "unset"))
		return (1);
	return (0);
}
