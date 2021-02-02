/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:35:00 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 23:27:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lst_func.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = NULL;
		*lst = tmp;
	}
	*lst = NULL;
}
