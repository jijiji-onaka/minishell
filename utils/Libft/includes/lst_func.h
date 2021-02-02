/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 20:46:37 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 23:41:32 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_FUNC_H
# define LST_FUNC_H

# include "libft.h"

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

#endif
