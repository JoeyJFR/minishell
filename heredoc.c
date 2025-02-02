#include "mini_exec.h"

static	int	loop_call(t_parse *parse_result, t_data *data, int fd[])
{
	char	*s;

	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		s = get_next_line(STDIN_FILENO);
		if (!s)
		{
			ft_putstr_fd("\n", STDOUT_FILENO);
			break ;
		}
		if (!ft_strncmp(s, parse_result->str, ft_strlen(parse_result->str)) \
		&& s[ft_strlen(parse_result->str)] == '\n')
		{
			free(s);
			break ;
		}
		ft_putstr_fd(s, fd[1]);
	}
	if (!s)
		free(s);
	return (0);
}

void	handle_heredoc(t_parse *parse_result, t_data *data)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return ;
	}
	loop_call(parse_result, data, fd);
	data->infile = fd[0];
	close(fd[1]);
}
