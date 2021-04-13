/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_sort_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:44:00 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 16:14:02 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

t_wild_lst	*make_wildlst(char *value,
						t_wild_lst *next, t_wild_lst *qnext)
{
	t_wild_lst	*new;

	new = malloc(sizeof(t_wild_lst));
	if (new == NULL)
		return (NULL);
	new->value = value;
	new->next = next;
	new->qnext = qnext;
	return (new);
}

static bool	initial_enqueue(t_wild_lst **qhead,
						t_wild_lst **tail, t_wild_lst *lst)
{
	t_wild_lst	*begin;
	t_wild_lst	*next;

	*qhead = make_wildlst(lst->value, NULL, NULL);
	if (*qhead == NULL)
		return (false);
	*tail = *qhead;
	begin = lst;
	lst = lst->next;
	while (lst)
	{
		next = lst->next;
		(*tail)->qnext = make_wildlst(lst->value, NULL, NULL);
		if ((*tail)->qnext == NULL)
			return (false);
		(*tail) = (*tail)->qnext;
		free(lst);
		lst = next;
	}
	free(begin);
	return (true);
}

static t_wild_lst	*dequeue(t_wild_lst **qhead)
{
	t_wild_lst	*ret;
	t_wild_lst	*tmp;

	ret = make_wildlst((*qhead)->value, (*qhead)->next, NULL);
	if (ret == NULL)
		return (NULL);
	tmp = (*qhead)->qnext;
	free(*qhead);
	*qhead = tmp;
	return (ret);
}

static t_wild_lst	*merge(t_wild_lst *cmp1, t_wild_lst *cmp2)
{
	t_wild_lst	head;
	t_wild_lst	*res;
	int			tmp;

	res = &head;
	while (cmp1 && cmp2)
	{
		if (ft_strcmp(cmp1->value, cmp2->value) < 0)
		{
			res->next = cmp1;
			res = cmp1;
			cmp1 = cmp1->next;
		}
		else
		{
			res->next = cmp2;
			res = cmp2;
			cmp2 = cmp2->next;
		}
	}
	if (cmp1 == NULL)
		res->next = cmp2;
	else
		res->next = cmp1;
	return (head.next);
}

t_wild_lst	*file_sort(t_wild_lst *lst)
{
	t_wild_lst	*cmp1;
	t_wild_lst	*cmp2;
	t_wild_lst	*qhead;
	t_wild_lst	*tail;

	if (initial_enqueue(&qhead, &tail, lst) == false)
		return (NULL);
	lst = dequeue(&qhead);
	if (lst == NULL)
		return (destroy_queue_(&qhead));
	while (qhead)
	{
		tail->qnext = lst;
		tail = tail->qnext;
		cmp1 = dequeue(&qhead);
		if (cmp1 == NULL)
			return (destroy_queue_(&qhead));
		cmp2 = dequeue(&qhead);
		if (cmp2 == NULL)
			return (destroy_queue_(&qhead));
		lst = merge(cmp1, cmp2);
	}
	return (lst);
}
