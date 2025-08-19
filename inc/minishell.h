#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_garbage_collector.h"

# define E_WPERROR 1
# define E_WRITE_STDE 2

/*--------GLOBAL VARIABLE--------*/
extern volatile int g_signal_status;


/*--------STRUCTS--------*/
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
	int		last_status;
}	t_shell;


/*--------FUNCTIONS--------*/
void	clean_exit(t_shell *shell, int exit_code, int err_type, char *str);
t_env	*env_init(char **envp, t_shell *shell);

/*	->	Prompt*/
void	prompt(t_shell *shell);
int		is_all_whitespaces(char *input);
char	*get_user(t_shell *shell);
char	*safe_dup(char *str, t_shell *shell);
char	*get_host(t_shell *shell);
char	*mini_get_env(t_env *env, const char *key);
char	*get_replaced_cwd(const char *raw, const char *home, t_shell *shell)

#endif