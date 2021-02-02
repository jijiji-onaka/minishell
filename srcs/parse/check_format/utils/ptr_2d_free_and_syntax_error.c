/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr_2d_free_and_syntax_error.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 02:15:41 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:24:06 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"

bool	ptr_2d_free_and_syntax_error(int type, char ***cmd_grp,
			t_minishell_info *info)
{
	int	i;

	i = 0;
	if (cmd_grp != NULL)
	{
		while ((*cmd_grp)[i])
			i++;
		ptr_2d_free((void ***)cmd_grp, i);
	}
	return (syntax_error(type, info));
}
