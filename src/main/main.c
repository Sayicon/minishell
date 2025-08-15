#include "../inc/libft/libft.h"
#include "../inc/ft_garbage_collector.h"
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	t_gc	*gc;

	gc = NULL;
	gc_malloc(10, &gc);
	gc_free(gc_malloc(10, &gc), &gc);
	gc_free_all(&gc);

	printf("\033[34mminishell \033[32m$ \033[0m");

	return (0);
}