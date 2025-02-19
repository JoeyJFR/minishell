#include "../../minishell.h"

/*
checks what is the current operator it is dealing with
*/
int	is_ope(char c, char *current)
{
	if (!current || !*current)
	{
		if (c == '<' || c == '>' || c == '|')
			return (1);
		return (0);
	}
	else if (*current == c && (c == '>' || c == '<') && !*(current + 1))
		return (1);
	else if (*current != '<' && *current != '>' \
		&& *current != '|' && (c == '<' || c == '>' || c == '|'))
		return (1);
	return (0);
}

/*
check the number of command
*/
int	count_cmd(t_token *token)
{
	int	i;

	i = 0;
	if (token)
		i = 1;
	while (token->prev)
		token = token->prev;
	while (token)
	{
		if (token->type == PI)
			++i;
		token = token->next;
	}
	return (i);
}

void	define_type(t_token *node)
{
	if (node->str[0] == '/')
		node->type = ABS;
	else if (!ft_strcmp(node->str, "cd"))
		node->type = CD;
	else if (!ft_strcmp(node->str, "echo"))
		node->type = ECHO;
	else if (!ft_strcmp(node->str, "export"))
		node->type = EXPORT;
	else if (!ft_strcmp(node->str, "env"))
		node->type = ENV;
	else if (!ft_strcmp(node->str, "pwd"))
		node->type = PWD;
	else if (!ft_strcmp(node->str, "unset"))
		node->type = UNSET;
	else if (!ft_strcmp(node->str, "exit"))
		node->type = EXIT;
	else
		node->type = ARG;
}

void	define_ope(t_token *node)
{
	if (!ft_strcmp(node->str, "<<"))
		node->type = DL;
	else if (!ft_strcmp(node->str, ">>"))
		node->type = DR;
	else if (!ft_strcmp(node->str, "<"))
		node->type = SL;
	else if (!ft_strcmp(node->str, ">"))
		node->type = SR;
	else if (!ft_strcmp(node->str, "|"))
		node->type = PI;
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf("[%s]", token->str);
		token = token->next;
	}
	printf("\n");
}
