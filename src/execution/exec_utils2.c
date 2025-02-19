#include "../../minishell.h"

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

void	closeall_exit(t_data *data, t_alloc *alloc, char *s)
{
	close_all_fd(data);
	exit_parsing(s, alloc, 1);
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
	if (data->stdin_backup != STDIN_FILENO \
		&& dup2(data->stdin_backup, STDIN_FILENO) == -1)
		closeall_exit(data, alloc, "dup2 for stdin");
	if (data->stdout_backup != STDOUT_FILENO \
		&& dup2(data->stdout_backup, STDOUT_FILENO) == -1)
		closeall_exit(data, alloc, "dup2 for stdout");
	if (data->no_permission)
		alloc->exit_status = 1;
	close_all_fd(data);
}

int	get_error_code(void)
{
	int	error_code;

	error_code = errno;
	return (error_code);
}
