/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: v <v@student.42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 08:23:25 by vgarcia           #+#    #+#             */
/*   Updated: 2025/02/04 10:48:52y v                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	len_word(char *s, char c)
{
	int	i;
	int	index_d;
	int	index_s;

	i = 0;
	index_s = 1;
	index_d = 1;
	while (*s)
	{
		if (*s == '\"' && index_d == 1 && (index_s % 2))
			--index_d;
		else if (*s == '\"' && index_d == 0 && (index_s % 2))
			++index_d;
		else if (*s == 39 && index_s == 1 && (index_d % 2))
			--index_s;
		else if (*s == 39 && index_s == 0 && (index_d % 2))
			++index_s;
		if (*s == c && index_s && index_d)
			break ;
		i++;
		s++;
	}
	return (i);
}

char	*fill_str(char **str, char c, char *result)
{
	int		index_d;
	int		index_s;
	int		j;

	index_d = 1;
	index_s = 1;
	j = 0;
	while (**str && (**str != c || !index_d || !index_s))
	{
		if (**str == 39 && index_s == 1 && (index_d % 2))
			--index_s;
		else if (**str == 39 && index_s == 0 && (index_d % 2))
			++index_s;
		else if (**str == '\"' && index_d == 1 && (index_s % 2))
			--index_d;
		else if (**str == '\"' && index_d == 0 && (index_s % 2))
			++index_d;
		if ((index_s && !index_d && **str != '\"')
			|| (index_d && !index_s && **str != '\'')
			|| (index_d && index_s && **str != '\'' && **str != '\"'))
			result[j++] = **str;
		++(*str);
	}
	result[j] = '\0';
	return (result);
}
