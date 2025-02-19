#include "../../minishell.h"

t_env	*env_lstnew_export(char *str)
{
	t_env	*new_list;

	if (!str)
		return (NULL);
	new_list = malloc(sizeof(t_env));
	if (!new_list)
		return (NULL);
	new_list->str = ft_strdup(str);
	if (!new_list->str)
	{
		free(new_list);
		return (NULL);
	}
	new_list->next = NULL;
	return (new_list);
}

static void	add_var(t_env *env, char *str, t_alloc *alloc, t_data *data)
{
	t_env	*new_var;
	int		i_env;

	i_env = check_in_env(env, str);
	if (i_env >= 0)
	{
		if (change_var(env, str, i_env))
		{
			free(data->pid);
			close_all_fd(data);
			exit_parsing("Alloc", alloc, 1);
		}
	}
	else
	{
		new_var = env_lstnew_export(str);
		if (!new_var)
			exit_parsing("Alloc", alloc, 1);
		env_lstadd_back(&env, new_var);
	}
}

int	mini_export(char *av[], t_alloc *alloc, t_data *data)
{
	int		i;
	t_env	*temp;

	i = 0;
	temp = alloc->env_head;
	if (av[1] == NULL)
		return (ascii_env(temp, alloc, data), 0);
	if (av[1][0] == '-')
	{
		print_error("mini_export takes no option\n");
		return (1);
	}
	while (av[1 + i])
	{
		if (check_name(av[1 + i]))
		{
			print_error("Invalid identifier");
			return (1);
		}
		if (check_def(av[1 + i]))
			return (1);
		add_var(temp, av[1 + i], alloc, data);
		i++;
	}
	return (0);
}
