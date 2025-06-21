/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 12:01:05 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/21 16:49:38 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	no_digit(char *str)
{
	int		i;
	bool	found_no_digit;

	i = 0;
	found_no_digit = true;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			found_no_digit = false;
		i++;
	}
	return (found_no_digit);
}

static int	*copy_into_rgb_array(char **rgb_to_convert, int *rgb)
{
	int		i;

	i = -1;
	while (rgb_to_convert[++i])
	{
		rgb[i] = ft_atoi(rgb_to_convert[i]);
		if (rgb[i] == -1 || no_digit(rgb_to_convert[i]) == true)
		{
			free_tab((void **)rgb_to_convert);
			free(rgb);
			return (0);
		}
	}
	free_tab((void **)rgb_to_convert);
	return (rgb);
}

static int	*set_rgb_colors(char *line)
{
	char	**rgb_to_convert;
	int		*rgb;
	int		count;

	rgb_to_convert = ft_split(line, ',');
	count = 0;
	while (rgb_to_convert[count])
		count++;
	if (count != 3)
	{
		free_tab((void **)rgb_to_convert);
		return (0);
	}
	rgb = malloc(sizeof(int) * 3);
	if (!rgb)
	{
		err_msg("Malloc error during rgb set up", 0);
		return (0);
	}
	return (copy_into_rgb_array(rgb_to_convert, rgb));
}

static int	check_rgb_line(char *line)
{
	int	i;

	i = 1;
	while (ft_isspace(line[i]))
		line++;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && line[i] != ',' && line[i] != '\n')
		{
			return (err_msg("Invalid character in RGB line", ERR));
		}
		i++;
	}
	return (SUCCESS);
}

int	fill_color_textures(t_texinfo *textures, char *line, int j)
{
	if (check_rgb_line(line) == ERR)
		return (ERR);
	if (line[j + 1] && !ft_isspace(line[j + 1]))
		return (err_msg("Invalid floor or ceiling format", ERR));
	if (!textures->ceiling_set && line[j] == 'C')
	{
		textures->ceiling = set_rgb_colors(line + j + 1);
		if (textures->ceiling == 0)
			return (err_msg("Invalid RGB color for ceiling", ERR));
		textures->ceiling_set = 1;
	}
	else if (!textures->floor_set && line[j] == 'F')
	{
		textures->floor = set_rgb_colors(line + j + 1);
		if (textures->floor == 0)
			return (err_msg("Invalid RGB color for floor", ERR));
		textures->floor_set = 1;
	}
	else
		return (err_msg("Invalid floor or ceiling format", ERR));
	return (SUCCESS);
}
