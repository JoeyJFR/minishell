#include "mini_exec.h"

void	define_type(t_parse *node)
{
	if (node->str[0] == '/')
		node->type = ABS_PATH;
	else if (!ft_strcmp(node->str, "<<"))
		node->type = DL;
	else if (!ft_strcmp(node->str, ">>"))
		node->type = DR;
	else if (!ft_strcmp(node->str, "<"))
		node->type = SL;
	else if (!ft_strcmp(node->str, ">"))
		node->type = SR;
	else if (!ft_strcmp(node->str, "|"))
		node->type = PIPE;
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

	i = 0;
	while (str[0][i] && str[0][i] != ' ' && str[0][i] != '$')
		++i;
	arg_str = malloc(sizeof(char) * (i + 1));
	if (!arg_str)
		return (NULL);
	i = -1;
	while (str[0][++i] && str[0][i] != ' ' && str[0][i] != '$')
		arg_str[i] = str[0][i];
	arg_str[i] = '\0';
	(*str) += i;
	return (arg_str);
}

void	skip_blank(char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

t_parse	*define_arg(t_parse **list, char **str)
{
	char	*arg_str;
	t_parse	*node;

	skip_blank(str);
	arg_str = fill_arg(str);
	node = mini_lstnew(arg_str);
	if (!node)
		return (NULL);
	mini_lstadd_back(list, node);
	define_type(node);
	return (*list);
}

t_parse	*parsing(char *str)
{
	t_parse	*node;

	node = NULL;
	while (*str)
	{
		node = define_arg(&node, &str);
		if (!node)
			return (mini_error("arg_node", 1), NULL);
	}
	return (node);
}
