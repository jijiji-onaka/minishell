/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:26:40 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 22:07:44 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lst_func.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_elem;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_elem = ft_lstlast(*lst);
	last_elem->next = new;
}
