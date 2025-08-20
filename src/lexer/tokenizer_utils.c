#include "../../inc/structs.h"
#include "sys/types.h"

t_bool	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (TRUE);
	return (FALSE);
}

t_bool	is_defined_operator(char *input, int i)
{
	if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		return (TRUE);
	return (FALSE);
}

t_token_type	get_token_type(char *str, size_t len)
{
	if (str[0] == '|')
		return (PIPE);
	else if (str[0] == '<' && len == 1)
		return (REDIR_IN);
	else if (str[0] == '>' && len == 1)
		return (REDIR_OUT);
	else if (str[0] == '>' && len == 2)
		return (REDIR_APPEND);
	else if (str[0] == '<' && len == 2)
		return (HEREDOC);
	else
		return (INVALID);
}
