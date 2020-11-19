/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:37:51 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:51:34 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				init_camera(t_data *data)
{
	t_vector		camera_pos;
	t_vector		target;
	t_vector		cam_direction;
	t_vector		cam_up;
	t_vector		cam_right;

	camera_pos = vector_copy(data->camera->xyz);
	target = vector_copy(data->camera->target);
	target = rotate_vector(camera_pos, target, data->camera->rot, 1);
	cam_direction = vector_minus(target, camera_pos);
	cam_direction = normalized_vector(cam_direction);
	cam_up = vectornew(0, -1, 0);
	cam_right = cross_vector(cam_up, cam_direction);
	cam_right = normalized_vector(cam_right);
	cam_up = cross_vector(cam_right, cam_direction);
	data->camera->direction = vector_copy(cam_direction);
	data->camera->up = vector_copy(cam_up);
	data->camera->right = vector_copy(cam_right);
}

static void			copy_camera_data(t_data *data, char *str, int x)
{
	if (x == 0)
		data->camera->xyz.x = ft_atoi(str);
	else if (x == 1)
		data->camera->xyz.y = ft_atoi(str);
	else if (x == 2)
		data->camera->xyz.z = ft_atoi(str);
	else if (x == 3)
		data->camera->target.x = ft_atoi(str);
	else if (x == 4)
		data->camera->target.y = ft_atoi(str);
	else if (x == 5)
		data->camera->target.z = ft_atoi(str);
	else if (x == 6)
		data->camera->rot.x = ft_atoi(str);
	else if (x == 7)
		data->camera->rot.y = ft_atoi(str);
	else if (x == 8)
		data->camera->rot.z = ft_atoi(str);
}

void				parse_camera(char *line, t_data *data)
{
	int				i;
	int				y;
	char			*str;
	int				x;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * 6 + 1)))
		memory_allocation_fail();
	x = 0;
	while (line[i] != '\0')
	{
		y = 0;
		while (ft_isdigit(line[i]) == 0 && line[i] != '\0' && line[i] != '-')
			i++;
		str = if_negative(line, str, &i, &y);
		while (ft_isdigit(line[i]) == 1 && line[i] != '\0' &&
				line[i] != '-' && y < 6)
			str[y++] = line[i++];
		copy_camera_data(data, str, x);
		x++;
		ft_memset(str, 0, ft_strlen(str));
	}
	init_camera(data);
	free(str);
}
