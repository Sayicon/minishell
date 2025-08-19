#include "../../../inc/minishell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	upd_sh_last_stat(t_shell *sh, int new_value)
{
	sh->last_status = g_signal_status;
	g_signal_status = new_value;
}

void	setup_signals_prompt(void)
{
	struct sigaction	sa_int;	

	sa_int = setup_sigint_prompt();
	sigaction(SIGINT, &sa_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}

struct sigaction	setup_sigint_prompt(void)
{
	struct sigaction	sa_int;

	sa_int.sa_handler = handle_sigint_prompt;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	return (sa_int);
}

void	handle_sigint_prompt(int sig)
{
	(void) sig;
	g_signal_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}