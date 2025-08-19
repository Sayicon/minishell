#include "../../../inc/minishell.h"
#include "../../../inc/libft/libft.h"
#include <sys/types.h>

static char	*trim_endofhome(const char *home, t_shell *shell)
{
	size_t len;
	char	*trimmed_home;

	len = ft_strlen(home);
	if (len <= 1)
		return (safe_dup(home, shell));
	trimmed_home = safe_dup(home, shell);
	while (len > 1 && trimmed_home[len-1] == '/')
	{
		trimmed_home[len-1] = '\0';
		len--;
	}
	return (trimmed_home);
}

static char	*replaced_two(const char *raw, char *trimmed_home, t_shell *shell)
{
	size_t home_len;

	home_len = ft_strlen(trimmed_home);
	if (home_len == 1 && trimmed_home[0] == '/')
    	return (safe_dup(raw, shell));
	if (ft_strlen(raw) < home_len || ft_strncmp(raw, trimmed_home, home_len) != 0)
		return (safe_dup(raw, shell));
	if (raw[home_len] == '\0')
		return (safe_dup("~", shell));
	if (raw[home_len] != '/')
		return (safe_dup(raw, shell));
	return (NULL);
}

char	*get_replaced_cwd(const char *raw, const char *home, t_shell *shell)
{
	char	*cwd;
	char	*trimmed_home;
	char	*replaced_two_out;
	size_t	home_len;

	if (!raw)
		return (safe_dup("~", shell));
	if (!home || !*home)
		return (safe_dup(raw, shell));
	trimmed_home = trim_endofhome(home, shell);
	home_len = ft_strlen(trimmed_home);
	if ((replaced_two_out = replaced_two(raw, trimmed_home, shell)) != NULL)
		return (replaced_two_out);
	while (raw[home_len] == '/')
		home_len++;
	if (raw[home_len] == '\0')
		return (safe_dup("~", shell));
	cwd = ft_strjoin("~/", raw + home_len);
	if (!cwd || gc_add_garbage(cwd, &(shell->gc)) == 0)
		clean_exit(shell, 1, E_WRITE_STDE, "minishell: failed to create replaced cwd\n");
	return (cwd);
}
