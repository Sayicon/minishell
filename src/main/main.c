#include "../inc/libft/libft.h"
#include "../inc/minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void	shell_init(t_shell *shell, char **envp);

volatile int	g_signal_status;

int	main(int argc, char *argv[], char **envp)
{
	t_shell	shell;

	if (argc > 1)
	{
		(void)argv;
		ft_putstr_fd("minishell: Sadece interaktif mod desteklenir\n", STDERR_FILENO);
		return (1);
	}
	shell_init(&shell, envp);
	prompt(&shell);
	clean_exit(&shell, 0, 0, NULL);
	return (0);
}

/* [BENİ SİL] Deneme için yazılmış fonkisyoundur siliniz. */
void	write_all_tokens(t_token_list *token_list)
{
	t_token	*current;

	if (!token_list || !token_list->head)
		return;
	current = token_list->head;
	printf("Tokens in the list:\n");
	while (current)
	{
		printf("Token Type: %d, Value: %s\n", current->type, current->value);
		current = current->next;
	}
}

void	minishell(char *input, t_shell *shell)
{
	shell->token_list = tokenizer(input, shell);
	if (!shell->token_list)
	{
		shell->last_status = 2;
		return ;
	}
	write_all_tokens(shell->token_list);
	shell->ast = parser(shell->token_list, shell);
	if (!shell->ast)
	{
		shell->last_status = 2;
		return ;
	}
	gc_free_tokens(&shell->token_list);
}

t_ast	*parser(t_token_list *token_list, t_shell *shell)
{
	if (!handle_syntax_errors(token_list, shell))
	{
		gc_free_tokens(&(shell->token_list));
		return (NULL);
	}
}

static void	shell_init(t_shell *shell, char **envp)
{
	shell->gc = NULL;
	shell->env = env_init(envp, shell);
	shell->token_list = NULL;
	shell->ast = NULL;
	if (!shell->env)
		clean_exit(shell, 1, E_WRITE_STDE, "minishell: failed to init environ\n");
	shell->last_status = 0;
}