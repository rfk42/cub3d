/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:44:58 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:51:39 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "../mlx/mlx.h"
# include <stddef.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <X11/X.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>
# include <math.h>

# define RED	"\033[0;31m"
# define BRED		"\033[1;31m"
# define RESET "\033[0m"

# define WIN_WIDTH 1000
# define WIN_HEIGHT 600

# ifndef O_DIRECTORY
#  define O_DIRECTORY 00200000
# endif

enum e_output
{
	SUCCESS = 0,
	FAILURE = 1,
	ERR = 2,
	BREAK = 3,
	CONTINUE = 4
};

typedef struct s_texinfo
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				*floor;
	int				*ceiling;
	int				floor_set;
	int				ceiling_set;
	unsigned long	floor_hex;
	unsigned long	ceiling_hex;
}	t_texinfo;

typedef struct s_player
{
	char	dir;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		has_moved;
	int		move_x;
	int		move_y;
	int		rotate;
}	t_player;

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	char		*path;
	char		**file;
	int			height;
	int			width;
	int			last_line_map;
}	t_mapinfo;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	int			win_height;
	int			win_width;
	t_texinfo	texinfo;
	t_mapinfo	mapinfo;
	t_player	player;
	char		**map;
	int			key_states[65536];
	t_img		texture[4];
}	t_vars;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_ray;

typedef struct s_draw
{
	int		tex_x;
	int		height;
	int		start;
	int		end;
}	t_draw;

int		main(int ac, char **av);
int		extract_map_info(t_vars *vars, char **map);
int		check_mdr_info(t_vars *vars);
int		ignore_whitespaces_get_info(t_vars *vars, char **map, int i, int j);
int		fill_direction_textures(t_texinfo *textures, char *line, int j);
char	*get_texture_path(char *line, int j);
int		fill_color_textures(t_texinfo *textures, char *line, int j);
int		err_msg(char *str, int code);
bool	parse_args(char **argv, int ac);
bool	check_file(char *fill);
void	init_data(t_vars *vars);
int		parse_data(char *path, t_vars *vars);
void	*ft_calloc(size_t nmemb, size_t size);
int		start_map_creation(t_vars *vars, char **file, int i);
int		parsing_map(t_vars *vars, char **map_tab);
bool	error_surr(int y, int x);
bool	check_map_borders(t_mapinfo *map, char **maps);
bool	check_surroundings(char **maps, int y, int i);
bool	check_map_inside(t_mapinfo *map, char **maps);
bool	is_valid_char(t_vars *vars, char **map_tab);
int		is_there_a_player(t_vars *vars, char **map_tab);
int		parsing_textures(t_texinfo *textures);
void	free_tab(void **tab);
void	free_textures(t_vars *vars);
int		free_vars(t_vars *vars);
void	clean_exit(t_vars *vars, int code);
int		key_press(int keycode, t_vars *vars);
int		key_release(int keycode, t_vars *vars);
int		close_window(t_vars *vars);
void	init_player_direction(t_vars *vars);
int		render(t_vars *vars);
void	render_column(t_vars *v, int x);
void	render_movement_translation(t_vars *v);
void	render_movement_strafe(t_vars *v);
void	render_movement_rotation(t_vars *v);
void	calc_ray(t_vars *v, t_ray *r, int x);
void	init_ray_step_x(t_vars *v, t_ray *r);
void	init_ray_step_y(t_vars *v, t_ray *r);
void	perform_dda(t_vars *vars, t_ray *ray);
void	load_textures(t_vars *v);
int		get_tex_id(t_ray *ray);
void	draw_texture_column(t_vars *v, int x, t_ray *r, t_img *t);

#endif