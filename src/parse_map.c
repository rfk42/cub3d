/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 12:43:16 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:32:56 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	error_surr(int y, int x)
{
	ft_putstr_fd(RED"Error : ", 2);
	ft_putstr_fd("Map is not surrounded at "BRED, 2);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(y, 2);
	ft_putstr_fd("]", 2);
	ft_putstr_fd("[", 2);
	ft_putnbr_fd(x, 2);
	ft_putstr_fd("]\n"RESET, 2);
	return (false);
}

bool	is_map_closed(t_mapinfo *map, char **maps)
{
	if (!check_map_borders(map, maps))
		return (false);
	if (!check_map_inside(map, maps))
		return (false);
	return (true);
}

static int	is_map_at_the_eof(t_mapinfo *map)
{
	int	i;
	int	j;

	i = map->last_line_map;
	while (map->file[i])
	{
		j = 0;
		while (map->file[i][j])
		{
			if (map->file[i][j] != ' ' && map->file[i][j] != '\t'
				&& map->file[i][j] != '\r' && map->file[i][j] != '\n'
				&& map->file[i][j] != '\v' && map->file[i][j] != '\f')
				return (FAILURE);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	parsing_map(t_vars *vars, char **map_tab)
{
	if (!vars->map || !vars->map[0])
		return (err_msg("Missing map", FAILURE));
	if (!is_map_closed(&vars->mapinfo, map_tab))
		return (FAILURE);
	if (vars->mapinfo.height < 3)
		return (err_msg("Map requires a minimum of 3 lines", FAILURE));
	if (!is_valid_char(vars, map_tab))
		return (FAILURE);
	if (is_there_a_player(vars, map_tab) == FAILURE)
		return (FAILURE);
	if (is_map_at_the_eof(&vars->mapinfo) == FAILURE)
		return (err_msg("Map is not at the end of the file", FAILURE));
	return (SUCCESS);
}
