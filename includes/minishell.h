/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 02:04:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/26 22:25:39 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../utils/Libft/includes/libft.h"
# include "builtin.h"
# include "error.h"
# include "execute.h"
# include "parse.h"
# include "pipe_redirect.h"
# include "prompt.h"
# include "read_stdin.h"

void	set_minishell(t_minishell *info);
void	set_prompt_message(t_envlst *env_lst);
void	set_shell_level(void);
void	set_env(t_minishell *info);
void	sig_quit(int code);
void	sig_int(int code);

#endif
