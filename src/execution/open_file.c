#include "../../minishell.h"

void	open_sr(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
	{
		data->outfile = open((*parse_result)->str, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (data->outfile == -1)
			perror("open in sr");
	}
	else
		perror("syntax error near '>'\n");
}

void	open_dr(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
	{
		data->outfile = open((*parse_result)->str, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (data->outfile == -1)
			perror("open in dr");
	}
	else
		perror("syntax error near '>>'\n");
}

void	open_sl(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
	{
		data->infile = open((*parse_result)->str, O_RDONLY);
		if (data->infile == -1)
			perror("open in sl");
	}
	else
		perror("syntax error near '<'\n");
}

void	open_dl(t_token **parse_result)
{
	(*parse_result) = (*parse_result)->next;
	if (*parse_result && (*parse_result)->type == ARG)
		open_heredoc(*parse_result);
	else
		perror("syntax error near '<<'\n");
}

void	open_file(t_data *data, t_token **token)
{
	if ((*token)->type == SR)
		open_sr(token, data);
	else if ((*token)->type == DR)
		open_dr(token, data);
	else if ((*token)->type == SL)
		open_sl(token, data);
	else
		open_dl(token);
}
