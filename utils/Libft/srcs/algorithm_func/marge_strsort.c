/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marge_strsort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 23:34:18 by tjinichi          #+#    #+#             */
/*   Updated: 2021/01/27 19:47:55 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/algorithm_func.h"

/*
** Make sure that the cmp_by function returns 1, 0, or -1.
** and The third argument of marge_strsort, end, means the end of \
** the index number.
*/

static int	merge(char **array, t_index info, char **work, int (*cmp_by)())
{
	size_t	i;
	size_t	j;
	int		rc;

	if (info.begin >= info.end)
		return (EXIT_SUCCESS);
	i = info.begin - 1;
	while (++i <= info.mid)
		work[i] = array[i];
	i = info.mid;
	while (++i <= info.end)
		work[info.end - (i - (info.mid + 1))] = array[i];
	i = info.begin - 1;
	j = info.end;
	while (++i <= j)
	{
		rc = cmp_by(work[info.begin], work[info.end]);
		if (rc == INT_MIN)
			return (EXIT_FAILURE);
		if (rc <= 0)
			array[i] = work[info.begin++];
		else
			array[i] = work[info.end--];
	}
	return (EXIT_SUCCESS);
}

int			merge_strsort(char **array, size_t begin, \
				size_t end, int (*cmp_by)())
{
	char		**work;
	size_t		i;
	size_t		j;
	t_index		info;

	if (!(work = malloc(sizeof(char *) * (end - begin + 1))))
		return (1);
	i = 1;
	while (i <= end - begin)
	{
		j = begin;
		while (j <= end - i)
		{
			info.begin = j;
			info.end = MIN(j + i * 2 - 1, end);
			info.mid = j + i - 1;
			merge(array, info, work, cmp_by);
			j += i * 2;
		}
		i *= 2;
	}
	free(work);
	return (0);
}
