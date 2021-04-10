/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:19:23 by sehattor          #+#    #+#             */
/*   Updated: 2021/04/09 02:48:33 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/file_func.h"

static char	*read_and_strchr(t_gnl_list *node)
{
	char	*nl_ptr;

	node->ret = read(node->fd, node->buf, BUFFER_SIZE);
	if (node->ret == -1)
		return (false);
	node->buf[node->ret] = '\0';
	nl_ptr = ft_strchr(node->buf, '\n');
	return (nl_ptr);
}

static t_gnl_list	*make_list(int fd)
{
	t_gnl_list	*new;

	new = malloc(sizeof(t_gnl_list));
	if (new == NULL)
		return (NULL);
	new->buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (new->buf == NULL)
	{
		free(new);
		return (NULL);
	}
	new->fd = fd;
	new->buf[0] = '\0';
	new->next = NULL;
	return (new);
}

static t_gnl_list	*setup_list(int fd, t_gnl_list **head)
{
	t_gnl_list	*new;
	t_gnl_list	*lst;

	lst = *head;
	while (lst)
	{
		if (lst->fd == fd)
			return (lst);
		lst = lst->next;
	}
	new = make_list(fd);
	if (new == NULL)
		return (NULL);
	if (*head == NULL)
		*head = new;
	else
		lst = new;
	return (new);
}

static bool	get_line(t_gnl_list *node, char **line)
{
	char	*nl_ptr;

	nl_ptr = NULL;
	if (node->buf[0] != '\0')
		nl_ptr = ft_strchr(node->buf, '\n');
	while (nl_ptr == NULL)
	{
		if (node->buf[0] == '\0')
		{
			nl_ptr = read_and_strchr(node);
			if (nl_ptr)
				break ;
		}
		*line = gnl_strjoin(line, node->buf);
		if (*line == NULL)
			return (false);
		node->buf[0] = '\0';
		if (node->ret == 0)
			return (true);
	}
	*line = gnl_strjoin(line, node->buf);
	if (*line == NULL)
		return (-1);
	node->buf = get_next_word(node->buf, nl_ptr + 1);
	return (true);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl_list	*head;
	t_gnl_list			*node;

	if (fd < 0 || !line)
		return (clear_all_node(&head));
	node = setup_list(fd, &head);
	if (node == NULL)
		return (clear_all_node(&head));
	if (*line != NULL)
		*line = NULL;
	if (get_line(node, line) == false)
		return (clear_all_node(&head));
	if (node->ret == 0)
		return (clear_one_node(fd, &head));
	return (GNL_NL);
}
