/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anikkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:24:05 by anikkane          #+#    #+#             */
/*   Updated: 2020/10/06 13:24:57 by anikkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		keypressed(int keycode)
{
	if (keycode == MAIN_PAD_ESC)
		exit(0);
	return (0);
}

int		min(int num1, int num2)
{
	return ((num1 > num2) ? num2 : num1);
}
