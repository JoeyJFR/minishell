#include "../../minishell.h"

//refaire fill_ope / fill_word
char	*fill_ope(char **str, char *result)
{
	int		index_d;
	int		index_s;
	int		j;

	index_d = 1;
	index_s = 1;
	j = 0;
	while (**str && ((**str != ' ' && is_ope(**str, result)) || !index_d || !index_s))
	{
		if (**str == '\"' && (index_s % 2) && --index_d == 1)
			index_d += 2;
		else if (**str == '\'' && (index_d % 2) && --index_s == 1)
			index_s += 2;
		if ((index_s && !index_d && **str != '\"')
			|| (index_d && !index_s && **str != '\'')
			|| (index_d && index_s && **str != '\'' && **str != '\"'))
			result[j++] = **str;
		++(*str);
	}
	result[j] = '\0';
	return (result);
}

char	*fill_word(char **str, char *result)
{
	int		index_d;
	int		index_s;
	int		j;

	index_d = 1;
	index_s = 1;
	j = 0;
	while (**str && ((**str != ' ' && !is_ope(**str, result)) || !index_d || !index_s))
	{
		if (**str == '\"' && (index_s % 2) && --index_d == 1)
			index_d += 2;
		else if (**str == '\'' && (index_d % 2) && --index_s == 1)
			index_s += 2;
		if ((index_s && !index_d && **str != '\"')
			|| (index_d && !index_s && **str != '\'')
			|| (index_d && index_s && **str != '\'' && **str != '\"'))
			result[j++] = **str;
		++(*str);
	}
	result[j] = '\0';
	return (result);
}

int	len_word(char *s)
{
	int	i;
	int	index_d;
	int	index_s;

	i = 0;
	index_s = 1;
	index_d = 1;
	while (*s)
	{
		if (*s == '\"' && (index_s % 2) && --index_d == 1)
			index_d += 2;
		else if (*s == '\'' && (index_d % 2) && --index_s == 1)
			index_s += 2;
		if (*s == ' ' && index_s && index_d)
			break ;
		++i;
		++s;
	}
	return (i);
}

void	define_type(t_token *node)
{
	if (node->str[0] == '/')
		node->type = ABS;
	else if (!ft_strcmp(node->str, "cd"))
		node->type = CD;
	else if (!ft_strcmp(node->str, "echo"))
		node->type = ECHO;
	else if (!ft_strcmp(node->str, "export"))
		node->type = EXPORT;
	else if (!ft_strcmp(node->str, "env"))
		node->type = ENV;
	else if (!ft_strcmp(node->str, "pwd"))
		node->type = PWD;
	else if (!ft_strcmp(node->str, "unset"))
		node->type = UNSET;
	else if (!ft_strcmp(node->str, "exit"))
		node->type = EXIT;
	else
		node->type = ARG;
}

void	define_ope(t_token *node)
{
	if (!ft_strcmp(node->str, "<<"))
		node->type = DL;
	else if (!ft_strcmp(node->str, ">>"))
		node->type = DR;
	else if (!ft_strcmp(node->str, "<"))
		node->type = SL;
	else if (!ft_strcmp(node->str, ">"))
		node->type = SR;
	else if (!ft_strcmp(node->str, "|"))
		node->type = PI;
}
