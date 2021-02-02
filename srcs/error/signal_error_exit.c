/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_error_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:08:01 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:08:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_error_exit(void)
{
	red_error();
	write(STDERR_FILENO, "signal fnction error\n", 21);
	exit(1);
}
