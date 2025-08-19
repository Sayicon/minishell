#include "../../../inc/minishell.h"
#include "../../../inc/libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*make_prompt(t_shell *shell)
{
	char	*prompt;
	char	*user;
	char	*host;
	char	*cwd;

	user = get_user(shell);
	host = get_host(shell);
	cwd = get_cwd(shell);
	prompt = assemble_prompt(user, host, cwd, shell);
	setup_signals_prompt();
	return (prompt);
}

void	prompt(t_shell *shell)
{
	char	*input;
	char	*pmt;

	while (1)
	{
		pmt = make_prompt(shell);
		g_signal_status = -1;
		input = readline(pmt);
		if (g_signal_status == 130)
			upd_sh_last_stat(shell, -1);
		if (!input)
			break ;
		if (is_all_whitespaces(input))
			continue ;
		if (ft_strcmp(input, "exit") == 0)
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			free(input);
			break ;
		}
		add_history(input);
		//minishell(input, shell);
		free(input);
	}
}

char	*get_cwd(t_shell *shell)
{
	char	*raw;
	char	*home;
	char	*cwd;
	char	*display;

	raw = mini_get_env(shell, "PWD");
	home = getenv("HOME");
	if (raw && home && ft_strncmp(raw, home, ft_strlen(home)) == 0)
		cwd = get_replaced_cwd(raw, home, shell);
	else if (raw)
		cwd = safe_dup(raw, shell);
	else
	{
		cwd = getcwd(NULL, 0);
		gc_add_garbage(cwd, &(shell->gc));
		if (!cwd)
			return (safe_dup("(deleted)", shell));
		if (cwd && home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
		{
			display = get_replaced_cwd(cwd, home, shell);
			return (display);
		}
	}
	return (cwd);
}