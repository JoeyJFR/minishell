#include "../../minishell.h"

/*
check if there is a quote unpaired and return the first's
*/
int	check_quotes(char *s)
{
	int	check_first;
	int	index_d;
	int	index_s;
	int	i;

	index_s = 0;
	index_d = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '\"' && !(index_s % 2) && ++index_d)
			check_first = i;
		if (s[i] == '\'' && !(index_d % 2) && ++index_s)
			check_first = i;
	}
	if ((index_s % 2) || (index_d % 2))
		return (check_first);
	return (-1);
}

/*
checks if the unpaired quote is a single
*/
int	is_in_squote(char *str)
{
	int	checker;

	checker = check_quotes(str);
	if (checker == -1)
		return (0);
	if (str[checker] == '\'')
		return (1);
	return (0);
}

/*
checks what is the current operator it is dealing with
*/
int	is_ope(char c, char *current)
{
	if (!current || !*current)
	{
		if (c == '<' || c == '>' || c == '|')
			return (1);
		return (0);
	}
	else if (*current == c && (c == '>' || c == '<') && !*(current + 1))
		return (1);
	else if (*current != '<' && *current != '>' \
		&& *current != '|' && (c == '<' || c == '>' || c == '|'))
		return (1);
	return (0);
}

/*
check the number of command
*/
int	count_cmd(t_token *token)
{
	int	i;

	i = 0;
	if (token)
		i = 1;
	while (token->prev)
	 	token = token->prev;
	while (token)
	{
		if (token->type == PI)
			++i;
		token = token->next;
	}
	return (i);
}
