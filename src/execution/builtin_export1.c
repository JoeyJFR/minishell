#include "../../minishell.h"

int	ft_fill_envcpy(t_env *env_head, char *cpy[])
{
	int		i;
	int		j;

	i = 0;
	while (env_head)
	{
		j = 0;
		cpy[i] = malloc(sizeof(char) * (ft_strlen(env_head->str) + 1));
		if (!cpy[i])
		{
			while (--i >= 0)
				free(cpy[i]);
			free(cpy);
			return (1);
		}
		while (env_head->str[j])
		{
			cpy[i][j] = env_head->str[j];
			j++;
		}
		cpy[i][j] = '\0';
		env_head = env_head->next;
		i++;
	}
	return (0);
}

void	sort_cpy(char *cpy[], int n)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < n - 1)
	{
		j = 0;
		while (j < n - 1 - i)
		{
			if (ft_strcmp(cpy[j], cpy[j + 1]) > 0)
			{
				temp = cpy[j];
				cpy[j] = cpy[j + 1];
				cpy[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	free_env_cpy(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	ft_export(t_env *env_head)
{
	int		n;
	char	**env_cpy;
	char	*equal_sign;

	n = cal_env_nb(env_head);
	env_cpy = malloc(sizeof(char *) * (n + 1));
	if (!env_cpy)
		return (perror("failed to create env_cpy"));
	env_cpy[n] = NULL;
	if (ft_fill_envcpy(env_head, env_cpy))
		return (perror("fail to copy env"), free(env_cpy));
	sort_cpy(env_cpy, n);
	n = -1;
	while (env_cpy[++n])
	{
		equal_sign = ft_strchr(env_cpy[n], '=');
		if (equal_sign)
			print_equal(env_cpy[n], equal_sign);
		else
			print_space(env_cpy[n]);
	}
	free_env_cpy(env_cpy);
}

void	check_b_export(t_parse *parse_result, t_env *env_head)
{
	if (!parse_result->next)
	{
		ft_export(env_head);
		free_parse(parse_result);
		return ;
	}
	else if (parse_result->next->str[0] == '-')
	{
		write(STDERR_FILENO, "wrong input, use: export without option.\n", 42);
		free_parse(parse_result);
		return ;
	}
	// else
	// {
	// 	// TO DO: the export with arg part;
	// }
}
