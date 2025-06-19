/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:53:40 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:53:48 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_direction(char **map, int i, int j)
{
	return (ft_isupper(map[i][j]) && ft_isupper(map[i][j + 1]));
}

static int	is_color(char **map, int i, int j)
{
	return ((map[i][j] == 'C' || map[i][j] == 'F') &&
			ft_isspace(map[i][j + 1]));
}

static int	handle_info_line(t_vars *vars, char **map, int i, int j)
{
	if (is_direction(map, i, j))
	{
		if (fill_direction_textures(&vars->texinfo, map[i], j) == ERR)
			return (err_msg("Invalid direction format", FAILURE));
		return (BREAK);
	}
	else if (is_color(map, i, j))
	{
		if (fill_color_textures(&vars->texinfo, map[i], j) == ERR)
			return (FAILURE);
		return (BREAK);
	}
	return (err_msg("Invalid texture", FAILURE));
}

int	ignore_whitespaces_get_info(t_vars *vars, char **map, int i, int j)
{
	while (ft_isspace(map[i][j]))
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
		return (handle_info_line(vars, map, i, j));
	else if (ft_isdigit(map[i][j]))
	{
		if (check_mdr_info(vars) == FAILURE)
			return (FAILURE);
		if (start_map_creation(vars, map, i) == FAILURE)
			return (err_msg("Invalid map", FAILURE));
		return (SUCCESS);
	}
	return (CONTINUE);
}
