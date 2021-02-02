/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:31 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/21 04:57:42 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_FUNC_H
# define FILE_FUNC_H

# include "libft.h"
# include <stdbool.h>
# define NO_RETURN 2
# define R_NL 1
# define R_EOF 0
# define R_ERR -1
# define BUFFER_SIZE 1024

typedef struct	s_gnl
{
	int				fd;
	char			*store;
	struct s_gnl	*next;
}				t_gnl;

char			*create_file_name(char *directory,
				char *file, char *extension);
int				get_next_line(int fd, char **line);
t_gnl			*gnl_lstnew(char *content, int fd);
void			gnl_lstadd_front(t_gnl **lst, t_gnl *new);
t_gnl			*recognize_fd(int fd, t_gnl **lst);
bool			ft_close(int *fd);

#endif
