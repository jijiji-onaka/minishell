/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:25:18 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 16:23:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ssize_t	safe_read(char buf[4], char **ptr, t_minishell *info)
{
	ssize_t	rc;

	ft_bzero(buf, READ_SIZE);
	rc = read(STDIN, buf, READ_SIZE);
	if (rc < 0)
	{
		if (ptr)
			ptr_free((void **)ptr);
		if (errno == EBADF)
			return (-1);
		all_free_exit(info, ERR_READ, __LINE__, __FILE__);
	}
	buf[rc] = '\0';
	return (rc);
}
