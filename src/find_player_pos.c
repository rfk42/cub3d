/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:41:50 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/17 14:52:55 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	process_line(t_vars *vars, char *line, int y, int *player_found)
{
	int	x;
	int	line_len;

	x = 0;
	line_len = (int)ft_strlen(line);
	while (x < line_len)
	{
		if (ft_strchr("NSEW", line[x]))
		{
			if (*player_found)
				return (err_msg("More than one player", FAILURE));
			vars->player.pos_x = (double)x + 0.5;
			vars->player.pos_y = (double)y + 0.5;
			vars->player.dir = line[x];
			line[x] = '0';
			*player_found = 1;
		}
		x++;
	}
	return (SUCCESS);
}

int	is_there_a_player(t_vars *vars, char **map_tab)
{
	int	y;
	int	player_found;
	int	ret;

	y = 0;
	player_found = 0;
	while (y < vars->mapinfo.height)
	{
		ret = process_line(vars, map_tab[y], y, &player_found);
		if (ret == FAILURE)
			return (FAILURE);
		y++;
	}
	if (!player_found)
		return (err_msg("No player found", FAILURE));
	return (SUCCESS);
}
