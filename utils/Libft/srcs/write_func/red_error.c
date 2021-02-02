/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:16:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/20 19:35:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/write_func.h"

/*
** [Error]を赤文字(\033[31m)・太文字(\033[1m)で出す関数
*/

void	red_error(void)
{
	write(2, "\033[31m\033[1m[Error]\033[0m\n", 21);
}
