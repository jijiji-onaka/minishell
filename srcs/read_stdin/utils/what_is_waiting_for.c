/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_waiting_for.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 21:36:06 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/29 18:47:45 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void		display_what_is_waiting_for(char quo, char **ptr1, char **ptr2,
					t_minishell *info)
{
	int		write_err_flag;

	write_err_flag = 1;
	if (quo == '\"')
		write_err_flag = write(STDOUT_FILENO, "wait :(double quote)> ", 22);
	else if (quo == '\'')
		write_err_flag = write(STDOUT_FILENO, "wait :(single quote)> ", 22);
	else if (quo == '|')
		write_err_flag = write(STDOUT_FILENO, "wait :(pipe)> ", 14);
	if (write_err_flag < 0)
	{
		if (ptr1)
			ptr_free((void**)ptr1);
		if (ptr2)
			ptr_free((void**)ptr2);
		all_free_exit(info, ERR_WRITE, __LINE__, __FILE__);
	}
}
