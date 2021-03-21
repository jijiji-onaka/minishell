/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 22:20:52 by tjinichi          #+#    #+#             */
/*   Updated: 2021/03/19 22:23:03 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*reset_prompt(char **ptr1, char **ptr2)
{
	if (ptr1)
		ptr_free((void **)ptr1);
	if (ptr2)
		ptr_free((void **)ptr2);
	return (NULL);
}
