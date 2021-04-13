/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:04:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 13:52:11 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H

# include "../utils/Libft/includes/libft.h"
# include "builtin_bonus.h"
# include "error_bonus.h"
# include "execute_bonus.h"
# include "parse_bonus.h"
# include "pipe_redirect_bonus.h"
# include "prompt_bonus.h"
# include "read_stdin_bonus.h"
# include "safe_function_bonus.h"

void		set_minishell(t_minishell *info);
void		update_command_history_file(t_minishell *info,
				t_hist_list *history);
void		set_prompt_message(t_envlst *env_lst);
void		set_shell_level(void);
void		set_env(t_minishell *info);
void		set_command_history(t_minishell *info);
void		set_term(t_minishell *info);
t_hist_list	*make_struct_hist_list(int fd, char *line, t_hist_list *prev,
				t_minishell *info);
void		historylist_add_front(t_hist_list **lst, t_hist_list *new);
void		update_command_history_file(t_minishell *info,
				t_hist_list *history);
void		sig_quit(int code);
void		sig_int(int code);
char		*ft_getenv(char *str, t_envlst *env_lst, bool get_shell_val);

#endif
