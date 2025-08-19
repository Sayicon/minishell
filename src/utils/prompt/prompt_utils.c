#include "../../../inc/libft/libft.h"
#include "../../../inc/minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int	is_all_whitespaces(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != ' ' && input[i] != '\t')
		{
			free(input);
			return (0);
		}
		i++;
	}
	return (1);
}

char	*get_user(t_shell *shell)
{
	char	*user;

	user = getenv("USER");
	if (!user || *user == 0)
		user = ft_strdup("unknown");
	else
		user = ft_strdup(user);
	if (!user)
		clean_exit(shell, 1, E_WPERROR, "minishell:");
	if (gc_add_garbage(user, &(shell->gc)) == 0)
	{
		free(user);
		clean_exit(shell, 1, E_WRITE_STDE, "minishell: failed to add garbage\n");
	}
	return (user);
}

char	*get_host(t_shell *shell)
{
	int		fd;
	char	buf[256];
	ssize_t	len;

	fd = open("/etc/hostname", O_RDONLY);
	if (fd < 0)
		return (safe_dup("unknown", shell));
	len = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (len <= 0)
		return (safe_dup("unknown", shell));
	if (len > 0)
	{
    	buf[len] = '\0';
    	while (len > 0 && (buf[len-1] == '\n' || buf[len-1] == '\r' || buf[len-1] == ' '))
        	buf[--len] = '\0';
	}
	return (safe_dup(buf, shell));
}

char	*safe_dup(const char *str, t_shell *shell)
{
	char	*ptr;
	t_gc	*iter;

	if (!str)
		ptr = ft_strdup("unknown");
	else
		ptr = ft_strdup(str);
	if (!ptr)
		clean_exit(shell, 1, E_WPERROR, "minishell:");
	if (gc_add_garbage(ptr, &(shell->gc)) == 0)
	{
		iter = shell->gc;
		while (iter)
		{
			if (iter->addr == ptr)
				break ;
			iter = iter->next;
		}
		if (iter == NULL)
			free(ptr);
		clean_exit(shell, 1, E_WRITE_STDE, "minishell: failed to add garbage\n");
	}
	return (ptr);
}

char	*mini_get_env(t_shell *shell, const char *key)
{
	t_env	*env;

	if (!shell || !shell->env || !key || !*key)
		return (NULL);
	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (safe_dup(env->value, shell));
		env = env->next;
	}
	return (NULL);
}
