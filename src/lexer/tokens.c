#include "../../inc/minishell.h"
#include "../../inc/libft/libft.h"
#include <stdlib.h>

t_token_list	*tokenlist_init(void)
{
	t_token_list	*token_list;

	token_list = malloc(sizeof(t_token_list));
	if (!token_list)
		return (NULL);
	token_list->head = NULL;
	token_list->tail = NULL;
	token_list->size = 0;
	return (token_list);
}

t_token	*token_create(char *value, t_token_type type)
{
	t_token	*new_token;

	if (!value)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void			tokenlist_add(t_token *new_token, t_token_list *list)
{
	if (!list || !new_token)
		return;
	if (list->size == 0)
		list->head = new_token;
	else
		list->tail->next = new_token;
	list->tail = new_token;
	list->size++;
}