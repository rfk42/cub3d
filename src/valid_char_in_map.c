/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_char_in_map.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:56:38 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/17 14:25:31 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	error_char(char c, int y, int x)
{
	ft_putstr_fd(RED"Error\n"BRED, 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(RED" is not a valid character at ", 2);
	ft_putstr_fd(BRED"[", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd("][", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd("]\n"RESET, 2);
	return (false);
}

bool	is_valid_char(t_vars *vars, char **map_tab)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < vars->mapinfo.height)
	{
		x = 0;
		while (x < vars->mapinfo.width && map_tab[y][x])
		{
			c = map_tab[y][x];
			if (!(c == '0' || c == '1' || c == ' ' || c == 'N'
					|| c == 'S' || c == 'E' || c == 'W'))
				return (error_char(map_tab[y][x], y, x));
			x++;
		}
		y++;
	}
	return (true);
}