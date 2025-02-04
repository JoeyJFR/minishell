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

//check arg, return 1 if it is cmd and 0 if it is not cmd, just arg
int	check_arg(char *arg, t_data *data)
{
	int		i;
	char	**env_paths;
	char	*cmd_to_exec;

	i = 0;
	while (ft_strncmp(data->env[i], "PATH=", 5) != 0)
		i++;
	env_paths = ft_split(data->env[i] + 5, ':');
	if (!env_paths)
		return (-1);
	i = -1;
	while (env_paths[++i])
	{
		cmd_to_exec = ft_strjoin1(env_paths[i], arg);
		if (!cmd_to_exec)
			return (ft_free(env_paths), -1);
		if (access(cmd_to_exec, X_OK) == 0)
		{
			ft_free(env_paths);
			data->cmd = arg;
			return (1);
		}
	}
	return (ft_free(env_paths), 0);
}
