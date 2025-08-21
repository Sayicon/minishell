#ifndef PARSER_H
# define PARSER_H

/*		<======================[INCLUDES]======================>*/
# include "structs.h"

/*		<======================[FUNCTIONS]======================>*/
t_ast	*parser(t_token_list *token_list);
t_bool	handle_syntax_errors(t_token_list *token_list);
t_bool	check_pipe(t_token *prev, t_token *next);

#endif