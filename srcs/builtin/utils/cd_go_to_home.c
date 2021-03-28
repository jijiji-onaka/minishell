/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_go_to_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 17:24:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/25 22:08:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		not_set_home_path(t_minishell *info)
{
	if (write(STDERR_FILENO, "minishell: cd: HOME not set\n", 28) < 28)
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	g_global.exit_status = EXIT_FAILURE;
}
