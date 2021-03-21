/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_syntax_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 16:01:28 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/12 15:35:58 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	free_syntax_error(int type, char ***cmd_grp, t_minishell *info)
{
	ptr_2d_free((void ***)cmd_grp, -1);
	return (syntax_error(type, info));
}
