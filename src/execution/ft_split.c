#include "../../minishell.h"

int	ft_seg(char const *s, char c)
{
	int	pos;
	int	i;

	pos = 0;
	i = 0;
	while (s[pos])
	{
		while (s[pos] == c)
			pos++;
		if (s[pos])
			i++;
		else
			return (i);
		while (s[pos] && (s[pos] != c))
			pos++;
	}
	return (i);
}

char	*ft_fill(char const *s, char c, int pos)
{
	int		l;
	int		j;
	char	*ptr;

	l = 0;
	while (s[pos + l] && (s[pos + l] != c))
		l++;
	ptr = (char *)malloc(sizeof(char) * (l + 1));
	if (!ptr)
		return (NULL);
	j = 0;
	while (j < l)
	{
		ptr[j] = s[pos + j];
		j++;
	}
	ptr[j] = '\0';
	return (ptr);
}

void	ft_clean(char **ptr, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(ptr[j]);
		ptr[j] = NULL;
		j++;
	}
}

int	ft_make(char const *s, char c, char **ptr, int seg)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (s[pos] && (s[pos] == c))
		pos++;
	while (i < seg)
	{
		ptr[i] = ft_fill(s, c, pos);
		if (ptr[i] == NULL)
		{
			ft_clean(ptr, i);
			return (1);
		}
		while (s[pos] && (s[pos] != c))
			pos++;
		while (s[pos] && (s[pos]) == c)
			pos++;
		i++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	int		seg;
	int		flag;
	char	**ptr;	

	seg = ft_seg(s, c);
	ptr = (char **)malloc(sizeof(char *) * (seg + 1));
	if (!ptr)
		return (NULL);
	flag = ft_make(s, c, ptr, seg);
	if (flag)
	{
		free (ptr);
		ptr = NULL;
		return (ptr);
	}
	ptr[seg] = NULL;
	return (ptr);
}
