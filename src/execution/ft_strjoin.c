#include "../../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return (NULL);
	i = 0;
	while (*s1)
		s3[i++] = *s1++;
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		++j;
	}
	s3[i + j] = '\0';
	return (s3);
}
