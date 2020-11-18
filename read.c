/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:18:21 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/06 13:23:02 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char			*if_negative(char *line, char *str, int *i, int *y)
{
	if (line[*i] == '-')
	{
		if (str[0] != '\0')
			data_read_error();
		str[0] = '-';
		*i += 1;
		*y = 1;
	}
	return (str);
}

static void		check_name(t_data *data, char *data_name, char *line)
{
	if (ft_strcmp(data_name, "SPHERE") == 0)
		parse_sphere(line, data);
	else if (ft_strcmp(data_name, "CYLINDER") == 0)
		parse_cylinder(line, data);
	else if (ft_strcmp(data_name, "CONE") == 0)
		parse_cone(line, data);
	else if (ft_strcmp(data_name, "SPOT") == 0)
		parse_spot(line, data);
	else if (ft_strcmp(data_name, "PLANE") == 0)
		parse_plane(line, data);
	else if (ft_strcmp(data_name, "CAMERA") == 0)
		parse_camera(line, data);
}

static char		*parse_name(char *line, char *tmp)
{
	int		i;
	int		y;

	i = 1;
	y = 0;
	if (line[i++] == ' ')
	{
		while (line[i] != ' ')
			tmp[y++] = line[i++];
	}
	free(line);
	return (tmp);
}

int				read_scene(const int fd, t_data *data)
{
	char	*line;
	char	*data_name;
	int		i;
	int		x;

	if (!(data_name = (char *)malloc(sizeof(char) * ft_strlen(line))))
		memory_allocation_fail();
	x = 0;
	i = 0;
	while ((get_next_line(fd, &line)) == 1)
	{
		if (line[i] == '*')
		{
			data_name = parse_name(line, data_name);
			get_next_line(fd, &line);
		}
		check_name(data, data_name, line);
		ft_memset(data_name, 0, ft_strlen(data_name));
		free(line);
	}
	free(data_name);
	return (0);
}
