#include "../../minishell.h"

void	define_type(t_parse *node)
{
	if (node->str[0] == '/')
		node->type = ABS;
	else if (!ft_strcmp(node->str, "<<"))
		node->type = DL;
	else if (!ft_strcmp(node->str, ">>"))
		node->type = DR;
	else if (!ft_strcmp(node->str, "<"))
		node->type = SL;
	else if (!ft_strcmp(node->str, ">"))
		node->type = SR;
	else if (!ft_strcmp(node->str, "|"))
		node->type = PI;
	else if (!ft_strcmp(node->str, "cd") || !ft_strcmp(node->str, "echo")
		|| !ft_strcmp(node->str, "export") || !ft_strcmp(node->str, "env")
		|| !ft_strcmp(node->str, "pwd") || !ft_strcmp(node->str, "unset")
		|| !ft_strcmp(node->str, "exit"))
		node->type = BUILT_IN;
	else
		node->type = ARG;
}

char	*fill_arg(char **str)
{
	char	*arg_str;
	int		i;

	i = len_word(*str, ' ');
	arg_str = malloc(sizeof(char) * (i + 1));
	if (!arg_str)
		return (NULL);
	arg_str = fill_str(str, ' ', arg_str);
	return (arg_str);
}

void	skip_blank(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		(*str)++;
}

t_parse	*define_arg(t_parse **list, char **str)
{
	char	*arg_str;
	t_parse	*node;

	skip_blank(str);
	arg_str = fill_arg(str);
	if (!arg_str)
		return (NULL);
	if (*arg_str)
	{
		node = mini_lstnew(arg_str);
		if (!node)
			return (free(arg_str), NULL);
		mini_lstadd_back(list, node);
		define_type(node);
	}
	return (*list);
}
/*
	Remplacer buffer par str en changeant les variables d'env et les quotes
*/

t_parse	*parsing(char *buffer, t_env *env)
{
	t_parse	*node;
	char	*str;
	char	*str_head;

	node = NULL;
	if (check_quotes(buffer) != -1)
		return (printf("single quote\n"), NULL);
	str = convert_var(buffer, env);
	if (!str)
		return (NULL);
	str_head = str;
	while (*str)
	{
		node = define_arg(&node, &str);
		if (!node)
			return (free(str_head), free_parse(node), NULL);
	}
	free(str_head);
	return (node);
}
