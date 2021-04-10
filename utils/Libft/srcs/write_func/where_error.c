/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 02:12:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:57:43 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/write_func.h"

t_err	where_err(int line, char *file)
{
	t_err	err;

	err.line = line;
	err.file = file;
	return (err);
}
