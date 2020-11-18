/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:30:26 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/06 13:33:59 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vector				new_start_dir_plane(t_data *data, t_ray *ray)
{
	t_vector		scaled;
	t_vector		n;

	scaled = vectorscale(data->hit.t, ray->target);
	ray->newstart = vectoradd(ray->start, scaled);
	if (vectordot(ray->target, data->plane->normal[data->hit.obj_idx]) < 0)
		n = data->plane->normal[data->hit.obj_idx];
	else
		n = vectorscale(-1, data->plane->normal[data->hit.obj_idx]);
	return (n);
}

int						intersectplane(t_data *data, int h, t_ray ray)
{
	double			dot;
	double			t1;

	dot = vectordot(ray.target, data->plane->normal[h]);
	if (dot == 0.0)
		return (0);
	t1 = vectordot(vector_minus(data->plane->xyz[h], ray.start),
			data->plane->normal[h]) / dot;
	if (t1 < 0.001 || t1 > 9999999)
		return (0);
	if (t1 < data->hit.t)
	{
		data->hit.t = t1;
		return (1);
	}
	return (0);
}
