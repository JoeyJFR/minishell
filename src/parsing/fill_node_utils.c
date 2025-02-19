#include "../../minishell.h"


static int	ope_condition(char c, char *result, int in_quote, int x)
{
	if (!x)
		return (1);
	if (!c)
		return (1);
	if ((c == ' ' || !is_ope(c, result)) && !in_quote)
		return (1);
	return (0);
}

static int	word_condition(char c, char *result, int in_quote, int x)
{
	if (x)
		return (1);
	if (!c)
		return (1);
	if ((c == ' ' || is_ope(c, result)) && !in_quote)
		return (1);
	return (0);
}

char	*fill_str(char **buf, char *result, int x)
{
	int	in_quote;
	int	i;

	in_quote = 0;
	i = 0;
	while (!word_condition(**buf, result, in_quote, x) \
		||  !ope_condition(**buf, result, in_quote, x))
	{
		if (update_quote_var(&in_quote, buf))
			continue ;
		result[i++] = *(*buf)++;
	}
	result[i] = '\0';
	return (result);
}
/* 
char	*fill_ope(char **buf, char *result)
{
	int		i_d;
	int		i_s;
	int		j;

	i_d = 1;
	i_s = 1;
	j = 0;
	while (**buf && ((**buf != ' ' && is_ope(**buf, result)) || !i_d || !i_s))
	{
		if (**buf == '\"' && (i_s % 2) && --i_d == 1)
			i_d += 2;
		else if (**buf == '\'' && (i_d % 2) && --i_s == 1)
			i_s += 2;
		if ((i_s && !i_d && **buf != '\"')
			|| (i_d && !i_s && **buf != '\'')
			|| (i_d && i_s && **buf != '\'' && **buf != '\"'))
			result[j++] = **buf;
		++(*buf);
	}
	result[j] = '\0';
	return (result);
}
 */
