/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:51:17 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 23:27:46 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lst_func.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_element;

	if (!(new_element = malloc(sizeof(t_list))))
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}
