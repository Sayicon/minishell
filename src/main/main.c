#include "../inc/libft/libft.h"
#include "../inc/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	shell_init(t_shell *shell, char **envp);

volatile int	g_signal_status;

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	if (argc > 1)
	{
		(void)argv;
		ft_putstr_fd("minishell: Sadece interaktif mod desteklenir\n", STDERR_FILENO);
		return (1);
	}
	shell_init(&shell, envp);
	prompt(&shell);
	clean_exit(&shell, 0, 0, NULL);
	return (0);
}

static void	shell_init(t_shell *shell, char **envp)
{
	shell->gc = NULL;
	shell->env = env_init(envp, shell);
	if (!shell->env)
		clean_exit(shell, 1, E_WRITE_STDE, "minishell: failed to init environ\n");
	shell->last_status = 0;
}