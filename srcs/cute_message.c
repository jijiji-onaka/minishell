/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cute_message.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 03:54:12 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:51:01 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	put_help_message(void)
{
	ft_putstr_fd("\n================================\n", 1);
	ft_putstr_fd("Usage : this is usage of this shell\n\n", 1);
	ft_putstr_fd("     pwd [No option] ...\n", 1);
	ft_putstr_fd("     env [No option] [No argument]\n", 1);
	ft_putstr_fd("     echo [-n] ...\n", 1);
	ft_putstr_fd("     export [No option] ...\n", 1);
	ft_putstr_fd("     unset [No option] ...\n", 1);
	ft_putstr_fd("     exit [No option] ...\n", 1);
	ft_putstr_fd("\n================================\n\n", 1);
}
