/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_spaces_in_2d_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 01:30:47 by tjinichi          #+#    #+#             */
/*   Updated: 2021/02/02 17:26:29 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static bool	spaces_or_not_in_array(char **arr, int *element_num, int *i)
{
	bool	flag;

	*i = -1;
	*element_num = 0;
	flag = false;
	while (arr[++(*i)])
	{
		if (arr[(*i)][0] == ' ')
		{
			if (skip_space(arr[(*i)])[0] == '\0')
			{
				flag = true;
				continue ;
			}
		}
		(*element_num)++;
	}
	return (flag);
}

static char	**create_no_spaces_array(char **new, char **old)
{
	int		i;
	int		new_index;

	i = -1;
	new_index = 0;
	while (old[++i])
	{
		if (old[i][0] == ' ')
		{
			if (skip_space(old[i])[0] == '\0')
			{
				ptr_free((void **)&old[i]);
				continue ;
			}
		}
		new[new_index++] = old[i];
	}
	new[new_index] = NULL;
	return (new);
}

char		**rm_spaces_in_2d_array(char **arr, t_minishell_info *info)
{
	int		i;
	int		element_num;
	char	**res;

	if (spaces_or_not_in_array(arr, &element_num, &i) == false)
		return (arr);
	if (!(res = malloc(sizeof(char *) * (element_num + 1))))
	{
		ptr_2d_free((void ***)&arr, i);
		all_free_exit(info, ERR_MALLOC, __LINE__, __FILE__);
	}
	res = create_no_spaces_array(res, arr);
	ptr_2d_free((void ***)&arr, 0);
	return (res);
}
