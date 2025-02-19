#include "../../minishell.h"

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
	t_type	tmp;

	tmp = token->type;
	if (token->next)
	{
		if (tmp == SR && token->next->next && token->next->next->type == SR)
			return (1);
		if (tmp == SR && token->next->next && token->next->next->type == DR)
			return (1);
		if (tmp == DR && token->next->next && token->next->next->type == SR)
			return (1);
		if (tmp == DR && token->next->next && token->next->next->type == DR)
			return (1);
		if (tmp == SL && token->next->next && token->next->next->type == SL)
			return (1);
		if (tmp == SL && token->next->next && token->next->next->type == DL)
			return (1);
		if (tmp == DL && token->next->next && token->next->next->type == SL)
			return (1);
		if (tmp == DL && token->next->next && token->next->next->type == DL)
			return (1);
	}
	return (0);
}

void	waitfree_get_error_code(t_data *data, t_alloc *alloc)
{
	int		i;
	int		status;

	i = 0;
	while (i < data->pid_nb)
		waitpid(data->pid[i++], &status, 0);
	if (data->pid)
		free(data->pid);
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	close_all_fd(data);
	exit_parsing("Error in execution", alloc, 1);
}
