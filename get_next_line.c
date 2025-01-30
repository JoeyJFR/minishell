/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjiang <zjiang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 10:48:12 by zjiang            #+#    #+#             */
/*   Updated: 2025/01/06 08:43:28 by zjiang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_link(int fd, char	**lines, char **temp, int *char_read)
{
	*char_read = read(fd, *temp, BUFFER_SIZE);
	if (*char_read == -1 || (*char_read == 0 && (*lines)[0] == '\0'))
	{
		free(*temp);
		*temp = NULL;
		free(*lines);
		return (NULL);
	}
	(*temp)[*char_read] = '\0';
	*lines = ft_strjoin_gnl(lines, temp);
	if (!(*lines))
		return (NULL);
	return (*lines);
}

char	*make_string(int fd, char **lines, char start[])
{
	int		char_read;
	char	*temp;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
	{
		free(*lines);
		return (NULL);
	}
	char_read = 1;
	while (char_read > 0)
	{
		*lines = ft_link(fd, lines, &temp, &char_read);
		if (!(*lines))
		{
			if (char_read == -1)
				start[0] = '\0';
			return (NULL);
		}
		if (check_end(temp))
			break ;
	}
	free(temp);
	temp = NULL;
	return (*lines);
}

char	*read_file(int fd, char start[])
{
	char	*lines;
	int		i;

	lines = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!lines)
		return (NULL);
	i = 0;
	while (start[i])
	{
		lines[i] = start[i];
		i++;
	}
	lines[i] = '\0';
	i = 0;
	while (lines[i])
	{
		if (lines[i] == '\n')
			return (lines);
		i++;
	}
	lines = make_string(fd, &lines, start);
	if (!lines)
		return (NULL);
	return (lines);
}

char	*make_next_line(char *lines)
{
	int		i;
	int		j;
	char	*nl;

	i = 0;
	while (lines[i] && lines[i] != '\n')
		i++;
	if (lines[i] == '\n')
		i++;
	nl = (char *)malloc((i + 1) * sizeof(char));
	if (!nl)
		return (NULL);
	j = 0;
	i = 0;
	while (lines[i] && lines[i] != '\n')
		nl[j++] = lines[i++];
	if (lines[i] == '\n')
		nl[j++] = '\n';
	nl[j] = '\0';
	return (nl);
}

char	*get_next_line(int fd)
{
	static char	start[BUFFER_SIZE + 1];
	char		*lines;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		start[0] = '\0';
		return (NULL);
	}
	lines = read_file(fd, start);
	if (!lines)
		return (NULL);
	next_line = make_next_line(lines);
	if (!next_line)
	{
		free(lines);
		lines = NULL;
		return (NULL);
	}
	new_start(start, lines);
	free(lines);
	lines = NULL;
	return (next_line);
}
