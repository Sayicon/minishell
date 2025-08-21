/*	Programı Clean bir şekilde sonlandırmak istediğimizde kullanıcağımız scriptler	*/
#include "../../inc/minishell.h"
#include "../../inc/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

/*		<=======[CLEAN_EXIT]=======> 
		-> Programı temiz bir şekilde sonlandırmak için kullanılır.
		-> Hata mesajlarını yazdırır ve gerekli temizlik işlemlerini yapar.
*/
void	clean_exit(t_shell *shell, int exit_code, int err_type, char *str)
{
	if (err_type == E_WPERROR && str)
		perror(str);
	else if (err_type == E_WRITE_STDE && str)
		ft_putstr_fd(str, STDERR_FILENO);
	gc_free_all(shell);
	gc_free_tokens(&(shell->token_list));
	rl_clear_history();
	exit(exit_code);
}

/*		<=======[TOKEN_EXIT]=======> 
		-> Token işlemleri sırasında hata oluştuğunda kullanılır.
		-> Hata mesajını yazdırır ve gerekli temizlik işlemlerini yapar.
*/
void	token_exit(char *str, t_token_list *token_list, t_shell *shell)
{
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (token_list && shell && shell->token_list != token_list)
		gc_free_tokens(&token_list);
	if (shell)
		clean_exit(shell, 1, E_WRITE_STDE, NULL);
	exit(EXIT_FAILURE);
}

/*		<=======[REPORT_ERROR]=======> 
		-> Hata mesajlarını yazdırmak için kullanılır.
		-> Hata türüne göre farklı mesajlar yazdırır.
		-> E_WPERROR: Sistem hatası (perror ile yazdırılır).
		-> E_WRITE_STDE: Kullanıcı hatası (standart hata çıktısına yazdırılır).
		-> token: Hata ile ilgili token yazdırılır.
		-> str: Hata mesajı yazdırılır.
*/
void	report_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token", STDERR_FILENO);
	if (token)
	{
		ft_putstr_fd(" \'", STDERR_FILENO);
		ft_putstr_fd(token, STDERR_FILENO);
		ft_putstr_fd("\'\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd("\n", STDERR_FILENO);
}