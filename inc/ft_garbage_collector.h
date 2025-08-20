#ifndef FT_GARBAGE_COLLECTOR_H
# define FT_GARBAGE_COLLECTOR_H

/*		<=======[INCLUDES]=======>*/
# include "structs.h"
# include "sys/types.h"

/*		<=======[FUNCTIONS]=======>*/
int			gc_add_garbage(void	*ptr, t_shell *shell);
void		*gc_malloc(size_t size, t_shell *shell);
void		*gc_calloc(size_t size, t_shell *shell);
void		gc_free_all(t_shell *shell);
void		gc_free_tokens(t_token_list **token_list);
void		gc_free(void *ptr, t_shell *shell);


#endif