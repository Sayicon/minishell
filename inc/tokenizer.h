#ifndef TOKENIZER_H
# define TOKENIZER_H

/*		<======================[INCLUDES]======================>*/
# include "structs.h"

/*		<======================[FUNCTIONS]======================>*/

t_token_list	*tokenizer(char *input, t_shell *shell);
t_token			*token_create(char *value, t_token_type type);
t_token_list	*tokenlist_init(void);
void			tokenlist_add(t_token *new_token, t_token_list *list);
void			token_exit(char *str, t_token_list *token_list, t_shell *shell);
void			report_error(char *token);
t_bool			ft_isspace(int c);
t_bool			is_defined_operator(char *input, int i);
t_token_type	get_token_type(char *str, size_t len);

#endif