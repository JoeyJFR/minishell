#include "../../minishell.h"

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

int	len_word(char *s)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (*s)
	{
		if (update_quote_var(&in_quote, &s))
			continue ;
		if (*s == ' ' && !in_quote)
			break ;
		++i;
		++s;
	}
	return (i);
}

int	update_quote_var(int *in_quote, char **c)
{
	int	var;

	var = 0;
	if (*in_quote == 2 && **c == '"' && ++var)
		*in_quote = 0;
	else if (*in_quote == 1 && **c == '\'' && ++var)
		*in_quote = 0;
	else if (*in_quote == 0 && **c == '"' && ++var)
		*in_quote = 2;	
	else if (*in_quote == 0 && **c == '\'' && ++var)
		*in_quote = 1;	
	if (!var)
		return (0);
	++(*c);
	return (1);
}
