/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 02:26:44 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 02:26:52 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	putstr_fd(char *str, int fd, t_err err, t_minishell *info)
{
	if (ft_putstr_fd(str, fd) == false)
		all_free_exit(info, ERR_WRITE, err.line, err.file);
}

void	putchar_fd(char chr, int fd, t_err err, t_minishell *info)
{
	if (ft_putchar_fd(chr, fd) == false)
		all_free_exit(info, ERR_WRITE, err.line, err.file);
}
