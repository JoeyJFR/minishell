#include "../../minishell.h"

void	ft_built(char *av[], t_data *data, t_env *env_head)
{
	if (!ft_strcmp(av[0], "echo"))
		ft_echo(av);
	else if (!ft_strcmp(av[0], "pwd"))
		check_b_pwd(av);
	else if (!ft_strcmp(av[0], "env"))
		check_b_env(av, data);
	if (data->pid)
	{
		free(data->pid);
		data->pid = NULL;
	}
	if (env_head)
	{
		free_env(env_head);
		env_head = NULL;
	}
	if (data->p_head)
	{
		free_parse(data->p_head);
		data->p_head = NULL;
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
}
