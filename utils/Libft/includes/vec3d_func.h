/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjinichi <tjinichi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:40:42 by tjinichi          #+#    #+#             */
/*   Updated: 2020/12/11 21:22:33 by tjinichi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3D_FUNC_H
# define VEC3D_FUNC_H

/*
** t_p3 can be used for rgb, etc.
** (r corresponds to x.)
*/

# include <math.h>

typedef struct	s_p3
{
	double		x;
	double		y;
	double		z;
}				t_p3;

typedef struct	s_ray
{
	t_p3	o;
	t_p3	d;
}				t_ray;

t_p3			scal_times_vec(t_p3 a, double t);
t_p3			scal_sub_vec(t_p3 a, double t);
t_p3			crossproduct(t_p3 a, t_p3 b);
double			dotproduct(t_p3 a, t_p3 b);
t_p3			substract_vec(t_p3 minuend, t_p3 subtrahend);
void			normalize_vec(t_p3 *p);
double			length_vec(t_p3 a);
t_p3			intersect_point(t_ray ray, double t);
t_p3			new_vec(double x, double y, double z);
t_p3			add_vec(t_p3 a, t_p3 b);
double			distance_vec(t_p3 p1, t_p3 p2);
int				ft_stov(char *s, t_p3 *p);
double			cos_vec(t_p3 a, t_p3 b);

#endif
