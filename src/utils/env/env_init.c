#include "../../../inc/minishell.h"
#include "../../../inc/libft/libft.h"

static t_env	*env_create(char *env_str, t_shell *shell);

t_env	*env_init(char **envp, t_shell *shell)
{
	t_env	*head;
	t_env	*iter;
	int		i;

	if (!envp[0])
		return (NULL);
	head = env_create(envp[0], shell);
	i = 1;
	iter = head;
	while (envp[i])
	{
		iter->next = env_create(envp[i], shell);
		if (!iter->next)
			return (NULL);
		iter = iter->next;
		i++;
	}
	return (head);
}

static t_env	*env_create(char *env_str, t_shell *shell)
{
	t_env	*ptr;
	char	*sep;

	ptr = gc_calloc(sizeof(t_env), shell);
	if (!ptr)
		return (NULL);
	sep = ft_strchr(env_str, '=');
	if (!sep)
		return (NULL);
	*sep = '\0';
	ptr->key = ft_strdup(env_str);
	if (!ptr->key)
		return (NULL);
	gc_add_garbage(ptr->key, shell);
	ptr->value = ft_strdup(sep + 1);
	if (!ptr->value)
		return (NULL);
	gc_add_garbage(ptr->value, shell);
	*sep = '=';
	ptr->next = NULL;
	return (ptr);
}