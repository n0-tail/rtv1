/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:11:19 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/06 13:36:57 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double		get_discr_cylinder(t_data *data, t_vector to_x,
		t_vector ray_x, int h)
{
	double			abc[3];

	abc[0] = vectordot(ray_x, ray_x);
	abc[1] = 2 * vectordot(ray_x, to_x);
	abc[2] = vectordot(to_x, to_x) - (data->cylinder->radius[h] *
			data->cylinder->radius[h] *
			vectordot(data->cylinder->axis[h], data->cylinder->axis[h]));
	data->hit.a = abc[0];
	data->hit.b = abc[1];
	return ((abc[1] * abc[1]) - (4 * abc[0] * abc[2]));
}

t_vector			new_start_dir_cylinder(t_data *data, t_ray *ray)
{
	t_vector		scaled;
	t_vector		n;
	double			m;

	scaled = vectorscale(data->hit.t, ray->target);
	m = vectordot(ray->target, data->cylinder->axis[data->hit.obj_idx]) *
		data->hit.t + vectordot(vector_minus(ray->start,
					data->cylinder->start_xyz[data->hit.obj_idx]),
				data->cylinder->axis[data->hit.obj_idx]);
	ray->newstart = vectoradd(ray->start, scaled);
	n = normalized_vector(vector_minus(vector_minus(ray->newstart,
					data->cylinder->start_xyz[data->hit.obj_idx]),
				vectorscale(m, data->cylinder->axis[data->hit.obj_idx])));
	if (vectordot(ray->target, n) > 0.0001)
		n = vectorscale(-1, n);
	return (n);
}

int					intersectcylinder(t_ray ray, t_data *data, int h)
{
	double			discr;
	double			t[2];
	t_vector		to;
	t_vector		to_x;
	t_vector		ray_x;

	if (data->hit.find_shadow == 1)
	{
		data->hit.t = 1000.0;
		ray.target = vector_minus(ray.target, ray.start);
		ray.target = normalized_vector(ray.target);
	}
	to = vectorsub(ray.start, data->cylinder->start_xyz[h]);
	to_x = cross_vector(to, data->cylinder->axis[h]);
	ray_x = cross_vector(ray.target, data->cylinder->axis[h]);
	discr = get_discr_cylinder(data, to_x, ray_x, h);
	if (discr < 0)
		return (0);
	else
	{
		t[0] = (-data->hit.b + (sqrt(discr))) / (2 * data->hit.a);
		t[1] = (-data->hit.b - (sqrt(discr))) / (2 * data->hit.a);
		if (t[0] > t[1])
			t[0] = t[1];
		if ((t[0] > 0.001f) && (t[0] < data->hit.t))
		{
			data->hit.t = t[0];
			return (1);
		}
		return (0);
	}
}
