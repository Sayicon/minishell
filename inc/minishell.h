#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_garbage_collector.h"

# define E_WPERROR 1
# define E_WRITE_STDE 2

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	t_gc	*gc;
}	t_shell;

void	clean_exit(t_shell *shell, int exit_code, int err_type, char *str);
t_env	*env_init(char **envp, t_shell *shell);

#endif