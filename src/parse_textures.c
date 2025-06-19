/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 09:43:39 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:13:51 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_textures_file(char *file)
{
	int	fd;

	fd = open(file, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		ft_putstr_fd(RED"Error : ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" is a directory\n"RESET, 2);
		return (false);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd(RED"Error : File : ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(" cannot be opened or doesn't exist\n"RESET, 2);
		return (false);
	}
	close(fd);
	return (true);
}

static bool	is_xpm_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 4] != '.' || arg[len - 3] != 'x'
			|| arg[len - 2] != 'p'
			|| arg[len - 1] != 'm'))
		return (false);
	return (true);
}

static int	is_valid_rgb(int *rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_putstr_fd(RED "cub3D: Error: ", 2);
			ft_putnbr_fd(rgb[i], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("Is not in RGB range (min: 0, max: 255)\n"RESET, 2);
			return (false);
		}
		i++;
	}
	return (true);
}

static unsigned long	rgb_into_hex(int *rgb_tab)
{
	int	r;
	int	g;
	int	b;

	r = rgb_tab[0];
	g = rgb_tab[1];
	b = rgb_tab[2];
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

int	parsing_textures(t_texinfo *textures)
{
	if (!check_textures_file(textures->north)
		|| !check_textures_file(textures->south)
		|| !check_textures_file(textures->west)
		|| !check_textures_file(textures->east))
		return (FAILURE);
	if (!is_xpm_file(textures->north)
		|| !is_xpm_file(textures->north)
		|| !is_xpm_file(textures->south)
		|| !is_xpm_file(textures->east)
		|| !is_xpm_file(textures->west))
		return (err_msg("Textures is not an xpm", FAILURE));
	if (!is_valid_rgb(textures->ceiling)
		|| !is_valid_rgb(textures->floor))
		return (FAILURE);
	textures->floor_hex = rgb_into_hex(textures->floor);
	textures->ceiling_hex = rgb_into_hex(textures->ceiling);
	return (SUCCESS);
}
