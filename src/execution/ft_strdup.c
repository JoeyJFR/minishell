#include "../../minishell.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	int		slen;

	slen = 0;
	while (s[slen])
		++slen;
	result = malloc(sizeof(char) * slen + 1);
	if (result == NULL)
		return (NULL);
	slen = 0;
	while (*s)
		result[slen++] = *s++;
	result[slen] = '\0';
	return (result);
}
