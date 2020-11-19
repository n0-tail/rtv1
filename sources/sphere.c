/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:37:25 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:38:32 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "../libft/libft.h"

static void		copy_sphere_data(t_data *data, char *str, int *x, int e)
{
	if (*x == 0)
		data->sphere->xyz[e].x = ft_atoi(str);
	else if (*x == 1)
		data->sphere->xyz[e].y = ft_atoi(str);
	else if (*x == 2)
		data->sphere->xyz[e].z = ft_atoi(str);
	else if (*x == 3)
		data->sphere->radius[e] = ft_atoi(str);
	else if (*x == 4)
		data->sphere->rgb2[e].red = ft_atoi(str);
	else if (*x == 5)
		data->sphere->rgb2[e].green = ft_atoi(str);
	else if (*x == 6)
		data->sphere->rgb2[e].blue = ft_atoi(str);
	else if (*x == 7)
		data->sphere->rot_x[e] = ft_atoi(str);
	else if (*x == 8)
		data->sphere->rot_y[e] = ft_atoi(str);
	else if (*x == 9)
		data->sphere->rot_z[e] = ft_atoi(str);
	*x += 1;
}

static int		count_objects(t_data *data)
{
	int			e;

	data->objnbr++;
	e = data->sphere->nbr;
	data->sphere->nbr++;
	return (e);
}

void			parse_sphere(char *line, t_data *data)
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
		while (ft_isdigit(line[i]) == 1 && line[i] != '\0' && line[i] != '-'
				&& y < 6)
			str[y++] = line[i++];
		copy_sphere_data(data, str, &x, e);
		ft_memset(str, 0, ft_strlen(str));
	}
	free(str);
}
