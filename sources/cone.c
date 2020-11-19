/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:27:54 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:30:48 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "../libft/libft.h"

static void		init_cone(t_data *data, int e, char *str)
{
	data->cone->axis[e] = vec_rot_zyx(vectornew(0, 1, 0), data->cone->rot[e]);
	data->cone->angle[e] = tan(DTR(data->cone->angle[e]));
	free(str);
}

static void		copy_cone_data(t_data *data, char *str, int *x, int e)
{
	if (*x == 0)
		data->cone->start_xyz[e].x = ft_atoi(str);
	else if (*x == 1)
		data->cone->start_xyz[e].y = ft_atoi(str);
	else if (*x == 2)
		data->cone->start_xyz[e].z = ft_atoi(str);
	else if (*x == 3)
		data->cone->angle[e] = ft_atoi(str);
	else if (*x == 4)
		data->cone->rgb2[e].red = ft_atoi(str);
	else if (*x == 5)
		data->cone->rgb2[e].green = ft_atoi(str);
	else if (*x == 6)
		data->cone->rgb2[e].blue = ft_atoi(str);
	else if (*x == 7)
		data->cone->rot[e].x = ft_atoi(str);
	else if (*x == 8)
		data->cone->rot[e].y = ft_atoi(str);
	else if (*x == 9)
		data->cone->rot[e].z = ft_atoi(str);
	*x += 1;
}

static int		count_objects(t_data *data)
{
	int			e;

	data->objnbr++;
	e = data->cone->nbr;
	data->cone->nbr++;
	return (e);
}

void			parse_cone(char *line, t_data *data)
{
	int		i;
	int		y;
	char	*str;
	int		e;
	int		x;

	i = 0;
	if (!(str = (char *)malloc(sizeof(char) * 6 + 1)))
		memory_allocation_fail();
	x = 0;
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
		copy_cone_data(data, str, &x, e);
		ft_memset(str, 0, ft_strlen(str));
	}
	init_cone(data, e, str);
}
