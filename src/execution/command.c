#include "../../minishell.h"

void	check_rel_arg(char	*s, t_data *data, t_alloc *alloc)
{
	int	i;

	i = 1;
	if (!s[i])
		handle_rel_sfail(data, "Error: filename required\n", alloc);
	while (s[i])
	{
		if (s[i] != '.')
			return ;
		i++;
	}
	handle_rel_fail(data, NULL, "Error: no argument\n", alloc);
}

void	relative_path(char *cmd, char *av[], t_data *data, t_alloc *alloc)
{
	char	*cwd;
	char	*full_path;

	check_rel_arg(av[0], data, alloc);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
		handle_execve_fail(data, NULL, "getcwd failed", alloc);
	full_path = malloc(ft_strlen(cwd) + ft_strlen(cmd) + 2);
	if (full_path == NULL)
	{
		free(cwd);
		handle_execve_fail(data, NULL, "malloc failed for full path", alloc);
	}
	ft_strcpy(full_path, cwd);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, cmd);
	free(cwd);
	if (execve(full_path, av, data->env) == -1)
	{
		if (errno == ENOENT)
			handle_execve_fail(data, full_path, "Error", alloc);
		else
			handle_directory_fail(data, full_path, \
			"Permission denied\n", alloc);
	}
}

void	absolute_path(char *av[], t_data *data, t_alloc *alloc)
{
	struct stat	buff;

	if (stat(av[0], &buff) == 0)
	{
		if (execve(av[0], av, data->env) == -1)
			handle_directory_fail(data, NULL, "Error: Is a directory\n", alloc);
	}
	if (execve(av[0], av, data->env) == -1)
		handle_execve_fail(data, NULL, "exec failed", alloc);
}

void	exec_cmd(char *av[], t_data *data, t_alloc *alloc)
{
	char		*path;
	int			flag;

	close_all_fd(data);
	free(data->pid);
	data->pid = NULL;
	rl_clear_history();
	if (av[0] && av[0][0] == '/')
		absolute_path(av, data, alloc);
	else if (av[0] && check_built(av[0]))
	{
		flag = built_in(av, data, alloc);
		free_alloc_pid(alloc, data);
		exit (flag);
	}
	else if (av[0] && av[0][0] == '.')
		relative_path(av[0], av, data, alloc);
	else if (av[0])
	{
		path = find_path(av[0], data->env, data, alloc);
		if (!path)
			handle_execve_fail(data, path, "no path", alloc);
		if (execve(path, av, data->env) == -1)
			handle_execve_fail(data, path, "exec failed", alloc);
	}
}
