/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:53:39 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:57:02 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		init_cylinder(t_data *data, int e, char *str)
{
	data->cylinder->end_xyz[e] = rotate_vector(data->cylinder->start_xyz[e],
			data->cylinder->end_xyz[e], data->cylinder->rot[e], 0);
	data->cylinder->axis[e] = vector_minus(data->cylinder->start_xyz[e],
			data->cylinder->end_xyz[e]);
	data->cylinder->axis[e] = normalized_vector(data->cylinder->axis[e]);
	free(str);
}

static void		copy_cylinder_color(t_data *data, char *str, int *x, int e)
{
	if (*x == 7)
		data->cylinder->rgb2[e].red = ft_atoi(str);
	else if (*x == 8)
		data->cylinder->rgb2[e].green = ft_atoi(str);
	else if (*x == 9)
		data->cylinder->rgb2[e].blue = ft_atoi(str);
}

static void		copy_cylinder_data(t_data *data, char *str, int *x, int e)
{
	if (*x == 0)
		data->cylinder->start_xyz[e].x = ft_atoi(str);
	else if (*x == 1)
		data->cylinder->start_xyz[e].y = ft_atoi(str);
	else if (*x == 2)
		data->cylinder->start_xyz[e].z = ft_atoi(str);
	else if (*x == 3)
		data->cylinder->end_xyz[e].x = ft_atoi(str);
	else if (*x == 4)
		data->cylinder->end_xyz[e].y = ft_atoi(str);
	else if (*x == 5)
		data->cylinder->end_xyz[e].z = ft_atoi(str);
	else if (*x == 6)
		data->cylinder->radius[e] = ft_atoi(str);
	else if (*x == 7 || *x == 8 || *x == 9)
		copy_cylinder_color(data, str, x, e);
	else if (*x == 10)
		data->cylinder->rot[e].x = ft_atoi(str);
	else if (*x == 11)
		data->cylinder->rot[e].y = ft_atoi(str);
	else if (*x == 12)
		data->cylinder->rot[e].z = ft_atoi(str);
	*x += 1;
}

static int		count_objects(t_data *data)
{
	int			e;

	data->objnbr++;
	e = data->cylinder->nbr;
	data->cylinder->nbr++;
	return (e);
}

void			parse_cylinder(char *line, t_data *data)
{
	int		i;
	int		y;
	char	*str;
	int		e;
	int		x;

	x = 0;
	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * 6 + 1)))
		memory_allocation_fail();
	e = count_objects(data);
	while (line[i] != '\0')
	{
		y = 0;
		while (ft_isdigit(line[i]) == 0 && line[i] != '\0' && line[i] != '-')
			i++;
		str = if_negative(line, str, &i, &y);
		while (ft_isdigit(line[i]) == 1 && line[i] != '\0' && line[i] != '-' &&
				y < 6)
			str[y++] = line[i++];
		copy_cylinder_data(data, str, &x, e);
		ft_memset(str, 0, ft_strlen(str));
	}
	init_cylinder(data, e, str);
}
