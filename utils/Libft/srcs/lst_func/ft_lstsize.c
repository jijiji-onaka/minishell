/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:17:41 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 23:27:51 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lst_func.h"

int	ft_lstsize(t_list *lst)
{
	int	cnt;

	if (!lst)
		return (INT_MIN);
	cnt = 0;
	while (lst)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}
