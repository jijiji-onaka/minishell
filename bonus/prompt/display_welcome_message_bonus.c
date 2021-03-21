/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_welcome_message_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:38:09 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/18 13:20:48 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell_bonus.h"

void	display_welcome_message(void)
{
	write(STDERR_FILENO, "\n\n\033[1m\x1b[35m Welcome to minishell \x1b[0m\n\n\
This is my own little bash written by C. \n\
A student project at 42tokyo.\n\
Run 'help' for information on a command.\n\n", 153);
}
