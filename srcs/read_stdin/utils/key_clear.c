/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:51:59 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 01:48:43 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		clear_terminal(char *buf, t_string *command, t_minishell *info)
{
	(void)buf;
	ft_putstr_fd(info->key.clean, STDOUT_FILENO);
	put_prompt(info);
	ft_putstr_fd(command->str, STDOUT_FILENO);
}
