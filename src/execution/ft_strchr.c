#include "../../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (ptr[i])
	{
		if (ptr[i] == (char)c)
			return (&(ptr[i]));
		else
			i++;
	}
	if ((char)c == '\0')
		return (&(ptr[i]));
	else
		return (NULL);
}
