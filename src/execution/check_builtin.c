#include "../../minishell.h"

int	built_in(char *av[], t_data *data, t_alloc *alloc)
{
	if (!ft_strcmp(av[0], "cd"))
		return (mini_cd(av, data, alloc));
	else if (!ft_strcmp(av[0], "exit"))
		return (mini_exit(av, alloc, data));
	else if (!ft_strcmp(av[0], "export"))
		return (mini_export(av, alloc, data));
	else if (!ft_strcmp(av[0], "unset"))
		return (mini_unset(alloc->env_head, av));
	else if (!ft_strcmp(av[0], "pwd"))
		return (mini_pwd(av));
	else if (!ft_strcmp(av[0], "env"))
		return (mini_env(alloc));
	else if (!ft_strcmp(av[0], "echo"))
		return (mini_echo(av, alloc, data));
	return (0);
}
