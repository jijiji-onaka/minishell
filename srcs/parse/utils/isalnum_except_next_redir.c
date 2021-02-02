/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalnum_except_next_redir.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 18:27:21 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:28:09 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

bool	isalnum_except_next_redir(char *str)
{
	return (!((*str == '|' || *str == '>' || *str == '<' || *str == ';')
			|| (*str == '>' && *(str + 1) == '>')));
}
