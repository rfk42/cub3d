/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:32:29 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:32:47 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_map_borders(t_mapinfo *map, char **maps)
{
	int	i;

	i = 0;
	while (maps[0][i])
	{
		if (maps[0][i] != '1')
			return (error_surr(0, i));
		i++;
	}
	i = 0;
	while (maps[map->height - 1][i])
	{
		if (maps[map->height - 1][i] != '1')
			return (error_surr(map->height - 1, i));
		i++;
	}
	return (true);
}

bool	check_surroundings(char **maps, int y, int i)
{
	if (maps[y][i + 1] != '0' && maps[y][i + 1] != '1'
		&& !ft_isalpha(maps[y][i + 1]))
		return (error_surr(y, i + 1));
	if (maps[y][i - 1] != '0' && maps[y][i - 1] != '1'
		&& !ft_isalpha(maps[y][i - 1]))
		return (error_surr(y, i - 1));
	if (maps[y + 1][i] != '0' && maps[y + 1][i] != '1'
		&& !ft_isalpha(maps[y + 1][i]))
		return (error_surr(y + 1, i));
	if (maps[y - 1][i] != '0' && maps[y - 1][i] != '1'
		&& !ft_isalpha(maps[y - 1][i]))
		return (error_surr(y - 1, i));
	return (true);
}

bool	check_map_inside(t_mapinfo *map, char **maps)
{
	int	y;
	int	i;

	y = 1;
	while (y < map->height - 1)
	{
		i = 0;
		while (maps[y][i])
		{
			if (maps[y][i] == '0' || ft_isalpha(maps[y][i]))
			{
				if (!check_surroundings(maps, y, i))
					return (false);
			}
			i++;
		}
		y++;
	}
	return (true);
}
