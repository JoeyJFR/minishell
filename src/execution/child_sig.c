#include "../../minishell.h"

void	child_int(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

// void	child_quit(int sig)
// {
// 	(void)sig;
// 	g_signal = 1;
// 	signal(SIGQUIT, SIG_DFL);
// }

void	sigquit_handler(int sig)
{
	(void)sig;
}

// void	sigsegv_handler(int code)
// {
// 	(void)code;
// 	write(2, "Segmentation fault\n", 19);
// 	exit(11);
// }
