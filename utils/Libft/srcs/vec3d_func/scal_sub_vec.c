/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scal_sub_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 07:41:52 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:22:59 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vec3d_func.h"

t_p3	scal_sub_vec(t_p3 a, double t)
{
	t_p3	res;

	res.x = a.x - t;
	res.y = a.y - t;
	res.z = a.z - t;
	return (res);
}
