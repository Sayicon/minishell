/*	Programı Clean bir şekilde sonlandırmak istediğimizde kullanıcağımız scriptler	*/
#include "../../inc/minishell.h"
#include "../../inc/libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

void	clean_exit(t_shell *shell, int exit_code, int err_type, char *str)
{
	if (err_type == E_WPERROR && str)
		perror(str);
	else if (err_type == E_WRITE_STDE && str)
		ft_putstr_fd(str, STDERR_FILENO);
	gc_free_all(&(shell->gc));
	rl_clear_history();
	exit(exit_code);
}