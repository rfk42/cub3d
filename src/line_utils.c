/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:48:36 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/17 14:48:46 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_line	build_line(int x, int y0, int y1, int color)
{
	t_line	l;

	l.x = x;
	l.start = y0;
	l.end = y1;
	l.color = color;
	return (l);
}

int	get_wall_color(int side)
{
	if (side == 1)
		return (0xAAAAAA);
	return (0xFFFFFF);
}
