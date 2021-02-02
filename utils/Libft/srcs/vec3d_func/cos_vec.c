/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos_vec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:50:10 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:22:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3d_func.h"

double		cos_vec(t_p3 a, t_p3 b)
{
	return (dotproduct(a, b) / (length_vec(a) * length_vec(b)));
}
