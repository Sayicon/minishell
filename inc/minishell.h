#ifndef MINISHELL_H
# define MINISHELL_H

/*		<=======[INCLUDES]=======>*/
# include "ft_garbage_collector.h"
# include <signal.h>
//POSIX sinyal kütüphanesini rahat açabilsin diye define
#define _POSIX_C_SOURCE 200809L

/*		<=======[DEFINES]=======>*/
# define E_WPERROR 1
# define E_WRITE_STDE 2

/*	->Colors*/
#define RL_BEG "\001"
#define RL_END "\002"
/*		->Nord teması (soğuk tonlar, göz dostu)*/
# define C_CYAN 		"\033[0;36m"
# define C_WHITE_BOLD	"\033[1;37m"
# define C_BLUE			"\033[0;34m"
/*		->Gruvbox esintisi (sıcak toprak tonları)*/
# define C_YELLOW		"\033[0;33m"
# define C_ORANGE		"\033[0;38;5;208m"
# define C_RED			"\033[0;31m"
# define C_RESET		"\033[0m"

/*		<=======[GLOBAL VARIABLE]=======>*/
extern volatile int g_signal_status;


/*		<=======[STRUCTS]=======>*/
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


/*		<=======[FUNCTIONS]=======>*/
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
/*		->	Prompt Signals*/
void				upd_sh_last_stat(t_shell *sh, int new_value);
void				setup_signals_prompt(void);
void				handle_sigint_prompt(int sig);


#endif