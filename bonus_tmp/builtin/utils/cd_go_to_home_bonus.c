/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_to_home_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:24:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/21 14:33:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

void		not_set_home_path(t_minishell *info)
{
	if (write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28) < 28)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
}
