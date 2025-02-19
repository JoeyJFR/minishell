#include "../../minishell.h"

void	child_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_sigint = 1;
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
