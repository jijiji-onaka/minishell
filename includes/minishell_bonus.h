/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:04:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:49:01 by tjinichi         ###   ########.fr       */
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

char	*search_env(char *str, int num, t_envlst *env_lst, bool *flag);
void	set_minishell(t_minishell *info);
void	set_prompt_message(t_envlst *env_lst);
void	set_shell_level(void);
void	set_env(t_minishell *info);
void	sig_quit(int code);
void	sig_int(int code);

#endif
