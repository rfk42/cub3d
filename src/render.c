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

int get_tex_id(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x < 0)
			return 0; // NO
		else
			return 1; // SO
	}
	else
	{
		if (ray->ray_dir_y < 0)
			return 2; // WE
		else
			return 3; // EA
	}
}

void draw_texture_column(t_vars *v, int x, t_ray *r, t_img *t)
{
	int		line_h;
	int		y;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	wall_x;

	if (r->side == 0)
		wall_x = v->player.pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = v->player.pos_x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * (double)t->width);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		tex_x = t->width - tex_x - 1;
	line_h = (int)(WIN_HEIGHT / r->perp_wall_dist);
	draw_start = -line_h / 2 + WIN_HEIGHT / 2;
	draw_end = line_h / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		if (y < draw_start)
			mlx_pixel_put(v->mlx, v->win, x, y, v->texinfo.ceiling_hex);
		else if (y > draw_end)
			mlx_pixel_put(v->mlx, v->win, x, y, v->texinfo.floor_hex);
		else
		{
			int tex_y = (y - draw_start) * t->height / line_h;
			int color = ((unsigned int *)t->addr)[t->width * tex_y + tex_x];
			mlx_pixel_put(v->mlx, v->win, x, y, color);
		}
		y++;
	}
}

void render_column(t_vars *v, int x)
{
	t_ray r;

	calc_ray(v, &r, x);
	perform_dda(v, &r);
	if (r.side == 0)
		r.perp_wall_dist = (r.map_x - v->player.pos_x
			+ (1 - r.step_x) / 2.0) / r.ray_dir_x;
	else
		r.perp_wall_dist = (r.map_y - v->player.pos_y
			+ (1 - r.step_y) / 2.0) / r.ray_dir_y;
	draw_texture_column(v, x, &r, &v->texture[get_tex_id(&r)]);
}
