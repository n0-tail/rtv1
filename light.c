/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:09:10 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/06 13:16:51 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static double		get_lambert(t_data *data, t_vector n,
		t_vector newstart, t_vector dist)
{
	t_ray		lightray;
	double		lambert;

	lightray.start = newstart;
	lightray.target = vectorscale((1 / (data->hit.t)), dist);
	lambert = vectordot(lightray.target, n) * data->light_scale;
	data->light_scale *= 0.9;
	return (lambert);
}

static t_vector		get_dist(t_vector light_pos, t_vector newstart)
{
	t_vector	dist;

	dist = (vector_minus(light_pos, newstart));
	return (dist);
}

static t_material	get_material(t_data *data, int i)
{
	t_material	material;

	material.diffuse_red = ((double)data->spot->power[i] / 100);
	material.diffuse_green = ((double)data->spot->power[i] / 100);
	material.diffuse_blue = ((double)data->spot->power[i] / 100);
	if ((ft_strcmp(data->hit.obj_name, "plane") == 0) &&
			data->iter != data->org_iter)
	{
		material.diffuse_red = 0.05;
		material.diffuse_green = 0.05;
		material.diffuse_blue = 0.05;
	}
	return (material);
}

static t_rgb		get_light_intensity(t_data *data, int h)
{
	t_rgb		intensity;
	t_rgb2		color;

	if (ft_strcmp(data->hit.obj_name, "cone") == 0)
		color = data->cone->rgb2[h];
	else if (ft_strcmp(data->hit.obj_name, "sphere") == 0)
		color = data->sphere->rgb2[h];
	else if (ft_strcmp(data->hit.obj_name, "plane") == 0)
		color = data->plane->rgb2[h];
	else
		color = data->cylinder->rgb2[h];
	intensity.red = ((double)color.red / 125);
	intensity.green = ((double)color.green / 125);
	intensity.blue = ((double)color.blue / 125);
	return (intensity);
}

t_rgb				 get_light(t_data *data, t_rgb rgb, t_vector newstart,
		t_vector n, int i)
{
	t_material	material;
	t_vector	light_pos;
	t_rgb		intensity;
	int			h;

	h = data->hit.obj_idx;
	light_pos.x = data->spot->x[i];
	light_pos.y = data->spot->y[i];
	light_pos.z = data->spot->z[i];
	intensity = get_light_intensity(data, h);
	if (vectordot(n, get_dist(light_pos, newstart)) <= 0.0f)
		return (rgb);
	data->hit.t = sqrt(vectordot(get_dist(light_pos, newstart),
				get_dist(light_pos, newstart)));
	if (data->hit.t <= 0.0f)
		return (rgb);
	material = get_material(data, i);
	rgb.red += get_lambert(data, n, newstart, get_dist(light_pos, newstart))
		* intensity.red * material.diffuse_red;
	rgb.green += get_lambert(data, n, newstart, get_dist(light_pos, newstart))
		* intensity.green * material.diffuse_green;
	rgb.blue += get_lambert(data, n, newstart, get_dist(light_pos, newstart))
		* intensity.blue * material.diffuse_blue;
	return (rgb);
}
