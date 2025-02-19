#include "../../minishell.h"

/*
// initialize the argument
*/
void	init_arg(char **str, char **arg_str, t_token **node, t_alloc *data)
{
	int	i;

	i = len_word(*str);
	*arg_str = ft_calloc(sizeof(char), i + 1);
	if (!*arg_str)
		exit_parsing("Alloc", data, 1);
	*node = mini_lstnew(NULL);
	if (!*node)
	{
		free(*arg_str);
		exit_parsing("Alloc", data, 1);
	}
	(*node)->str = *arg_str;
}

/*
init the node,
fill its string's argument
fill its type's argument
*/
t_token	*fill_arg(char **str, t_alloc *data)
{
	t_token	*arg;
	char	*arg_str;

	arg_str = NULL;
	arg = NULL;
	init_arg(str, &arg_str, &arg, data);
	if (is_ope(**str, NULL))
	{
		fill_str(str, arg_str, 1);
		define_ope(arg);
	}
	else
	{
		fill_str(str, arg_str, 0);
		define_type(arg);
	}
	return (arg);
}

/*
skip blanks
*/
void	skip_blank(char **str)
{
	while (**str && (**str == ' ' || **str == '\t'))
		++(*str);
}

/*
skip the whitespaces from the inputed string,
create and fill a new argument,
add it to the current chained-list
*/
t_token	*define_arg(t_alloc *data, char **str)
{
	t_token	*arg;

	skip_blank(str);
	if (!ft_strlen(*str))
		return (data->token_head);
	arg = fill_arg(str, data);
	mini_lstadd_back(&data->token_head, arg);
	return (data->token_head);
}

/*
principal parsing function:
	check if there is an unpaired quote
	convert vars with there definition
	define the chained-list
*/
t_token	*parsing(char *buffer, t_env *env, int *exit_code)
{
	t_alloc	data;
	char	*str;

	data.token_head = NULL;
	data.env_head = env;
	if (check_quotes(buffer) != -1)
	{
		print_error("Quote unpaired case");
		*exit_code = 2;
		return (NULL);
	}
	str = convert_var(buffer, env, *exit_code);
	data.str = str;
	while (*str)
		data.token_head = define_arg(&data, &str);
	free(data.str);
	if (check_syntax(data.token_head))
	{
		print_error("Syntax");
		*exit_code = 2;
		free_token(data.token_head);
		return (NULL);
	}
	return (data.token_head);
}
