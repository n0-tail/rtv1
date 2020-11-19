/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 13:07:41 by anikkane          #+#    #+#             */
/*   Updated: 2020/11/18 12:39:52 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "../libft/libft.h"
#include "stdio.h"

static void		copy_spot_data(t_data *data, char *str, int x, int e)
{
	if (x == 0)
		data->spot->x[e] = ft_atoi(str);
	else if (x == 1)
		data->spot->y[e] = ft_atoi(str);
	else if (x == 2)
		data->spot->z[e] = ft_atoi(str);
	else if (x == 3)
		data->spot->power[e] = ft_atoi(str);
}

static int		count_objects(t_data *data)
{
	int			e;

	e = data->spot->nbr;
	data->spot->nbr++;
	return (e);
}

void			parse_spot(char *line, t_data *data)
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
		while (ft_isdigit(line[i]) == 0 && line[i] != '\0' && line[i] != '-')
			i++;
		y = 0;
		str = if_negative(line, str, &i, &y);
		while (ft_isdigit(line[i]) == 1 && line[i] != '\0' && line[i] !=
				'-' && y < 6)
			str[y++] = line[i++];
		copy_spot_data(data, str, x, e);
		x++;
		ft_memset(str, 0, ft_strlen(str));
	}
	free(str);
}
