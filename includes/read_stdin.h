/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:42:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:46:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_STDIN_H
# define READ_STDIN_H

# include "struct_etc.h"
# include "standard_lib.h"

int		add_command_group(char **split, t_cmd_grp *cmd_grp_info,
						int split_size, t_minishell_info *info);
void	ctrl_d_exit(char **ptr, t_minishell_info *info);
void	rm_chr_in_str(char **str, char chr);
ssize_t	safe_read(char *buf, char **ptr, t_minishell_info *info);
char	*waiting_for_input(t_minishell_info *info);
int		waiting_for_next_command(char ***cmd_grp, int array_size,
						t_minishell_info *info);
char	*waiting_for_quotation(char first_quo, char **command, \
						t_minishell_info *info);

#endif
