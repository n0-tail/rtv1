/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:25:37 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 13:02:11 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void			init_plane(t_data *data, int e, char *str)
{
	data->plane->normal[e] = rotate_vector(data->plane->xyz[e],
			data->plane->normal[e], data->plane->rot[e], 0);
	data->plane->normal[e] = vector_minus(data->plane->normal[e],
			data->plane->xyz[e]);
	data->plane->normal[e] = normalized_vector(data->plane->normal[e]);
	free(str);
}

static void			copy_plane_data(t_data *data, char *str, int *x, int e)
{
	if (*x == 0)
		data->plane->xyz[e].x = ft_atoi(str);
	else if (*x == 1)
		data->plane->xyz[e].y = ft_atoi(str);
	else if (*x == 2)
		data->plane->xyz[e].z = ft_atoi(str);
	else if (*x == 3)
		data->plane->normal[e].x = ft_atoi(str);
	else if (*x == 4)
		data->plane->normal[e].y = ft_atoi(str);
	else if (*x == 5)
		data->plane->normal[e].z = ft_atoi(str);
	else if (*x == 6)
		data->plane->rgb2[e].red = ft_atoi(str);
	else if (*x == 7)
		data->plane->rgb2[e].green = ft_atoi(str);
	else if (*x == 8)
		data->plane->rgb2[e].blue = ft_atoi(str);
	else if (*x == 9)
		data->plane->rot[e].x = ft_atoi(str);
	else if (*x == 10)
		data->plane->rot[e].y = ft_atoi(str);
	else if (*x == 11)
		data->plane->rot[e].z = ft_atoi(str);
	*x += 1;
}

static int			count_objects(t_data *data)
{
	int			e;

	data->objnbr++;
	e = data->plane->nbr;
	data->plane->nbr++;
	return (e);
}

void				parse_plane(char *line, t_data *data)
{
	int			i;
	int			y;
	char		*str;
	int			e;
	int			x;

	i = 0;
	x = 0;
	if (!(str = (char *)malloc(sizeof(char) * 6 + 1)))
		memory_allocation_fail();
	e = count_objects(data);
	while (line[i] != '\0')
	{
		y = 0;
		while (ft_isdigit(line[i]) == 0 && line[i] != '\0' && line[i] != '-')
			i++;
		str = if_negative(line, str, &i, &y);
		while (ft_isdigit(line[i]) == 1 && line[i] != '\0' &&
				line[i] != '-' && y < 6)
			str[y++] = line[i++];
		copy_plane_data(data, str, &x, e);
		ft_memset(str, 0, ft_strlen(str));
	}
	init_plane(data, e, str);
}
