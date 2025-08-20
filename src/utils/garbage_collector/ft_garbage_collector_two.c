#include "../../inc/ft_garbage_collector.h"
#include "../../inc/minishell.h"
#include <stdlib.h>

void	gc_free_all(t_shell *shell)
{
	t_gc	**garcol;
	t_gc	*it;
	t_gc	*next;

	garcol = &(shell->gc);
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

void	gc_free_tokens(t_token_list **token_list)
{
	t_token	*current_token;
	t_token	*next;

	if (!token_list || !(*token_list))
		return ;
	current_token = (*token_list)->head;
	while (current_token)
	{
		next= current_token->next;
		if (current_token->value)
		{
			free(current_token->value);
			current_token->value = NULL;
		}
		free(current_token);
		current_token = next;
	}
	(*token_list)->head = NULL;
	(*token_list)->tail = NULL;
	(*token_list)->size = 0;
	free(*token_list);
	*token_list = NULL;
}

void	gc_free(void *ptr, t_shell *shell)
{
	t_gc	**garcol;
	t_gc	*it;
	t_gc	*prev;

	garcol = &(shell->gc);
	if (!ptr || !garcol || !(*garcol))
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