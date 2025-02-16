#include "../../minishell.h"

int	sr(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
	{
		data->outfile = open((*parse_result)->str, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->outfile == -1)
		{
			perror("open in sr");
			data->open_out_fail = 1;
			return (0);
		}
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 in sr");
			close(data->outfile);
			return (1);
		}
		close(data->outfile);
		return (0);
	}
	else
		perror("syntax error near '>'\n");
	return (1);
}

int	dr(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
	{
		data->outfile = open((*parse_result)->str, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->outfile == -1)
		{
			perror("open in dr");
			data->open_out_fail = 1;
			return (0);
		}
		if (dup2(data->outfile, STDOUT_FILENO) == -1)
		{
			perror("dup2 in dr");
			close(data->outfile);
			return (1);
		}
		close(data->outfile);
		return (0);
	}
	else
		perror("syntax error near '>>'\n");
	return (1);
}

int	sl(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
	{
		data->infile = open((*parse_result)->str, O_RDONLY);
		if (data->infile == -1)
		{
			perror("open in sl");
			data->open_in_fail = 1;
			return (0);
		}
		if (dup2(data->infile, STDIN_FILENO) == -1)
		{
			perror("dup2 in sl");
			close(data->infile);
			return (1);
		}
		close(data->infile);
		return (0);
	}
	else
		perror("syntax error near '<'\n");
	return (1);
}

int	dl(t_token **parse_result)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
	{
		if (handle_heredoc(*parse_result))
			return (1);
		else
			return (0);
	}
	else
		perror("syntax error near '<<'\n");
	return (1);
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
		return (dl(parse_result));
}
