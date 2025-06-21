/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:04:24 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/21 16:21:18 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_tex_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return (0);
		else
			return (1);
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return (2);
		else
			return (3);
	}
}

static double	get_wall_hit(t_vars *v, t_ray *r)
{
	if (r->side == 0)
		return (v->player.pos_y + r->perp_wall_dist * r->ray_dir_y);
	else
		return (v->player.pos_x + r->perp_wall_dist * r->ray_dir_x);
}

static int	get_tex_x(t_ray *r, double wall_x, int tex_width)
{
	int	tex_x;

	tex_x = (int)(wall_x * (double)tex_width);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

static void	draw_pixel(t_vars *v, t_img *t, t_draw draw, int x)
{
	int			y;
	int			tex_y;
	int			color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < draw.start)
			put_pixel(&v->img, x, y, v->texinfo.ceiling_hex);
		else if (y > draw.end)
			put_pixel(&v->img, x, y, v->texinfo.floor_hex);
		else
		{
			tex_y = (y - draw.start) * t->height / draw.height;
			if (tex_y < 0 || tex_y >= t->height || draw.tex_x < 0
				|| draw.tex_x >= t->width)
			{
				y++;
				continue ;
			}
			color = ((unsigned int *)t->addr)[t->width * tex_y + draw.tex_x];
			put_pixel(&v->img, x, y, color);
		}
		y++;
	}
}

void	draw_texture_column(t_vars *v, int x, t_ray *r, t_img *t)
{
	t_draw	draw;
	double	wall_x;

	if (r->perp_wall_dist <= 0.01 || r->perp_wall_dist >= 1e6)
		return ;
	wall_x = get_wall_hit(v, r);
	wall_x -= floor(wall_x);
	draw.tex_x = get_tex_x(r, wall_x, t->width);
	draw.height = (int)(WIN_HEIGHT / r->perp_wall_dist);
	if (draw.height > WIN_HEIGHT * 10)
		draw.height = WIN_HEIGHT * 10;
	draw.start = -draw.height / 2 + WIN_HEIGHT / 2;
	if (draw.start < 0)
		draw.start = 0;
	draw.end = draw.height / 2 + WIN_HEIGHT / 2;
	if (draw.end >= WIN_HEIGHT)
		draw.end = WIN_HEIGHT - 1;
	draw_pixel(v, t, draw, x);
}
