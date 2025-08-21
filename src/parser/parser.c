#include "../../inc/minishell.h"
#include <stdlib.h>

t_ast	*parser(t_token_list *token_list)
{
	if (!handle_syntax_errors(token_list))
	{
		gc_free_tokens(&token_list);
		return (NULL);
	}
	/*PARSE ETME ZAMANI*/
}

t_bool	handle_syntax_errors(t_token_list *token_list)
{
	t_token	*current;
	t_token	*prev;

	if (token_list->size == 0)
		return (report_error("newline"), FALSE);
	if (!token_list->head || !token_list->tail)
		return (report_error("newline"), FALSE);
	if (token_list->head->type == PIPE)
		return (report_error("|"), FALSE);
	current = token_list->head;
	prev = NULL;
	while (current)
	{
		if (current->type == INVALID)
			return (report_error(current->value), FALSE);
		if (current->type == PIPE && !check_pipe(prev, current->next))
			return (FALSE);
		if ((current->type == REDIR_IN || current->type == REDIR_OUT
			|| current->type == REDIR_APPEND || current->type == HEREDOC) && 
			!check_redir(current->next))
			return (FALSE);
		prev = current;
		current = current->next;
	}
	if (prev->type != WORD)
		return (report_error("newline"), FALSE);
	return (TRUE);
}
