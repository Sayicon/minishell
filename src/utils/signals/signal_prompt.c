#include "../../../inc/minishell.h"

void	upd_sh_last_stat(t_shell *sh, int new_value)
{
	sh->last_status = g_signal_status;
	g_signal_status = new_value;
}