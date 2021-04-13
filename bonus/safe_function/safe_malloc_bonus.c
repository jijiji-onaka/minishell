/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_malloc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 07:44:43 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:38 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../bonus_includes/minishell_bonus.h"

void	*safe_malloc(size_t len, t_err err, t_minishell *info)
{
	void	*res;

	res = malloc(len);
	if (res == NULL)
		all_free_exit(info, ERR_MALLOC, err.line, err.file);
	return (res);
}
