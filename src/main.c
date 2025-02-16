#include "../minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
	struct sigaction sig_b;

	(void)ac;
	(void)av;
	alloc.exit_status = 0;
	alloc.str = NULL;
    signal(SIGINT, ctrl_c);
    sig_b.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sig_b, NULL);
	env = parse_env(envp);
	alloc.env_head = env;
	if (alloc.env_head == NULL)
		return (1);
	while (1)
	{
		//read_input
		//parsing
		str = readline(" readline > ");
		if (!str)
			break ;
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
