#include "../../minishell.h"

static void	ft_sort_int_tab(char **tab, int size)
{
	int		i;
	int		temoin;
	char	*temp;

	temp = 0;
	temoin = 0;
	while (temoin != 1)
	{
		temoin = 1;
		i = 1;
		while (i < size - 1)
		{
			if (ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				temp = tab[i + 1];
				tab[i + 1] = tab[i];
				tab[i] = temp;
				temoin = 0;
			}
			i++;
		}
	}
}

static int	tab_len(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		++size;
		env = env->next;
	}
	return (size);
}

static char	**init_env_tab(t_env *env, int size, t_alloc *alloc, t_data *data)
{
	char	**tab;
	int		i;

	i = 0;
	(void)data;
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		exit_parsing("Alloc", alloc, 1);
	while (env)
	{
		tab[i] = ft_strdup(env->str);
		if (!tab[i])
		{
			free_tab(tab);
			exit_parsing("Alloc", alloc, 1);
		}
		env = env->next;
		++i;
	}
	tab[i] = NULL;
	return (tab);
}

static void	print_export(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		++i;
	write(1, "declare -x ", 11);
	if (str[i])
	{
		++i;
		write(1, str, i);
		write(1, "\"", 1);
		write(1, &str[i], ft_strlen(&str[i]));
		write(1, "\"", 1);
	}
	else
		write(1, str, i);
	write(1, "\n", 1);
}

void	ascii_env(t_env *env, t_alloc *alloc, t_data *data)
{
	int		i;
	int		size;
	char	**env_tab;

	i = 1;
	size = tab_len(env);
	env_tab = init_env_tab(env, size, alloc, data);
	while (env_tab[i] && i < size)
	{
		ft_sort_int_tab(env_tab, size);
		print_export(env_tab[i]);
		++i;
	}
	free_tab(env_tab);
}
