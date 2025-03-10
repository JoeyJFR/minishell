#include "../../minishell.h"

static	void	loop_call(t_token *parse_result, int fd[])
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
		free(s);
	}
	return ;
}

int	handle_heredoc(t_token *parse_result, t_data *data)
{
	int		fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe in here_doc");
		return (1);
	}
	if (STDIN_FILENO != data->stdin_backup)
		dup2(data->stdin_backup, STDIN_FILENO);
	loop_call(parse_result, fd);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	return (0);
}
