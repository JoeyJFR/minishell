#include "mini_exec.h"
// after the ope, need to redirect them using dup2()
void	sl(t_parse **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	{
		if (*parse_result && (*parse_result)->type == ARG)
		{
			data->infile = open((*parse_result)->str, O_RDONLY);
			if (data->infile == -1)
				perror("open");
		}
	}
}

void	dl(t_parse **parse_result, t_data *data, char *av[])
{
	(*parse_result) = (*parse_result)->next;
	{
		if (*parse_result && (*parse_result)->type == ARG)
			handle_heredoc(*parse_result, data);
		if (dup2(data->infile, STDIN_FILENO) == -1)
			perror("dup2");
		close(data->infile);
	}
}

void	sr(t_parse **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	{
		if (*parse_result && (*parse_result)->type == ARG)
		{
			data->outfile = open((*parse_result)->str, \
					O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (data->outfile == -1)
				perror("open");
		}
	}
}

void	dr(t_parse **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	{
		if (*parse_result && (*parse_result)->type == ARG)
		{
			data->outfile = open((*parse_result)->str, \
					O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (data->outfile == -1)
				perror("open");
		}
	}
}

int	ft_ope(t_parse **parse_result, t_data *data, char *av[], int cmd_index)
{
	if ((*parse_result)->type == SR)
		sr(parse_result, data);
	else if ((*parse_result)->type == DR)
		dr(parse_result, data);
	else if ((*parse_result)->type == SL)
		sl(parse_result, data);
	else if ((*parse_result)->type == DL)
	{
		av[cmd_index] = NULL;
		dl(parse_result, data, av);
	}
	return (1);
}
