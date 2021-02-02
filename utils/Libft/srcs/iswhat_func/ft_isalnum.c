/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 22:03:37 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/15 03:12:36 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/iswhat_func.h"

bool	ft_isalnum(int c)
{
	return (ft_isdigit(c) || ft_isalpha(c));
}
