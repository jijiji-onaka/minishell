/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:39:11 by sehattor          #+#    #+#             */
/*   Updated: 2020/12/11 21:30:25 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/file_func.h"

t_gnl	*gnl_lstnew(char *content, int fd)
{
	t_gnl	*new_element;

	if (!(new_element = malloc(sizeof(t_gnl))))
		return (NULL);
	new_element->fd = fd;
	new_element->store = ft_strdup(content);
	new_element->next = NULL;
	return (new_element);
}

void	gnl_lstadd_front(t_gnl **lst, t_gnl *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	*lst = new;
}

t_gnl	*recognize_fd(int fd, t_gnl **lst)
{
	t_gnl			*res;

	res = *lst;
	while (res)
	{
		if (res->fd == fd)
			return (res);
		res = res->next;
	}
	res = gnl_lstnew("", fd);
	gnl_lstadd_front(lst, res);
	return (res);
}
