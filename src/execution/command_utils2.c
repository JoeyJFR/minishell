#include "../../minishell.h"

char	*ft_strjoin1(char const *s1, char const *s2)
{
	size_t		i;
	int			j;
	char		*ptr;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2);
	ptr = ft_calloc(sizeof(char), i + 2);
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
	return (ptr);
}

int	build_path(char **cmd_to_exec, char **env_paths, char *cmd, int i)
{
	*cmd_to_exec = ft_strjoin1(env_paths[i], cmd);
	if (!(*cmd_to_exec))
		return (2);
	if (access(*cmd_to_exec, X_OK) == 0)
		return (1);
	free(*cmd_to_exec);
	return (0);
}

void	ft_free_path(char **s)
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

char	*check_exec_path(char **paths, char *cmd, t_data *data, t_alloc *alloc)
{
	int		i;
	int		flag;
	char	*cmd_to_exec;

	i = -1;
	while (paths[++i])
	{
		flag = build_path(&cmd_to_exec, paths, cmd, i);
		if (flag == 1)
		{
			ft_free_path(paths);
			return (cmd_to_exec);
		}
		if (flag == 2)
		{
			ft_free_path(paths);
			handle_execve_fail(data, NULL, "strjoint1 failed", alloc);
		}
	}
	ft_free_path(paths);
	return (NULL);
}

char	*find_path(char *cmd, char *env[], t_data *data, t_alloc *alloc)
{
	int		i;
	char	**env_paths;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return (NULL);
	env_paths = ft_split(env[i] + 5, ':');
	if (!env_paths)
	{
		perror("fail to split env");
		return (NULL);
	}
	return (check_exec_path(env_paths, cmd, data, alloc));
}
