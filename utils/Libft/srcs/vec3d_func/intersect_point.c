/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 14:57:54 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:22:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3d_func.h"

t_p3	intersect_point(t_ray ray, double t)
{
	t_p3	res;

	res.x = ray.o.x + ray.d.x * t;
	res.y = ray.o.y + ray.d.y * t;
	res.z = ray.o.z + ray.d.z * t;
	return (res);
}
