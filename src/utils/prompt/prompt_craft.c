#include "../../../inc/minishell.h"
#include "../../../inc/libft/libft.h"
#include <sys/types.h>

static void	p_append_str(char *prompt, char *str, size_t total_len);
static void p_change_color(char *prompt, const char *color, size_t total_len);
static size_t get_colors_len(void);

char	*assemble_prompt(char *user, char *host, char *cwd, t_shell *shell)
{
	char	*prompt;
	size_t	len;
	size_t	colors_len;
	size_t	total_len;

	/*	user + '@' + host + ':' + cwd + "$" + ' ' = 4*/
	len = ft_strlen(user) + 1 + ft_strlen(host) + 1 + ft_strlen(cwd) + 2;
	colors_len = get_colors_len();
	total_len = len + colors_len + 1;
	prompt = gc_calloc(total_len, shell);
	if (!prompt)
		clean_exit(shell, 1, E_WRITE_STDE, "minishell: failed to allocate prompt\n");
	p_change_color(prompt, C_CYAN, total_len);
	p_append_str(prompt, user, total_len);
	p_change_color(prompt, C_WHITE_BOLD, total_len);
	p_append_str(prompt, "@", total_len);
	p_append_str(prompt, host, total_len);
	p_change_color(prompt, C_BLUE, total_len);
	p_append_str(prompt, ":", total_len);
	p_append_str(prompt, cwd, total_len);
	p_change_color(prompt, C_RESET, total_len);
	p_append_str(prompt, "$ ", total_len);
	prompt[total_len - 1] = '\0';
	return (prompt);
}

static void p_change_color(char *prompt, const char *color, size_t total_len)
{
	size_t i = 0;
	size_t beg_len;
	size_t end_len;
	size_t color_len;

	beg_len = ft_strlen(RL_BEG);
	end_len = ft_strlen(RL_END);
	color_len = ft_strlen(color);
	while (i < total_len - 1 && prompt[i] != '\0')
		i++;
	if (i + beg_len + color_len + end_len < total_len)
	{
		ft_memmove(prompt + i, RL_BEG, beg_len);
		i += beg_len;
		ft_memmove(prompt + i, color, color_len);
		i += color_len;
		ft_memmove(prompt + i, RL_END, end_len);
		i += end_len;
		prompt[i] = '\0';
	}
}

static void	p_append_str(char *prompt, char *str, size_t total_len)
{
	size_t		i;
	size_t	str_len;

	i = 0;
	str_len = ft_strlen(str);
	while (prompt[i] != '\0' && i < total_len - 1)
		i++;
	ft_memmove(prompt + i, str, str_len);
	i += str_len;
	prompt[i] = '\0';  // Sonuna null karakter ekle
}

static size_t get_colors_len(void)
{
	size_t	colors_len;
	size_t	beg_len;
	size_t	end_len;

	beg_len = ft_strlen(RL_BEG);
	end_len = ft_strlen(RL_END);
	colors_len = (beg_len + ft_strlen(C_CYAN) + end_len) + 
					(beg_len + ft_strlen(C_WHITE_BOLD) + end_len) +
					(beg_len + ft_strlen(C_BLUE) + end_len) +
					(beg_len + ft_strlen(C_RESET) + end_len);
	return (colors_len);
}



