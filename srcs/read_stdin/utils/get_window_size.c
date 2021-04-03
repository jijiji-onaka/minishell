/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_window_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 00:11:50 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/03 00:14:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	get_window_size(t_minishell *info)
{
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &(info->window.ws)) == -1)
		all_free_exit(info, ERR_IOCTL, __LINE__, __FILE__);
}
