/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:12:07 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/19 12:22:32 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

static void	free_texinfo(t_texinfo *textures)
{
	if (textures->north)
		free(textures->north);
	if (textures->south)
		free(textures->south);
	if (textures->west)
		free(textures->west);
	if (textures->east)
		free(textures->east);
	if (textures->floor)
		free(textures->floor);
	if (textures->ceiling)
		free(textures->ceiling);
}

void	free_textures(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (vars->texture[i].img)
			mlx_destroy_image(vars->mlx, vars->texture[i].img);
		i++;
	}
}

static void	free_map(t_vars *vars)
{
	if (vars->mapinfo.fd > 0)
		close(vars->mapinfo.fd);
	if (vars->mapinfo.file)
		free_tab((void **)vars->mapinfo.file);
	if (vars->map)
		free_tab((void **)vars->map);
}

int	free_vars(t_vars *vars)
{
	free_texinfo(&vars->texinfo);
	free_map(vars);
	return (FAILURE);
}

void	clean_exit(t_vars *vars, int code)
{
	if (!vars)
		exit(code);
	if (vars->win && vars->mlx)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
	{
		free_textures(vars);
		mlx_destroy_display(vars->mlx);
		mlx_loop_end(vars->mlx);
		free(vars->mlx);
	}
	free_vars(vars);
	exit(code);
}
