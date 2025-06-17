/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:10:56 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/16 18:10:59 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_ray(t_vars *v, t_ray *r, int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	r->ray_dir_x = v->player.dir_x + v->player.plane_x * camera_x;
	r->ray_dir_y = v->player.dir_y + v->player.plane_y * camera_x;
	r->map_x = (int)v->player.pos_x;
	r->map_y = (int)v->player.pos_y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
	r->hit = 0;
	init_ray_step_x(v, r);
	init_ray_step_y(v, r);
}

void	init_ray_step_x(t_vars *v, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (v->player.pos_x - r->map_x)
			* r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - v->player.pos_x)
			* r->delta_dist_x;
	}
}

void	init_ray_step_y(t_vars *v, t_ray *r)
{
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (v->player.pos_y - r->map_y)
			* r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - v->player.pos_y)
			* r->delta_dist_y;
	}
}

void	perform_dda(t_vars *vars, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (vars->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	draw_vertical_line(t_vars *vars, t_line line)
{
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < line.start)
			mlx_pixel_put(vars->mlx, vars->win, line.x, y,
				vars->texinfo.ceiling_hex);
		else if (y >= line.start && y <= line.end)
			mlx_pixel_put(vars->mlx, vars->win, line.x, y, line.color);
		else
			mlx_pixel_put(vars->mlx, vars->win, line.x, y,
				vars->texinfo.floor_hex);
		y++;
	}
}
