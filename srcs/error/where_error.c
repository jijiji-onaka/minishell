/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 02:12:45 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/04 02:30:35 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_err	where_err(int line, char *file)
{
	t_err	err;

	err.line = line;
	err.file = file;
	return (err);
}
