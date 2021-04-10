/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:50:10 by tjinichi          #+#    #+#             */
/*   Updated: 2021/04/09 03:22:19 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3d_func.h"

double	cos_vec(t_p3 a, t_p3 b)
{
	double	a_len;
	double	b_len;

	a_len = length_vec(a);
	b_len = length_vec(b);
	return (dotproduct(a, b) / (a_len * b_len));
}
