/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_history_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 05:11:14 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

void	historylist_add_front(t_hist_list **lst, t_hist_list *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	new->old_hist = *lst;
	(*lst)->new_hist = new;
	*lst = new;
}

static void	lstadd_back(t_hist_list **lst, t_hist_list *new)
{
	t_hist_list	*last_elem;

	if (!new || !lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last_elem = *lst;
	while (last_elem->new_hist)
		last_elem = last_elem->new_hist;
	last_elem->new_hist = new;
}

t_hist_list	*make_struct_hist_list(int fd, char *line, t_hist_list *old_hist,
						t_minishell *info)
{
	t_hist_list	*new;

	new = malloc(sizeof(t_hist_list));
	if (new == NULL)
	{
		if (fd == -1)
			close(fd);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	new->command = line;
	new->new_hist = NULL;
	new->old_hist = old_hist;
	return (new);
}

static void	get_command_history(int fd, t_hist_list **history,
						t_minishell *info)
{
	char		*line;
	int			ret;
	t_hist_list	*old_hist;

	line = NULL;
	ret = get_next_line(fd, &line);
	old_hist = make_struct_hist_list(fd, line, NULL, info);
	lstadd_back(history, old_hist);
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ret == 0 || line[0] == '\0')
		{
			ptr_free((void **)&line);
			if (ret == 0)
				break ;
			continue ;
		}
		old_hist = make_struct_hist_list(fd, line, old_hist, info);
		lstadd_back(history, old_hist);
	}
}

void	set_command_history(t_minishell *info)
{
	int	fd;

	info->history.list = NULL;
	fd = open(info->history.file_path, O_RDONLY);
	if (fd == -1)
	{
		info->history.list = make_struct_hist_list(-1, NULL, NULL, info);
		info->history.begin = info->history.list;
		return ;
	}
	get_command_history(fd, &(info->history.list), info);
	while (info->history.list->new_hist)
	{
		info->history.list = info->history.list->new_hist;
	}
	info->history.begin = info->history.list;
	return ;
}
