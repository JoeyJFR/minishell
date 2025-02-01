#include "mini_exec.h"

int	exec(t_parse *parse_result, t_data *data)
{
	char	*av[100];//2097153
	int		cmd_index;
	int		result;
	int		fd[2];

	cmd_index = 0;
	data->infile = 0;
	data->outfile = 1;
	av[cmd_index] = NULL;

	while (parse_result)
	{
		if (parse_result->type == ARG)
			av[cmd_index++] = parse_result->str;
		else if (parse_result->type == SL || parse_result->type == DL || parse_result->type == SR || parse_result->type == DR)
			ft_ope(&parse_result, data);
		else if (parse_result->type == PIPE)
		{
			av[cmd_index] = NULL;
			handle_pipe(av, data, fd);
			cmd_index = 0;
			close(fd[1]);
			data->infile = fd[0];
		}
		else if (parse_result->type == ABS_PATH)
			av[cmd_index++] = parse_result->str;
		else
			av[cmd_index++] = parse_result->str;
		parse_result = parse_result->next;
	}
	if (cmd_index > 0)
	{
		av[cmd_index] = NULL;
		exec_cmd(av, data);
		printf("last command runned\n");
	}
	if (data->infile != STDIN_FILENO)
        close(data->infile);
    if (data->outfile != STDOUT_FILENO)
        close(data->outfile);
	return (0);
}
