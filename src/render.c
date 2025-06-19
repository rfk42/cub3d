/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 01:04:29 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:04:32 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render(t_vars *vars)
{
	int	x;

	render_movement_translation(vars);
	render_movement_rotation(vars);
	render_movement_strafe(vars);
	x = 0;
	while (x < WIN_WIDTH)
	{
		render_column(vars, x);
		x++;
	}
	return (0);
}

void	render_movement_translation(t_vars *v)
{
	t_player	*p;
	double		move;

	p = &v->player;
	move = 0.05;
	if (v->key_states[XK_w])
	{
		if (v->map[(int)p->pos_y][(int)(p->pos_x + p->dir_x * move)] != '1')
			p->pos_x += p->dir_x * move;
		if (v->map[(int)(p->pos_y + p->dir_y * move)][(int)p->pos_x] != '1')
			p->pos_y += p->dir_y * move;
	}
	if (v->key_states[XK_s])
	{
		if (v->map[(int)p->pos_y][(int)(p->pos_x - p->dir_x * move)] != '1')
			p->pos_x -= p->dir_x * move;
		if (v->map[(int)(p->pos_y - p->dir_y * move)][(int)p->pos_x] != '1')
			p->pos_y -= p->dir_y * move;
	}
}

void	render_movement_strafe(t_vars *v)
{
	t_player	*p;
	double		move;

	p = &v->player;
	move = 0.05;
	if (v->key_states[XK_a])
	{
		if (v->map[(int)p->pos_y][(int)(p->pos_x - p->plane_x * move)] != '1')
			p->pos_x -= p->plane_x * move;
		if (v->map[(int)(p->pos_y - p->plane_y * move)][(int)p->pos_x] != '1')
			p->pos_y -= p->plane_y * move;
	}
	if (v->key_states[XK_d])
	{
		if (v->map[(int)p->pos_y][(int)(p->pos_x + p->plane_x * move)] != '1')
			p->pos_x += p->plane_x * move;
		if (v->map[(int)(p->pos_y + p->plane_y * move)][(int)p->pos_x] != '1')
			p->pos_y += p->plane_y * move;
	}
}

void	render_movement_rotation(t_vars *v)
{
	t_player	*p;
	double		rot;
	double		tmp;

	p = &v->player;
	if (v->key_states[XK_Left])
		rot = -0.03;
	else if (v->key_states[XK_Right])
		rot = 0.03;
	else
		return ;
	tmp = p->dir_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = tmp * sin(rot) + p->dir_y * cos(rot);
	tmp = p->plane_x;
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = tmp * sin(rot) + p->plane_y * cos(rot);
}

void	render_column(t_vars *v, int x)
{
	t_ray	r;

	calc_ray(v, &r, x);
	perform_dda(v, &r);
	if (r.side == 0)
		r.perp_wall_dist = (r.map_x - v->player.pos_x + (1 - r.step_x) / 2.0)
			/ r.ray_dir_x;
	else
		r.perp_wall_dist = (r.map_y - v->player.pos_y + (1 - r.step_y) / 2.0)
			/ r.ray_dir_y;
	draw_texture_column(v, x, &r, &v->texture[get_tex_id(&r)]);
}
