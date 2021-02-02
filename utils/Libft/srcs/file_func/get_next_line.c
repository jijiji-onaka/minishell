/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 23:19:23 by sehattor          #+#    #+#             */
/*   Updated: 2020/12/11 21:30:18 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/file_func.h"

static int		free_return(char **ptr, int rc)
{
	free(*ptr);
	*ptr = NULL;
	return (rc);
}

static int		read_and_store(int fd, char **store, int rc)
{
	char	*buf;
	char	*tmp_ptr;

	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if ((rc = read(fd, buf, BUFFER_SIZE)) >= 0)
		buf[rc] = '\0';
	if (!(*store) && rc > 0)
		*store = ft_strdup(buf);
	else if (*store && rc > 0)
	{
		tmp_ptr = *store;
		*store = ft_strjoin(tmp_ptr, buf);
		free(tmp_ptr);
		tmp_ptr = NULL;
	}
	free(buf);
	if (rc == -1)
		free_return(store, rc);
	return (rc);
}

int				get_next_line(int fd, char **line)
{
	static t_gnl	*lst;
	t_gnl			*now;
	char			*newline;
	char			*tmp;
	int				rc;

	if (fd < 0 || !line || (!(now = recognize_fd(fd, &lst))))
		return (-1);
	rc = 1;
	while ((!(newline = ft_strchr(now->store, '\n'))) && \
		(rc = read_and_store(fd, &(now->store), rc)) > 0)
		if (!(now->store))
			return (free_return(&(now->store), R_ERR));
	if (newline)
	{
		*line = ft_substr(now->store, 0, newline - now->store);
		tmp = now->store;
		now->store = ft_strdup(newline + 1);
		free_return(&tmp, NO_RETURN);
		return ((!(*line)) || !(now->store) ? \
			free_return(&(now->store), R_ERR) : R_NL);
	}
	*line = ft_strdup(now->store);
	free_return(&(now->store), NO_RETURN);
	return ((!(*line) || rc < 0) ? R_ERR : R_EOF);
}
