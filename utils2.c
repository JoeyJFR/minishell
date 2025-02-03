#include "mini_exec.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	wait_dup_free(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->pid_nb)
		waitpid(data->pid[i++], NULL, 0);
	if (dup2(data->stdin_backup, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	if (dup2(data->stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		return (-1);
	}
	free(data->pid);
	return (0);
}