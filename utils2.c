#include "mini_exec.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_parse(t_parse *p)
{
	t_parse	*temp;

	temp = p;
	while (p)
	{
		temp = p->next;
		free(p->str);
		free (p);
		p = temp;
	}
}

int	wait_dup_free(t_data *data, t_parse *parse_result)
{
	int		i;

	i = 0;
	while (i < data->pid_nb)
		waitpid(data->pid[i++], NULL, 0);
	if (dup2(data->stdin_backup, STDIN_FILENO) == -1)
	{
		perror("dup2 in stdin backup");
		free_parse(parse_result);
		free(data->pid);
		return (get_error_code());
	}
	if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("dup2 in stdout backup");
		free_parse(parse_result);
		free(data->pid);
		return (get_error_code());
	}
	free(data->pid);
	free_parse(parse_result);
	close(data->stdin_backup);
	close(data->stdout_backup);
	return (0);
}

int	get_error_code(void)
{
	int	error_code;

	error_code = errno;
	return (error_code);
}

void	handle_execve_fail(t_data *data, char *path)
{
	perror("execve failed");
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	free(data->pid);
	if (path)
		free(path);
	exit (127);
}
