/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 01:51:32 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/03 00:14:11 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "struct_etc.h"
# include "standard_lib.h"
# define ERR_READ "Failed to \033[4mread\033[0m at the above location. "
# define ERR_WRITE "Failed to \033[4mwrite\033[0m at the above location. "
# define ERR_MALLOC "Failed to \033[4mmalloc\033[0m at the above location. "
# define ERR_SIGNAL "Failed to \033[4msignal\033[0m at the above location. "
# define ERR_EXECVE "Failed to \033[4mexecve\033[0m at the above location. "
# define ERR_FORK "Failed to \033[4mfork\033[0m at the above location. "
# define ERR_FAIL_CHILD "The child process did not terminate successfully. "
# define ERR_WAIT_PID "Failed to \033[4mwait_pid\033[0m at the above location. "
# define ERR_PIPE "Failed to \033[4mpipe\033[0m at the above location. "
# define ERR_OPEN "Failed to \033[4mopen\033[0m at the above location. "
# define ERR_CLOSE "Failed to \033[4mclose\033[0m at the above location. "
# define ERR_DUP "Failed to \033[4mdup\033[0m at the above location. "
# define ERR_DUP2 "Failed to \033[4mdup2\033[0m at the above location. "
# define ERR_CHDIR "Failed to \033[4mchdir\033[0m at the above location. "
# define ERR_OPENDIR "Failed to \033[4mopendir\033[0m at the above location. "
# define ERR_READDIR "Failed to \033[4mreaddir\033[0m at the above location. "
# define ERR_CLOSEDIR "Failed to \033[4mclosedir\033[0m at the above location. "
# define ERR_GETCWD "Failed to \033[4mgetcwd\033[0m at the above location. "
# define ERR_LSTAT "Failed to \033[4mlstat\033[0m at the above location. "
# define ERR_ISATTY "Failed to \033[4misatty\033[0m at the above location. "
# define ERR_TGETENT "Failed to \033[4mtgetent\033[0m at the above location. "
# define ERR_TGETSTR "Failed to \033[4mtgetstr\033[0m at the above location. "
# define ERR_IOCTL "Failed to \033[4mioctl\033[0m at the above location. "
# define SYNTAX_EOL_NUM -1
# define SYNTAX_EOL "minishell: syntax error: unexpected end of file\n"
# define NEWLINE -2
# define NO_OLDPWD "minishell: cd: OLDPWD not set\n"
# define SYNTAX "minishell: syntax error near unexpected "
# define SYNTAX_OP "minishell: syntax error near unexpected token `>\'\n"
# define SYNTAX_DB_OP "minishell: syntax error near unexpected token `>>\'\n"
# define SYNTAX_SEMICOLON "minishell: syntax error near unexpected token `;\'\n"
# define SYNTAX_PIPE "minishell: syntax error near unexpected token `|\'\n"
# define SYNTAX_INPUT "minishell: syntax error near unexpected token `<\'\n"
# define SYNTAX_NL "minishell: syntax error near unexpected token `newline\'\n"
# define ERR_DB_SEMICOLON "minishell: `;;\' is not supported by mandatory.\n"
# define ERR_DB_PIPE "minishell: `||\' is not supported by mandatory.\n"
# define ERR_OUTPUT_PIPE "minishell: `>|\' is not supported by mandatory.\n"
# define ERR_DB_INPUT "minishell: `<<\' is not supported by mandatory.\n"
# define ERR_TR_INPUT "minishell: `<<<\' is not supported by mandatory.\n"
# define ERR_MANDATORY "That command is not supported by mandatory.\n"
# define ERR_ENV "Usage: env [No option] [No argument]\n"
# define ERR_PWD "Usage: pwd [No option] ...\n"
# define ERR_ECHO "Usage: echo [-n] ...\n"
# define ERR_EXPORT "Usage: export [No option] ...\n"
# define ERR_UNSET "Usage: unset [No option] ...\n"

void			all_free_minishell_info(t_minishell *info);
void			all_free_exit(t_minishell *info, char *error_message, \
							int line_num, char *file_name);
void			*ft_perror(char *err_message);
void			ft_perror_exit(char *error_message);
void			signal_error_exit(void);
bool			syntax_error(int type, t_minishell *info);

#endif
