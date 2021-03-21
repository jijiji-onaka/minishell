/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:12:55 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 04:54:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_BONUS_H
# define EXECUTE_BONUS_H

# include "struct_etc_bonus.h"
# include "standard_lib_bonus.h"

void		execute_command_loop(t_minishell *info);
bool		execute_command(t_minishell *info, t_cmdlst **cmd);
bool		at_first_change_only_env(t_cmdlst *cmd,
				int *type, t_minishell *info);
t_cmdlst	*do_db_pipe(t_cmdlst **cmd);
t_cmdlst	*do_and(t_cmdlst **cmd);
size_t		word_count(char const *s, char c);

#endif
