/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sort_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:31:11 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/13 14:03:24 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../bonus_includes/minishell_bonus.h"

static t_envlst	*make_envlst(t_string key, t_string value,
						t_envlst *next, t_envlst *qnext)
{
	t_envlst	*new;

	new = malloc(sizeof(t_envlst));
	if (new == NULL)
		return (NULL);
	new->env.key = key;
	new->env.value = value;
	new->next = next;
	new->qnext = qnext;
	return (new);
}

static bool	initial_enqueue(t_envlst **qhead,
					t_envlst **tail, t_envlst *lst)
{
	*qhead = make_envlst(lst->env.key, lst->env.value, NULL, NULL);
	if (*qhead == NULL)
		return (false);
	*tail = *qhead;
	lst = lst->next;
	while (lst)
	{
		(*tail)->qnext = make_envlst(lst->env.key, lst->env.value, NULL, NULL);
		if ((*tail)->qnext == NULL)
			return (false);
		(*tail) = (*tail)->qnext;
		lst = lst->next;
	}
	return (true);
}

static t_envlst	*dequeue(t_envlst **qhead)
{
	t_envlst	*ret;
	t_envlst	*tmp;

	ret = make_envlst((*qhead)->env.key,
			(*qhead)->env.value, (*qhead)->next, NULL);
	if (ret == NULL)
		return (NULL);
	tmp = (*qhead)->qnext;
	free(*qhead);
	*qhead = tmp;
	return (ret);
}

static t_envlst	*merge(t_envlst *cmp1, t_envlst *cmp2)
{
	t_envlst	head;
	t_envlst	*res;

	res = &head;
	while (cmp1 && cmp2)
	{
		if (ft_strcmp(cmp1->env.key.str, cmp2->env.key.str) < 0)
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

t_envlst	*merge_lst_sort(t_envlst *lst)
{
	t_envlst	*cmp1;
	t_envlst	*cmp2;
	t_envlst	*qhead;
	t_envlst	*tail;
	t_envlst	*res;

	if (initial_enqueue(&qhead, &tail, lst) == false)
		return (NULL);
	res = dequeue(&qhead);
	if (res == NULL)
		return (destroy_queue(&qhead));
	while (qhead)
	{
		tail->qnext = res;
		tail = tail->qnext;
		cmp1 = dequeue(&qhead);
		if (cmp1 == NULL)
			return (destroy_queue(&qhead));
		cmp2 = dequeue(&qhead);
		if (cmp2 == NULL)
			return (destroy_queue(&qhead));
		res = merge(cmp1, cmp2);
	}
	return (res);
}
