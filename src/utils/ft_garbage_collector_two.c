#include "../../inc/ft_garbage_collector.h"

void	gc_free_all(t_gc **garcol)
{
	t_gc	*it;
	t_gc	*next;

	if (!garcol || !(*garcol))
		return ;
	it = *garcol;
	next = NULL;
	while (it)
	{
		next = it->next;
		if (it->addr)
		{
			free(it->addr);
			it->addr = NULL;
		}
		it->next = NULL;
		free(it);
		it = next;
	}
	*garcol = NULL;
}

void	gc_free(void *ptr, t_gc **garcol)
{
	t_gc	*it;
	t_gc	*prev;

	if (!ptr || !garcol)
		return ;
	it = *garcol;
	prev = NULL;
	while (it) {
		if (it->addr == ptr) {
			if (prev)
				prev->next = it->next;
			else
				*garcol = it->next;
			if (it->addr)
				free(it->addr);
			it->addr = NULL;
			it->next = NULL;
			free(it);
			return ;
		}
		prev = it;
		it = it->next;
	}
	if (ptr)
		free(ptr);
}
