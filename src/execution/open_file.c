#include "../../minishell.h"

void	open_sr(t_token **parse_result, t_data *data)
{
	if (data->no_permission == 1)
		return ;
	(*parse_result) = (*parse_result)->next;
	data->outfile = open((*parse_result)->str, \
			O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (data->outfile == -1)
	{
		data->no_permission = 1;
		perror("open in sr");
	}
	close(data->outfile);
}

void	open_dr(t_token **parse_result, t_data *data)
{
	if (data->no_permission == 1)
		return ;
	(*parse_result) = (*parse_result)->next;
	data->outfile = open((*parse_result)->str, \
			O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (data->outfile == -1)
	{
		data->no_permission = 1;
		perror("open in dr");
	}
	close(data->outfile);
}

void	open_sl(t_token **parse_result, t_data *data)
{
	if (data->no_permission == 1)
		return ;
	(*parse_result) = (*parse_result)->next;
	data->infile = open((*parse_result)->str, O_RDONLY);
	if (data->infile == -1)
	{
		data->no_permission = 1;
		perror("open in sl");
	}
	close(data->infile);
}

void	open_dl(t_token **parse_result, t_data *data)
{
	(*parse_result) = (*parse_result)->next;
	open_heredoc(*parse_result, data);
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
		open_dl(token, data);
}
