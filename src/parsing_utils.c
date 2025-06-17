/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 09:33:18 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/17 14:25:07 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_file(char *file)
{
	int	fd;

	if ((fd = open(file, O_DIRECTORY)) != -1)
	{
		ft_putstr_fd(RED"Error : Invalide : is a directory\n"RESET, 2);
		return (false);
	}
	if ((fd = open(file, O_RDONLY)) == -1)
	{
		ft_putstr_fd(RED"Error : File .cub invalide\n", 2);
		return (false);
	}
	close(fd);
	return (true);
}