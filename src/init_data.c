/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:13:50 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/19 12:17:00 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_textinfo(t_texinfo *textures)
{
	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->floor = 0;
	textures->floor_hex = 0x0;
	textures->floor_set = 0;
	textures->ceiling = 0;
	textures->ceiling_hex = 0x0;
	textures->ceiling_set = 0;
}

static void	init_mapinfo(t_mapinfo *mapinfo)
{
	mapinfo->fd = 0;
	mapinfo->line_count = 0;
	mapinfo->path = NULL;
	mapinfo->file = NULL;
	mapinfo->height = 0;
	mapinfo->width = 0;
	mapinfo->last_line_map = 0;
}

void	init_data(t_vars *vars)
{
	ft_bzero(vars, sizeof(t_vars));
	ft_bzero(vars->key_states, sizeof(vars->key_states));
	memset(vars->texture, 0, sizeof(vars->texture));
	vars->mlx = NULL;
	vars->win = NULL;
	vars->win_height = WIN_HEIGHT;
	vars->win_width = WIN_WIDTH;
	vars->map = NULL;
	init_mapinfo(&vars->mapinfo);
	init_textinfo(&vars->texinfo);
}
