/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_waiting_for_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:36:06 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 12:51:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		display_what_is_waiting_for(char quo, char **ptr1, char **ptr2,
					t_minishell *info)
{
	int		f;

	f = 1;
	if (quo == '\"')
		f = write(STDOUT, "wait :(double quote)> ", 22);
	else if (quo == '\'')
		f = write(STDOUT, "wait :(single quote)> ", 22);
	else if (quo == '|')
		f = write(STDOUT, "wait :(pipe)> ", 14);
	if (f < 0)
	{
		if (ptr1)
			ptr_free((void **)ptr1);
		if (ptr2)
			ptr_free((void **)ptr2);
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
}
