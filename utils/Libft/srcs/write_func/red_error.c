/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 22:16:42 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/04 14:30:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/write_func.h"

void	red_error(void)
{
	write(2, "\033[31m\033[1m[Error]\033[0m\n", 21);
}
