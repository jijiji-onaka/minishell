/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:12:55 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 03:16:23 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "struct_etc.h"
# include "standard_lib.h"

void		execute_command_loop(t_minishell *info);
bool		execute_command(t_minishell *info, t_cmdlst *cmd);
bool		at_first_change_only_env(t_cmdlst *cmd,
				int *type, t_minishell *info);

#endif
