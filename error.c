/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 10:21:21 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/06 13:29:38 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "rtv1.h"

void	memory_allocation_fail(void)
{
	ft_putendl("Memory allocation failed.");
	exit(1);
}

void	data_read_error(void)
{
	ft_putendl("data read error, wrong syntax.");
	exit(1);
}
