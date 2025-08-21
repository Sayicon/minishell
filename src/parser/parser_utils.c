#include "../../inc/structs.h"
#include "../../inc/tokenizer.h"

t_bool	check_pipe(t_token *prev, t_token *next)
{
	if (!prev || prev->type != WORD)
		return (report_error("|"), FALSE);
	if (!next || next->type == PIPE || next->type == INVALID)
		return (report_error("|"), FALSE);
	return (TRUE);
}

t_bool	check_redir(t_token *next)
{
	if (!next)
		return (report_error("newline"), FALSE);
	if (next->type != WORD)
		return (report_error(next->value), FALSE);
	return (TRUE);
}