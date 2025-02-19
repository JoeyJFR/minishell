#include "../../minishell.h"

int	sr(t_token **parse_result, t_data *data)
{
	if (data->no_permission == 1)
		return (0);
	(*parse_result) = (*parse_result)->next;
	data->outfile = open((*parse_result)->str, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		perror("open in sr");
		data->no_permission = 1;
		return (0);
	}
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	return (0);
}

int	dr(t_token **parse_result, t_data *data)
{
	if (data->no_permission == 1)
		return (0);
	(*parse_result) = (*parse_result)->next;
	data->outfile = open((*parse_result)->str, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->outfile == -1)
	{
		perror("open in dr");
		data->no_permission = 1;
		return (0);
	}
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	return (0);
}

int	sl(t_token **parse_result, t_data *data)
{
	if (data->no_permission == 1)
		return (0);
	(*parse_result) = (*parse_result)->next;
	data->infile = open((*parse_result)->str, O_RDONLY);
	if (data->infile == -1)
	{
		perror("open in sl");
		data->no_permission = 1;
		return (0);
	}
	dup2(data->infile, STDIN_FILENO);
	close(data->infile);
	return (0);
}

int	dl(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	if (handle_heredoc(*parse_result, data))
		return (1);
	else
		return (0);
}

int	redirect_file(t_data *data, t_token **parse_result)
{
	if ((*parse_result)->type == SR)
		return (sr(parse_result, data));
	else if ((*parse_result)->type == DR)
		return (dr(parse_result, data));
	else if ((*parse_result)->type == SL)
		return (sl(parse_result, data));
	else
		return (dl(parse_result, data));
}
