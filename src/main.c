#include "../minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigterm_handler(int sig)
{
	(void)sig;
	exit(0);
}

void	init_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, sigterm_handler);
}
/* to do/redo
exec special cases / valgrind
signals
empty env case : only pwd should still work
exit
built_ins handle env case
main
*/
int main(int ac, char **av, char **envp)
{
	char	*str;
	t_alloc	alloc;
	t_env	*env;
	t_token	*token;

	(void)ac;
	(void)av;
	alloc.exit_status = 0;
	alloc.str = NULL;
    init_signal();
	env = parse_env(envp);
	alloc.env_head = env;
	if (alloc.env_head == NULL)
		return (1);
	while (1)
	{
		//read_input
		//parsing
		if (alloc.exit_status == 131)
			write(1, "Quit (core dumped)\n", 20);
		if (alloc.exit_status == 130)
			write(1, "\n", 1);
		str = readline(" readline > ");
		if (!str)
		{
			write(1, "exit\n", 6);
			break ;
		}
		else if (!*str)
		{
			free(str);
			continue ;
		}
		add_history(str);
		token = parsing(str, env, alloc.exit_status);
		alloc.token_head = token;
		free(str);
		if (alloc.token_head == NULL)
			continue ;
		//execution
		if (check_path(env))
			continue ;
		alloc.exit_status = exec(&alloc, env, token);
		free_token(alloc.token_head);
	}
	free_env(alloc.env_head);
	return (0);
}
