#include "../../minishell.h"

void	open_heredoc(t_token *parse_result, t_data *data)
{
	char	*s;

	if (STDIN_FILENO != data->stdin_backup)
		dup2(data->stdin_backup, STDIN_FILENO);
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
		free(s);
	}
}
