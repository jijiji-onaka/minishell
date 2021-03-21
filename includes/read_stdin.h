/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 17:42:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/19 23:00:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_STDIN_H
# define READ_STDIN_H

# include "struct_etc.h"
# include "standard_lib.h"

int			check_more_pipe(char **inputs, t_cmd_grp *cmd_grp_info,
						t_minishell *info);
void	ctrl_d_exit(char **ptr, t_minishell *info);
void	ctrl_d_rm(char **ptr, t_minishell *info);
void	display_what_is_waiting_for(char quo, char **ptr1, char **ptr2,
						t_minishell *info);
char	*reset_prompt(char **ptr1, char **ptr2);
void	rm_chr_in_str(char **str, char chr);
ssize_t	safe_read(char *buf, char **ptr, t_minishell *info);
char	*waiting_for_input(t_minishell *info);
char	*waiting_for_next_command(char ***cmd_grp, int array_size,
						t_minishell *info);
char	*waiting_for_quotation(char first_quo, char **command, \
						t_minishell *info);

#endif
