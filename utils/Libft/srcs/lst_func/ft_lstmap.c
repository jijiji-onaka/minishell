/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:41:35 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 23:27:41 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lst_func.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		if (!(tmp = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, tmp);
		lst = lst->next;
	}
	return (new_list);
}
