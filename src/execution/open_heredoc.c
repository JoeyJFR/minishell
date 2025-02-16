#include "../../minishell.h"


void	open_heredoc(t_token *parse_result)
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
	}
}
