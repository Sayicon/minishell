#ifndef STRUCTS_H
# define STRUCTS_H

/*		<===================[DEFINES]======================>*/
//POSIX sinyal kütüphanesini rahat açabilsin diye define
# define _POSIX_C_SOURCE 200809L
# define E_WPERROR 1
# define E_WRITE_STDE 2

/*	->Colors*/
# define RL_BEG "\001"
# define RL_END "\002"
/*		->Nord teması (soğuk tonlar, göz dostu)*/
# define C_CYAN 		"\033[0;36m"
# define C_WHITE_BOLD	"\033[1;37m"
# define C_BLUE			"\033[0;34m"
/*		->Gruvbox esintisi (sıcak toprak tonları)*/
# define C_YELLOW		"\033[0;33m"
# define C_ORANGE		"\033[0;38;5;208m"
# define C_RED			"\033[0;31m"
# define C_RESET		"\033[0m"

/*		<===================[ENUMS]======================>*/
/*Tokens symbols: 
		WORD: Normal words, arguments, etc.
		PIPE: Pipe operator '|'
		REDIR_IN: Input redirection '<'
		REDIR_OUT: Output redirection '>'
		REDIR_APPEND: Append output redirection '>>'
		HEREDOC: Here document '<<'
*/
typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HEREDOC,
	INVALID
}	t_token_type;

typedef enum s_bool
{
	FALSE,
	TRUE
}	t_bool;

/*		<===================[STRUCTS]======================>*/

/*		<=======[FT_GARBAGE_COLLECTOR]=======>*/
typedef struct s_gc
{
	void		*addr;
	struct s_gc	*next;
}	t_gc;

/*		<=======[TOKENIZER]=======>*/

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
	int		size;
}	t_token_list;

/*		<=======[MINISHELL]=======>*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env			*env;
	t_gc			*gc;
	t_token_list	*token_list;
	int		last_status;
}	t_shell;


#endif