/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:10:56 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/21 16:21:30 by rhamini          ###   ########.fr       */
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
		r->side_dist_x = (v->player.pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - v->player.pos_x) * r->delta_dist_x;
	}
}

void	init_ray_step_y(t_vars *v, t_ray *r)
{
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (v->player.pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - v->player.pos_y) * r->delta_dist_y;
	}
}

void	perform_dda(t_vars *v, t_ray *r)
{
	int		limit;

	limit = 400;
	while (r->hit == 0 && limit-- > 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_y < 0 || r->map_y >= v->mapinfo.height
			|| r->map_x < 0 || r->map_x >= (int)ft_strlen(v->map[r->map_y]))
			break ;
		if (v->map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
