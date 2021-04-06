/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_function.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 02:27:12 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/06 07:51:48 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAFE_FUNCTION_H
# define SAFE_FUNCTION_H

# include "struct_etc.h"
# include "standard_lib.h"

void		putstr_fd(char *str, int fd, t_err err, t_minishell *info);
void		putchar_fd(char chr, int fd, t_err err, t_minishell *info);
ssize_t		safe_read(char buf[4], char **ptr, t_minishell *info);
void		*safe_malloc(size_t len, t_err err, t_minishell *info);

#endif
