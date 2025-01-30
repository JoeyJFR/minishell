#include "mini_exec.h"

static	int	loop_call(t_parse *parse_result, t_data *data, int fd[])
{
	char	*s;

	ft_putstr_fd("> ", STDOUT_FILENO);
	s = get_next_line(STDIN_FILENO);
	if (!s)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	if (!ft_strncmp(s, parse_result->str, ft_strlen(parse_result->str)) \
	&& s[ft_strlen(parse_result->str)] == '\n')
	{
		free(s);
		return (1);
	}
	ft_putstr_fd(s, fd[1]);
	free(s);
	return (1);
}

void	handle_heredoc(t_parse *parse_result, t_data *data)
{
	int		fd[2];
	int		result;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	while (1)
	{
		result = loop_call(parse_result, data, fd);
		if (result == 1)
			break ;
	}
	data->infile = fd[0];
	close(fd[1]);
}