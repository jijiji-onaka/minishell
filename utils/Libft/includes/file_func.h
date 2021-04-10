/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_func.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:31 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 02:00:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_FUNC_H
# define FILE_FUNC_H

# include "libft.h"
# include <stdbool.h>
# define NO_RETURN 2
# define GNL_NL 1
# define GNL_EOF 0
# define GNL_ERR -1
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_gnl_list
{
	int					fd;
	ssize_t				ret;
	char				*buf;
	struct s_gnl_list	*next;
}				t_gnl_list;

char			*create_file_name(char *directory,
					char *file, char *extension);
int				get_next_line(int fd, char **line);
size_t			gnl_strlen(char *s);
char			*gnl_strjoin(char **s1, char *s2);
char			*get_next_word(char *buf, char *nl_ptr);
int				clear_one_node(int fd, t_gnl_list **head);
int				clear_all_node(t_gnl_list **head);
bool			ft_close(int *fd);

#endif
