/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:25:18 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 03:16:33 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

ssize_t		safe_read(char buf[4], char **ptr, t_minishell *info)
{
	ssize_t	rc;

	rc = read(STDIN, buf, READ_SIZE);
	if (rc < 0)
	{
		if (ptr)
			ptr_free((void**)ptr);
		if (errno == EBADF)
			return (-1);
		all_free_exit(info, ERR_READ, __LINE__, __FILE__);
	}
	buf[rc] = '\0';
	// printf("{{{{{{{{{{%s}}}}}}\n", buf);
	return (rc);
}
