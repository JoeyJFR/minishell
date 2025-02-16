#include "../../minishell.h"

static	char	*ft_strjoin1(char const *s1, char const *s2)
{
	size_t		i;
	int			j;
	char		*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc((i + 2) * sizeof(char));
	if (!ptr)
		return (perror("malloc in strjoin1"), NULL);
	i = 0;
	j = 0;
	while (s1[i])
		ptr[j++] = s1[i++];
	ptr[j++] = '/';
	i = 0;
	while (s2[i])
		ptr[j++] = s2[i++];
	ptr[j] = '\0';
	return (ptr);
}

static	void	ft_free_path(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static	char	*find_path(char *cmd, char *env[])
{
	int		i;
	char	**env_paths;
	char	*cmd_to_exec;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	env_paths = ft_split(env[i] + 5, ':');
	if (!env_paths)
		return (perror("fail to split env"), NULL);
	i = -1;
	while (env_paths[++i])
	{
		cmd_to_exec = ft_strjoin1(env_paths[i], cmd);
		if (!cmd_to_exec)
		{
			ft_free_path(env_paths);
			return (NULL);
		}
		if (access(cmd_to_exec, X_OK) == 0)
			return (ft_free_path(env_paths), cmd_to_exec);
		free(cmd_to_exec);
	}
	ft_free_path(env_paths);
	return (NULL);
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

void	exec_cmd(char *av[], t_data *data, t_alloc *alloc)
{
	char	*path;

	if (av[0][0] == '/')
	{
		close_all_fd(data);
		if (execve(av[0], av, data->env) == -1)
			handle_execve_fail(data, NULL);
	}
	else if (check_built(av[0]))
	{
		close_all_fd(data);
		exit (built_in(av, data, alloc));
	}
	else
	{
		close_all_fd(data);
		path = find_path(av[0], data->env);
		if (execve(path, av, data->env) == -1)
			handle_execve_fail(data, path);
	}
	return ;
}
