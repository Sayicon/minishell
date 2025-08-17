#ifndef FT_GARBAGE_COLLECTOR_H
# define FT_GARBAGE_COLLECTOR_H

typedef struct s_gc
{
	void		*addr;
	struct s_gc	*next;
}	t_gc;

#include <stdlib.h>

int			gc_add_garbage(void	*ptr, t_gc **garcol);
void		*gc_malloc(size_t size, t_gc **garcol);
void		*gc_calloc(size_t size, t_gc **garcol);
void		gc_free_all(t_gc **garcol);
void		gc_free(void *ptr, t_gc **garcol);


#endif