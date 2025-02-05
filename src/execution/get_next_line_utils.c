#include "../../minishell.h"

static int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	check_end(char *temp)
{
	int	i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		return (1);
	if (i < BUFFER_SIZE)
		return (1);
	return (0);
}

char	*ft_strjoin_gnl(char **head, char **end)
{
	int		l;
	int		i;
	int		j;
	char	*new_line;

	l = ft_strlen_gnl(*head) + ft_strlen_gnl(*end) + 1;
	new_line = (char *)malloc(l * sizeof(char));
	if (!new_line)
	{
		free(*head);
		free(*end);
		*end = NULL;
		return (NULL);
	}
	i = 0;
	j = 0;
	while ((*head)[i])
		new_line[j++] = (*head)[i++];
	i = 0;
	while ((*end)[i])
		new_line[j++] = (*end)[i++];
	new_line[j] = '\0';
	free(*head);
	return (new_line);
}

void	new_start(char start[], char *lines)
{
	int	i;
	int	j;

	i = 0;
	while (lines[i] && lines[i] != '\n')
		i++;
	if (lines[i] == '\n')
		i++;
	j = 0;
	while (lines[i])
		start[j++] = lines[i++];
	start[j] = '\0';
}
