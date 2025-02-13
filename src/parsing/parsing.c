#include "../../minishell.h"

/*
initialize the argument
*/
void	init(char **str, char **arg_str, t_token **node)
{
	int		i;

	i = len_word(*str);
	*arg_str = ft_calloc(sizeof(char), i + 1);
	if (!*arg_str)
		return ;
	*node = mini_lstnew(NULL);
	if (!*node)
		return (free(*arg_str));
	(*node)->str = *arg_str;
}

/*
init the node,
fill its string's argument
fill its type's argument
*/
t_token	*fill_arg(char **str)
{
	t_token *arg;
	char	*arg_str;
	
	arg_str = NULL;
	arg = NULL;
	init(str, &arg_str, &arg);
	if (is_ope(**str, NULL))
	{
		fill_ope(str, arg_str);
		define_ope(arg);
	}
	else
	{
		fill_word(str, arg_str);
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
		(*str)++;
}

/*
skip the whitespaces in the inputed string,
create and fill a new argument,
add it to the current chained-list
*/
t_token	*define_arg(t_token **list, char **str)
{
	t_token	*arg;

	skip_blank(str);
	arg = fill_arg(str);
	if (!arg)
		return (NULL);
	mini_lstadd_back(list, arg);
	return (*list);
}

/*
principal parsing function:
	check if there is an unpaired quote
	convert vars with there definition
	define the chained-list
*/
t_token	*parsing(char *buffer, t_env *env)
{
	t_alloc data;
	char	*str;
	char	*str_head;

	data.token_head = NULL;
	data.env_head = env;
	if (check_quotes(buffer) != -1)
		return (print_error("Quote unpaired case"), NULL);
	str = convert_var(buffer, &data);
	str_head = str;
	while (*str)
		data.token_head = define_arg(&data.token_head, &str);
	free(str_head);
	return (data.token_head);
}
