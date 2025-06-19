/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 08:30:55 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:24:34 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_mlx(t_vars *vars)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
		clean_exit(vars, err_msg("Can't start mlx", 1));
	vars->win = mlx_new_window(vars->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!vars->win)
		clean_exit(vars, err_msg("Can't create mlx window", 1));
	return ;
}

static int	start_parsing(int ac, char **av, t_vars *vars)
{
	if (!parse_args(av, ac))
		return (FAILURE);
	init_data(vars);
	if (parse_data(av[1], vars) != 0)
		return (FAILURE);
	if (extract_map_info(vars, vars->mapinfo.file) == FAILURE)
		return (FAILURE);
	if (!vars->map || !vars->map[0])
	{
		err_msg("Map is missing", FAILURE);
		return (FAILURE);
	}
	if (parsing_map(vars, vars->map) == FAILURE)
		return (FAILURE);
	if (parsing_textures(&vars->texinfo) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	start_mlx(t_vars *vars)
{
	init_player_direction(vars);
	init_mlx(vars);
	load_textures(vars);
	mlx_do_key_autorepeaton(vars->mlx);
	mlx_hook(vars->win, KeyPress, KeyPressMask, key_press, vars);
	mlx_hook(vars->win, KeyRelease, KeyReleaseMask, key_release, vars);
	mlx_hook(vars->win, 17, 0, close_window, vars);
	mlx_loop_hook(vars->mlx, render, vars);
	mlx_loop(vars->mlx);
}

int	main(int ac, char **av)
{
	t_vars	vars;

	if (start_parsing(ac, av, &vars) == FAILURE)
		return (free_vars(&vars), 1);
	start_mlx(&vars);
	clean_exit(&vars, 0);
	return (0);
}
