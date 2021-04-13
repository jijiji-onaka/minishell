/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matched_file_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:40:15 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:49:08 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static char			*make_current_dir(char *current_dir, int depth,
						struct dirent *dp, char *asta)
{
	char	*res;

	(void)depth;
	(void)asta;
	if (asta[ft_strlen(asta) - 1] == '/')
		res = ft_strjoin(dp->d_name, "/");
	if (ft_strcmp(current_dir, ".") == 0 && (int)word_count(asta, '/') == depth)
		res = ft_strdup(dp->d_name);
	else if (ft_strcmp(current_dir, "/") == 0)
		res = ft_strjoin(current_dir, dp->d_name);
	else
		res = ft_str3join(current_dir, "/", dp->d_name);
	return (res);
}

static void			lstadd_front(t_wild_lst **lst, t_wild_lst *new)
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

static t_wild_lst	*reach_max_depth(char *asta, char *current_dir,
						t_wild_lst **lst)
{
	bool	f;
	size_t	tmp;

	f = false;
	tmp = ft_strlen(asta) - 1;
	if (asta[tmp] == '/')
		f = true;
	if (f)
		asta[tmp] = '\0';
	if (pattern_match(asta, current_dir) == true)
	{
		if (f)
		{
			asta[tmp] = '/';
			current_dir = re_strjoin(&current_dir, current_dir, "/");
		}
		lstadd_front(lst, make_wildlst(current_dir, NULL, NULL));
	}
	if (f)
		asta[tmp] = '/';
	return (*lst);
}

static bool			is_dir(char *name)
{
	struct stat	stat_buf;

	if (lstat(name, &stat_buf) != 0)
		return (0);
	return (S_ISDIR(stat_buf.st_mode));
}

t_wild_lst			*get_matched_files(t_wild_lst **lst,
							char *current_dir, int depth, char *asta)
{
	DIR				*dir;
	char			*tmp;
	struct dirent	*dp;

	if (depth == 0)
		return (reach_max_depth(asta, current_dir, lst));
	if ((dir = opendir(current_dir)) == NULL)
		return (0);
	while ((dp = readdir(dir)) != NULL)
	{
		if (asta[0] != '.' && dp->d_name[0] == '.')
			continue;
		tmp = make_current_dir(current_dir, depth, dp, asta);
		if (asta[ft_strlen(asta) - 1] == '/')
			if (is_dir(tmp) == false)
				continue ;
		if (!(get_matched_files(lst, tmp, depth - 1, asta)))
			free(tmp);
	}
	if (errno != 0)
		NULL;
	if (closedir(dir) == -1)
		NULL;
	return (NULL);
}
