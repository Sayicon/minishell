#ifndef MINISHELL_H
# define MINISHELL_H

/*		<======================[INCLUDES]======================>*/
# include "ft_garbage_collector.h"
# include "tokenizer.h"
# include "structs.h"
# include "parser.h"
# include <signal.h>

/*		<======================[GLOBAL VARIABLES]======================>*/
extern volatile int g_signal_status;


/*		<======================[FUNCTIONS]======================>*/
void				minishell(char *input, t_shell *shell);
void				clean_exit(t_shell *shell, int exit_code, int err_type, char *str);
t_env				*env_init(char **envp, t_shell *shell);

/*	->	Prompt*/
void				prompt(t_shell *shell);
int					is_all_whitespaces(char *input);
char				*get_user(t_shell *shell);
char				*get_host(t_shell *shell);
char				*get_cwd(t_shell *shell);
char				*safe_dup(const char *str, t_shell *shell);
char				*mini_get_env(t_shell *shell, const char *key);
char				*get_replaced_cwd(const char *raw, const char *home, t_shell *shell);
char				*assemble_prompt(char *user, char *host, char *cwd, t_shell *shell);
/*	->	Prompt Signals*/
void				upd_sh_last_stat(t_shell *sh, int new_value);
void				setup_signals_prompt(void);
void				handle_sigint_prompt(int sig);


#endif