/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envlst_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 00:31:11 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/08 07:59:12 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static t_envlst	*make_envlst(t_string key, t_string value,
						t_envlst *next, t_envlst *qnext)
{
	t_envlst	*new;
	// char		*equ_ptr;
	// size_t		key_len;

	new = malloc(sizeof(t_envlst));
	if (new == NULL)
		return (NULL);
	new->env.key = key;
	new->env.value = value;
	new->next = next;
	new->qnext = qnext;
	return (new);
}

static bool		initial_enqueue(t_envlst **qhead,
					t_envlst **tail, t_envlst *lst)
{
	if (!(*qhead = make_envlst(lst->env.key, lst->env.value, NULL, NULL)))
		return (false);
	*tail = *qhead;
	lst = lst->next;
	while (lst)
	{
		if (!((*tail)->qnext = make_envlst(lst->env.key, lst->env.value, NULL, NULL)))
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

	if (!(ret = make_envlst((*qhead)->env.key, (*qhead)->env.value, (*qhead)->next, NULL)))
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
	int			tmp;

	res = &head;
	while (cmp1 && cmp2)
	{
		if ((tmp = ft_strcmp(cmp1->env.key.str, cmp2->env.key.str)) < 0)
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

t_envlst		*merge_lst_sort(t_envlst *lst)
{
	t_envlst	*cmp1;
	t_envlst	*cmp2;
	t_envlst	*qhead;
	t_envlst	*tail;
	t_envlst	*res;

	if (initial_enqueue(&qhead, &tail, lst) == false)
		return (NULL);
	if (!(res = dequeue(&qhead)))
		return (destroy_queue(&qhead));
	while (qhead)
	{
		tail->qnext = res;
		tail = tail->qnext;
		if (!(cmp1 = dequeue(&qhead)))
			return (destroy_queue(&qhead));
		if (!(cmp2 = dequeue(&qhead)))
			return (destroy_queue(&qhead));
		res = merge(cmp1, cmp2);
	}
	return (res);
}
