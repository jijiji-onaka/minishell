/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:12:55 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:14:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "struct_etc.h"
# include "standard_lib.h"

void		execute_each_command_loop(t_minishell_info *info);
bool		execute_each_command(t_minishell_info *info, t_cmdlst *cmd);

#endif
