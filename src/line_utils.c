/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:48:36 by rhamini           #+#    #+#             */
/*   Updated: 2025/06/20 01:12:55 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_single_texture(t_vars *v, t_img *img, char *path)
{
	img->img = mlx_xpm_file_to_image(v->mlx, path, &img->width, &img->height);
	if (!img->img)
		clean_exit(v, err_msg("Failed to load texture image", FAILURE));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		clean_exit(v, err_msg("Failed to get texture data address", FAILURE));
}

void	load_textures(t_vars *v)
{
	load_single_texture(v, &v->texture[0], v->texinfo.north);
	load_single_texture(v, &v->texture[1], v->texinfo.south);
	load_single_texture(v, &v->texture[2], v->texinfo.west);
	load_single_texture(v, &v->texture[3], v->texinfo.east);
}
