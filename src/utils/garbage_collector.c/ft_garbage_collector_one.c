#include "../../../inc/ft_garbage_collector.h"
#include "../../../inc/libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_gc	*gc_create(void)
{
	t_gc	*garbage;

	garbage = (t_gc *)malloc(sizeof(t_gc));
	if (!garbage)
		return (NULL);
	garbage->addr = NULL;
	garbage->next = NULL;
	return	(garbage);
}

static void	garbage_add_back(t_gc *garbage, t_gc **garcol)
{
	t_gc	*iter;

	if (!garbage || !garcol)
		return ;
	if (!(*garcol))
		*garcol = garbage;
	else
	{
		iter = *garcol;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = garbage;
	}
}

void	*gc_malloc(size_t size, t_gc **garcol)
{
	void	*ptr;
	t_gc	*garbage;

	if (!garcol || size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	garbage = gc_create();
	if (!garbage)
		return (free(ptr), NULL);
	garbage->addr = ptr;
	garbage_add_back(garbage, garcol);
	return (ptr);
}

void	*gc_calloc(size_t size, t_gc **garcol)
{
	void	*ptr;
	t_gc	*garbage;

	if (!garcol || size == 0)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, size);
	garbage = gc_create();
	if (!garbage)
		return (free(ptr), NULL);
	garbage->addr = ptr;
	garbage_add_back(garbage, garcol);
	return (ptr);
}

int	gc_add_garbage(void	*ptr, t_gc **garcol)
{
	t_gc	*garbage;

	if (!ptr || !garcol)
		return (0);
	garbage = gc_create();
	if (!garbage)
	{
		free(ptr);
		gc_free_all(garcol);
		perror("gc_add_garbage: ");
		exit(EXIT_FAILURE);
	}
	garbage->addr = ptr;
	garbage_add_back(garbage, garcol);
	return (1);
}
