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
We need a struct alloc which contains the heads to free in voids func
signals
empty env case : only pwd should still work
exit
built_ins handle env case
main
*/
int main(int ac, char **av, char **env)
{
	char	*str;
	t_alloc	gen;
	t_data	data;
	pid_t	pid;
	struct sigaction sig_b;
	
	(void)ac;
	(void)av;
    signal(SIGINT, ctrl_c);
    sig_b.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sig_b, NULL);
	gen.env_head = parse_env(env);
	if (gen.env_head == NULL)
		return (1);
	// the idea is sending gen to every function which could fail
	while (1)
	{
		str = readline(" readline > ");
		if (!str)
			break ;
		else if (!*str)
		{
			free(str);
			continue ;
		}
		add_history(str);
		gen.token_head = parsing(str, gen.env_head);
		free(str);
		if (gen.token_head == NULL)
			return (free_env(gen.env_head), 1);
		if (built_in(gen.token_head, gen.env_head))
			continue ;
		if (check_path(gen.env_head))
		{
			printf("error in environment: no PATH for execution.\n");
			continue ;
		}
		reform_env(gen.env_head, data.env);
		pid = fork();
		if (pid == -1)
			exit_parsing("Fork", &gen, get_error_code());
		if (pid == 0)
			exec(gen.token_head, &data);
		else
			waitpid(pid, NULL, 0);
		free_token(gen.token_head);
	}
	free_env(gen.env_head);
	return (0);
}
