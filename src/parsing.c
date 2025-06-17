/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 09:49:00 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/17 14:24:31 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	bool	err_extension(char *str, int i, bool hidden)
{
	ft_putstr_fd(RED"Error\nThe file is not ending with .cub\n", 2);
	ft_putstr_fd(RED"Actual extension: "BRED, 2);
	ft_putstr_fd(str + i, 2);
	if (hidden)
		ft_putstr_fd(" (hidden file)"RESET, 2);
	ft_putstr_fd(RESET"\n", 2);
	return (false);
}

static int	extension_index(char *str)
{
	int		i;

	i = ft_strlen(str) - 1;
	while (str[i] && i > 0)
	{
		if (str[i] == '.')
			break ;
		--i;
	}
	return (i);
}

bool	check_file_name(char *str)
{
	int		i;

	i = extension_index(str);
	if (!ft_strcmp(str + i, ".cub") && str[i - 1] && str[i - 1] != '/')
		return (true);
	else
	{
		if (str[i - 1] == '/')
		{
			return (err_extension(str, i, true));
		}
		else
			return (err_extension(str, i, false));
	}
}

static bool	check_arg_and_name(int ac, char **av)
{
	if (ac != 2)
	{
		ft_putstr_fd(RED"Error : Incorrect number of arguments.\n", 2);
		ft_putstr_fd(BRED"Usage: ./cub3d 'map_file'\n"RESET, 2);
		return (false);
	}
	if (!check_file_name(av[1]))
		return (false);
	return (true);
}

bool	parse_args(char **av, int ac)
{
	if (!check_arg_and_name(ac, av))
		return (false);
	if (!check_file(av[1]))
		return (false);
	return (true);
}