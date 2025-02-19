#include "../minishell.h"

int	g_sigint = 0;

int	init_main(int ac, char **av, t_alloc *alloc, t_env *env)
{
	(void)ac;
	(void)av;
	alloc->exit_status = 0;
	alloc->str = NULL;
	init_signal();
	alloc->env_head = env;
	if (alloc->env_head == NULL)
		return (1);
	return (0);
}

// *** OLD PROMPT
// int	init_prompt(t_alloc *alloc, char **str, t_env *env)
// {
// 	if (alloc->exit_status == 131)
// 		write(1, "Quit (core dumped)\n", 20);
// 	if (alloc->exit_status == 130)
// 		write(1, "\n", 1);
// 	if (isatty(fileno(stdin)))
// 		*str = readline("minishell > ");
// 	else
// 		*str = get_next_line(fileno(stdin));
// 	if (*str)
// 	{
// 		char	*tmp = *str;
// 		*str = ft_strtrim(*str, "\n");
// 		free(tmp);
// 	}
// 	if (!(*str))
// 	{
// 		write(1, "exit\n", 6);
// 		free_env(env);
// 		rl_clear_history();
// 		exit (0);
// 	}
// 	else if (!(*(*str)))
// 	{
// 		free(*str);
// 		return (1);
// 	}
// 	add_history(*str);
// 	if (g_sigint == 1)
// 		alloc->exit_status = 130;
// 	return (0);
// }

int	init_prompt(t_alloc *alloc, char **str, t_env *env)
{
	if (alloc->exit_status == 131)
		write(1, "Quit (core dumped)\n", 20);
	if (alloc->exit_status == 130)
		write(1, "\n", 1);
	(void)str;
	(void)env;
	// *str = readline("minishell > ");
	// if (!(*str))
	// {
	// 	write(1, "exit\n", 6);
	// 	free_env(env);
	// 	exit (0);
	// }
	// else if (!(*(*str)))
	// {
	// 	free(*str);
	// 	return (2);
	// }
	// add_history(*str);
	if (g_sigint == 1)
		alloc->exit_status = 130;
	return (0);
}

int	check_token_env(t_alloc *alloc)
{
	if (alloc->token_head == NULL)
		return (1);
	return (0);
}


// int	main(int ac, char **av, char **envp)
// {
// 	char	*str;
// 	t_alloc	alloc;
// 	t_env	*env;
// 	t_token	*token;

// 	env = parse_env(envp);
// 	if (init_main(ac, av, &alloc, env))
// 		return (1);
// 	while (1)
// 	{
// 		if (init_prompt(&alloc, &str, env))
// 			continue ;
// 		token = parsing(str, env, &alloc.exit_status);
// 		// print_token(token);
// 		// continue;
// 		free(str);
// 		alloc.token_head = token;
// 		if (check_token_env(&alloc))
// 			continue ;
// 		alloc.exit_status = exec(&alloc, env, token);
// 		free_token(alloc.token_head);
// 	}
// 	rl_clear_history();
// 	free_env(alloc.env_head);
// 	return (0);
// }

int main(int ac, char **av, char **envp)
{
    char 	*str;
    t_alloc alloc;
    t_env 	*env;
    t_token *token;

    env = parse_env(envp);
    if (init_main(ac, av, &alloc, env))
        return (1);
    while (1)
    {
		if (isatty(fileno(stdin)))  // Mode interactif
			str = readline("minishell > ");
		else  // Mode testeur (lecture via get_next_line)
			str = get_next_line(fileno(stdin));
		if (!str)
            break;
		if (str)
		{
			char *tmp = str;
			str = ft_strtrim(str, "\n");
			free(tmp);
		}
        add_history(str);
        if (init_prompt(&alloc, &str, env))
            continue;
        token = parsing(str, env, &alloc.exit_status);
        free(str);
        alloc.token_head = token;
        if (check_token_env(&alloc))
            continue;
        alloc.exit_status = exec(&alloc, env, token);
        free_token(alloc.token_head);
    }
    free_env(alloc.env_head);
    return (0);
}