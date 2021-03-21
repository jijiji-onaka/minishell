/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_read_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:25:18 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/20 13:59:27 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

ssize_t		safe_read(char *buf, char **ptr, t_minishell *info)
{
	ssize_t	rc;

	rc = read(0, buf, 1);
	if (rc < 0 && errno != EBADF)
	{
		if (ptr)
			ptr_free((void**)ptr);
		all_free_exit(info, ERR_READ, __LINE__, __FILE__);
	}
	return (rc);
}
