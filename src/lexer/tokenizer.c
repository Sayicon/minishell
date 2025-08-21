#include "../../inc/libft/libft.h"
#include "../../inc/minishell.h"
#include "../../inc/structs.h"
#include "../../inc/tokenizer.h"
#include "../../inc/ft_garbage_collector.h"
#include <stdlib.h>

static t_bool	handle_word(char *input, int *i, t_token_list *token_list);
static t_bool	handle_quotes(char *input, int *i);
static void		handle_operators(char *input, int *i, t_token_list *token_list);

t_token_list	*tokenizer(char *input, t_shell *shell)
{
	int				i;
	t_token_list	*token_list;

	if (!input || !*input)
		return (NULL);
	token_list = tokenlist_init();
	if (!token_list)
		clean_exit(shell, 1, E_WRITE_STDE, "minishell: malloc failed\n");
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '\0')
			break ;
		if (is_defined_operator(input, i))
			handle_operators(input, &i, token_list);
		else
			if (!handle_word(input, &i, token_list))
				return (gc_free_tokens(&token_list), NULL);
	}
	if (token_list->size == 0)
		return (free(token_list), NULL);
	return (token_list);
}

static t_bool	handle_word(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;
	int		start;
	char	*word;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !is_defined_operator(input, *i))
		if (!handle_quotes(input, i))
			return (FALSE);
	if (*i == start)
		return (FALSE);
	word = ft_substr(input, start, *i - start);
	if (!word)
		token_exit("minishell: malloc failed\n", token_list, NULL);
	new_token = token_create(word, WORD);
	if (!new_token)
	{
		free(word);
		token_exit("minishell: malloc failed\n", token_list, NULL);
	}
	tokenlist_add(new_token, token_list);
	return (TRUE);
}

static t_bool	handle_quotes(char *input, int *i)
{
	int	quote_type;

	if (input[*i] == '\'' || input[*i] == '\"')
	{
		quote_type = input[*i];
		(*i)++;
		while (input[*i] && input[*i] != quote_type)
			(*i)++;
		if (input[*i] != quote_type)
		{
			report_error(NULL);
			return (FALSE);
		}
		else
			(*i)++;
	}
	else
		(*i)++;
	return (TRUE);
}

static void	handle_operators(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;
	size_t	len;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		token_exit("minishell: malloc failed\n", token_list, NULL);
	len = 1;
	if (input[*i] == '<' || input[*i] == '>')
		if (input[*i + 1] == input[*i])
			len++;
	new_token->value = ft_substr(input, *i, len);
	if (!new_token->value)
		token_exit("minishell: malloc failed\n", token_list, NULL);
	new_token->type = get_token_type(&input[*i], len);
	tokenlist_add(new_token, token_list);
	*i += len;
}
