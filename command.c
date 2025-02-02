#include "mini_exec.h"

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
		return (NULL);
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

static	void	ft_free(char **s)
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
		return (NULL);
	i = -1;
	while (env_paths[++i])
	{
		cmd_to_exec = ft_strjoin1(env_paths[i], cmd);
		if (!cmd_to_exec)
		{
			ft_free(env_paths);
			return (NULL);
		}
		if (access(cmd_to_exec, X_OK) == 0)
			return (ft_free(env_paths), cmd_to_exec);
		free(cmd_to_exec);
	}
	ft_free(env_paths);
	return (NULL);
}

// static	void	free_cmd(t_data *data, char *path, char **args)
// {
// 	int	i;

// 	if (data->pipe_fds)
// 		free(data->pipe_fds);
// 	if (data->pid)
// 		free(data->pid);
// 	if (path)
// 		free(path);
// 	i = 0;
// 	if (args)
// 	{
// 		while (args[i])
// 		{
// 			free(args[i]);
// 			i++;
// 		}
// 		free(args);
// 	}
// }

int	check_built(char *s)
{
	if (!ft_strcmp(s, "echo"))
		return (1);
	else if (!ft_strcmp(s, "cd"))
		return (1);
	else if (!ft_strcmp(s, "pwd"))
		return (1);
	else if (!ft_strcmp(s, "export"))
		return (1);
	else if (!ft_strcmp(s, "unset"))
		return (1);
	else if (!ft_strcmp(s, "env"))
		return (1);
	else if (!ft_strcmp(s, "exit"))
		return (1);
	return (0);
}

int	exec_cmd(char *av[], t_data *data)
{
	char	*path;

	if (av[0][0] == '/')
		execve(av[0], av, data->env);
	// else if (check_built(av[0]))
	// 	ft_built(av, data);
	else
	{
		path = find_path(av[0], data->env);
		if (execve(path, av, data->env) == -1)
		{
			perror("execve failed");
			if (data->infile != STDIN_FILENO)
				close(data->infile);
			if (data->outfile != STDOUT_FILENO)
				close(data->outfile);
			exit (127);
		}
	}
	return (-1);
}
