/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:35:22 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:35:49 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
