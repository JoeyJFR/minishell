#include "../../minishell.h"

int	check_env(t_env *env_head)
{
	while (env_head)
	{
		if (!ft_strncmp(env_head->str, "PATH=", 5) && env_head->str[6])
			return (0);
		env_head = env_head->next;
	}
	return (1);
}

int	count_pid(t_parse *parse_result)
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

void	ft_putstr_fd(char *s, int fd)
{
	size_t	l;

	if (!s || !fd)
		return ;
	l = ft_strlen(s);
	write(fd, s, l);
}

void	reform_env(t_env *env, char *environ[])
{
	int		i;
	t_env	*temp;

	temp = env;
	i = 0;
	while (temp)
	{
		environ[i] = temp->str;
		i++;
		temp = temp->next;
	}
	environ[i] = NULL;
}

void	handle_execve_fail(t_data *data, char *path, t_env *env_head)
{
	perror("execve failed");
	if (STDIN_FILENO != 0)
		close(STDIN_FILENO);
	if (STDOUT_FILENO != 1)
		close(STDOUT_FILENO);
	free(data->pid);
	if (path)
		free(path);
	free_env(env_head);
	free_parse(data->p_head);
	exit (127);
}

int	wait_dup_free(t_data *data, t_env *env_head)
{
	int		i;

	i = 0;
	while (i < data->pid_nb)
		waitpid(data->pid[i++], NULL, 0);
	if (data->pid)
		free(data->pid);
	if (data->p_head)
		free_parse(data->p_head);
	if (env_head)
		free_env(env_head);
	return (0);
}

int	get_error_code(void)
{
	int	error_code;

	error_code = errno;
	return (error_code);
}
