/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_astarisk_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 07:53:13 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/10 12:51:37 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell_bonus.h"

static int		all_file_len(t_wild_lst *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len += ft_strlen(lst->value) + 1;
		lst = lst->next;
	}
	return (len);
}

static void		create_sorted_files(t_wild_lst *lst,
					char **ptr, t_minishell *info)
{
	int			i;
	int			j;
	char		*new;
	t_wild_lst	*next;

	lst = merge_lst_sort(lst);
	if (!(new = malloc((sizeof(char) * (all_file_len(lst) + 1)))))
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	i = 0;
	while (lst)
	{
		next = lst->next;
		j = 0;
		while ((lst->value)[j])
			new[i++] = (lst->value)[j++];
		if (next)
			new[i++] = ' ';
		free(lst);
		lst = next;
	}
	new[i] = '\0';
	ptr_free((void **)ptr);
	*ptr = new;
}

bool			change_astarisk(char **ptr, t_minishell *info, int i)
{
	char		*current_dir;
	bool		ret;
	t_wild_lst	*lst;

	ret = true;
	if (ft_strchr(*ptr, '*') == NULL)
		return (ret);
	if (ft_strchr(*ptr, '$'))
	{
		change_env_and_quo_and_slash(ptr, info);
		ret = false;
	}
	if ((*ptr)[0] == '/')
		current_dir = "/";
	else
		current_dir = ".";
	lst = NULL;
	get_matched_files(&lst, current_dir, word_count(*ptr, '/'), *ptr);
	if (lst == NULL)
		return (ret);
	create_sorted_files(lst, ptr, info);
	(void)i;
	if (i == 0 && ft_strchr(*ptr, ' '))
		(*ptr)[ft_strchr(*ptr, ' ') - *ptr] = '\0';
	return (ret);
}
