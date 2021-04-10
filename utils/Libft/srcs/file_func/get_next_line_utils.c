/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:39:11 by sehattor          #+#    #+#             */
/*   Updated: 2021/04/09 02:33:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/file_func.h"

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

char	*gnl_strjoin(char **s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	str = malloc(gnl_strlen(*s1) + gnl_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while ((*s1) && (*s1)[i])
	{
		str[i] = (*s1)[i];
		i++;
	}
	ptr_free((void **)s1);
	j = 0;
	while (s2 && s2[j] && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*get_next_word(char *buf, char *nl_ptr)
{
	size_t	i;

	i = 0;
	while (buf[i] && nl_ptr[i])
	{
		buf[i] = nl_ptr[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

int	clear_one_node(int fd, t_gnl_list **head)
{
	t_gnl_list	*begin;
	t_gnl_list	*tmp;

	begin = *head;
	while (begin && begin->next)
	{
		if (begin->next->fd == fd)
		{
			tmp = begin->next;
			begin->next = begin->next->next;
			ptr_free((void **)&(tmp->buf));
			free(tmp);
		}
		else
			begin = begin->next;
	}
	begin = *head;
	if (begin->fd == fd)
	{
		tmp = begin->next;
		ptr_free((void **)&(begin->buf));
		free(begin);
		begin = tmp;
	}
	return (GNL_EOF);
}

int	clear_all_node(t_gnl_list **head)
{
	t_gnl_list	*lst;
	t_gnl_list	*next;

	lst = *head;
	while (lst)
	{
		next = lst->next;
		ptr_free((void **)&(lst->buf));
		free(lst);
		lst = next;
	}
	return (GNL_ERR);
}
