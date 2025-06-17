/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamini <ahamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 14:35:23 by ahamini           #+#    #+#             */
/*   Updated: 2025/05/23 08:32:37 by ahamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_texture_path(char *line, int j)
{
	int		len;
	int		i;
	char	*path;

	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	path = malloc(sizeof(char) * (len - j + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		path[i++] = line[j++];
	path[i] = '\0';
	while (line[j] && (line[j] == ' ' || line[j] == '\t'))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(path);
		path = NULL;
	}
	return (path);
}

static int	fill_direction_textures(t_texinfo *textures, char *line, int j)
{
	if (line[j + 2] && !ft_isspace(line[j + 2]))
		return (ERR);
	if (line[j] == 'N' && line[j + 1] == 'O' && !(textures->north))
	textures->north = get_texture_path(line, j + 2);
	else if (line[j] == 'S' && line[j + 1] == 'O' && !(textures->south))
	textures->south = get_texture_path(line, j + 2);
	else if (line[j] == 'W' && line[j + 1] == 'E' && !(textures->west))
	textures->west = get_texture_path(line, j + 2);
	else if (line[j] == 'E' && line[j + 1] == 'A' && !(textures->east))
	textures->east = get_texture_path(line, j + 2);
	else
		return (ERR);
	return (SUCCESS);
}

static int	check_mdr_info(t_vars *vars)
{
	if (!vars->texinfo.north || !vars->texinfo.south
		|| !vars->texinfo.west || !vars->texinfo.east)
		return (err_msg("Missing texture path", FAILURE));
	if (!vars->texinfo.floor_set)
		return (err_msg("Missing floor color (F)", FAILURE));
	if (!vars->texinfo.ceiling_set)
		return (err_msg("Missing ceiling color (C)", FAILURE));
	return (SUCCESS);
}

static int	ignore_whitespaces_get_info(t_vars *vars, char **map, int i, int j)
{
	while (ft_isspace(map[i][j]))
		j++;
	if (ft_isprint(map[i][j]) && !ft_isdigit(map[i][j]))
	{
		if (ft_isupper(map[i][j]) && ft_isupper(map[i][j + 1]))
		{
			if (fill_direction_textures(&vars->texinfo, map[i], j) == ERR)
				return (err_msg("Invalid direction format", FAILURE));
			return (BREAK);
		}	
		else if ((map[i][j] == 'C' || map[i][j] == 'F') && ft_isspace(map[i][j + 1]))
		{
			if (fill_color_textures(&vars->texinfo, map[i], j) == ERR)
				return (FAILURE);
			return (BREAK);
		}
		else
			return (err_msg("Invalid texture", FAILURE));
	}
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

int	extract_map_info(t_vars *vars, char **map)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			ret = ignore_whitespaces_get_info(vars, map, i, j);
			if (ret == BREAK)
				break ;
			else if (ret == FAILURE)
				return (FAILURE);
			else if (ret == SUCCESS)
				return (SUCCESS);
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
