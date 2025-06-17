/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creation_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:12:14 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/17 14:39:45 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	calc_map_width(char **file, int start_index)
{
	int		i;
	size_t	max_len;
	size_t	current_len;

	i = start_index;
	max_len = 0;
	while (file[i])
	{
		current_len = ft_strlen(file[i]);
		if (max_len < current_len)
			max_len = current_len;
		i++;
	}
	return (max_len);
}

static int	calc_map_height(t_vars *vars, char **file, int start_index)
{
	int	i;
	int	j;
	int	height;

	i = start_index;
	height = 0;
	while (file[i])
	{
		j = 0;
		while (file[i][j] && ft_isspace(file[i][j]))
			j++;
		if (file[i][j] != '1')
			break ;
		height++;
		i++;
	}
	vars->mapinfo.last_line_map = i;
	return (height);
}

static int	copy_line_to_map_tab(char *src_line, char *dest_line, size_t width)
{
	size_t	i;

	i = 0;
	while (src_line[i] && src_line[i] != '\n' && i < width)
	{
		dest_line[i] = src_line[i];
		i++;
	}
	while (i < width)
	{
		dest_line[i] = '\0';
		i++;
	}
	dest_line[i] = '\0';
	return (SUCCESS);
}

static int	create_map_array(t_mapinfo *mapinfo, char **map_tab, int start_index)
{
	int	i;

	i = 0;
	while (i < mapinfo->height)
	{
		map_tab[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map_tab[i])
			return (err_msg("Malloc error", FAILURE));
		if (copy_line_to_map_tab(mapinfo->file[start_index + i], map_tab[i],
			mapinfo->width) == FAILURE)
			return (FAILURE);
		i++;
	}
	map_tab[i] = NULL;
	return (SUCCESS);
}

int	start_map_creation(t_vars *vars, char **file, int i)
{
	vars->mapinfo.height = calc_map_height(vars, file, i);
	vars->mapinfo.width = calc_map_width(file, i);
	vars->map = malloc(sizeof(char *) * (vars->mapinfo.height + 1));
	if (!vars->map)
		return (err_msg("Malloc error", FAILURE));
	if (create_map_array(&vars->mapinfo, vars->map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
