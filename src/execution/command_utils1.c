#include "../../minishell.h"

void	close_all_fd(t_data *data)
{
	close(data->stdin_backup);
	close(data->stdout_backup);
}

void	handle_directory_fail(t_data *data, char *path, char *s, t_alloc *alloc)
{
	write(STDOUT_FILENO, s, ft_strlen(s));
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	if (path)
		free(path);
	close_all_fd(data);
	free_alloc_pid(alloc, data);
	rl_clear_history();
	exit (126);
}

void	handle_execve_fail(t_data *data, char *path, char *s, t_alloc *alloc)
{
	perror(s);
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	close_all_fd(data);
	free_alloc_pid(alloc, data);
	if (path)
		free(path);
	rl_clear_history();
	exit (127);
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

void	free_alloc_pid(t_alloc *alloc, t_data *data)
{
	free_env(alloc->env_head);
	alloc->env_head = NULL;
	free_token(alloc->token_head);
	alloc->token_head = NULL;
	free(data->pid);
	data->pid = NULL;
}
