/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 11:41:16 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:53:16 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static t_ray		reflection_direction(t_ray ray, t_vector n)
{
	t_vector	tmp;
	double		reflect;

	ray.start = vector_copy(ray.newstart);
	reflect = 3.5f * vectordot(ray.target, n);
	tmp = vectorscale(reflect, n);
	ray.target = vector_minus(ray.target, tmp);
	return (ray);
}

static void			search_intersection(t_data *data, t_ray ray)
{
	int			i;

	i = data->objnbr - 1;
	data->hit.obj_idx = -1;
	data->hit.t = 1000.0;
	data->hit.find_shadow = 0;
	while (i >= 0)
	{
		if (data->cylinder->nbr > i && intersectcylinder(ray, data, i) == 1)
			set_hit(data, "cylinder", i);
		if (data->sphere->nbr > i && intersectsphere(ray, data, i) == 1)
			set_hit(data, "sphere", i);
		if (data->plane->nbr > i && intersectplane(data, i, ray) == 1)
			set_hit(data, "plane", i);
		if (data->cone->nbr > i && intersectcone(ray, data, i) == 1)
			set_hit(data, "cone", i);
		i--;
	}
}

static t_ray		new_hit_direction(t_data *data, t_ray org_ray, t_vector *n)
{
	double		temp;
	t_ray		ray;

	ray.newstart = vector_copy(org_ray.newstart);
	ray.start = vector_copy(org_ray.start);
	ray.target = vector_copy(org_ray.target);
	if (ft_strcmp(data->hit.obj_name, "cone") == 0)
		*n = new_start_dir_cone(data, &ray);
	if (ft_strcmp(data->hit.obj_name, "sphere") == 0)
	{
		*n = new_start_dir_sphere(data, &ray);
		temp = vectordot(*n, *n);
		if (temp == 0)
		{
			n->x = 101010;
			return (ray);
		}
		temp = 1.0f / sqrt(temp);
		*n = vectorscale(temp, *n);
	}
	if (ft_strcmp(data->hit.obj_name, "plane") == 0)
		*n = new_start_dir_plane(data, &ray);
	if (ft_strcmp(data->hit.obj_name, "cylinder") == 0)
		*n = new_start_dir_cylinder(data, &ray);
	return (ray);
}

static t_rgb		search_light_and_shadow(t_data *data, t_ray ray,
		t_vector n, t_rgb rgb)
{
	int			i;

	ray.target = vector_copy(n);
	i = (data->spot->nbr - 1);
	while (i >= 0)
	{
		if (data->iter == data->org_iter)
		{
			if (shadow(data, ray.newstart, i) != 1)
				rgb = get_light(data, rgb, ray, i);
		}
		else
			rgb = get_light(data, rgb, ray, i);
		i--;
	}
	return (rgb);
}

void				get_color(t_data *data, int x, int y)
{
	t_vector	n;
	t_rgb		rgb;
	t_ray		ray;

	ray = init_pixel(data, x, y, &rgb);
	while (data->iter > 0 && data->light_scale > 0.0f)
	{
		search_intersection(data, ray);
		if (data->hit.obj_idx == -1)
			break ;
		ray = new_hit_direction(data, ray, &n);
		if (n.x == 101010)
			break ;
		rgb = search_light_and_shadow(data, ray, n, rgb);
		data->iter--;
		ray = reflection_direction(ray, n);
		put_color(data, rgb, x, y);
	}
}
