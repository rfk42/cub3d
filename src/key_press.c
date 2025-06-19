/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 15:18:02 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:37:59 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_vars *vars)
{
	if (keycode == XK_Escape)
		return (close_window(vars));
	if (keycode >= 0 && keycode < 65536)
		vars->key_states[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_vars *vars)
{
	if (keycode >= 0 && keycode < 65536)
		vars->key_states[keycode] = 0;
	return (0);
}

int	close_window(t_vars *vars)
{
	ft_putstr_fd("Game closed. See you next time!\n", 2);
	clean_exit(vars, 0);
	return (0);
}
