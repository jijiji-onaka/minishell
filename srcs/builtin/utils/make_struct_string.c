/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_struct_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:45:04 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/24 19:46:10 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_string	make_struct_string(char *str, size_t len)
{
	t_string	res;

	res.str = str;
	res.len = len;
	return (res);
}
