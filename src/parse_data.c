/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhamini <rhamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:18:37 by ahamini           #+#    #+#             */
/*   Updated: 2025/06/17 14:26:39 by rhamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(char *path)
{
	int		fd;
	char	*line;
	int		line_count;

	line = NULL;
	line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		err_msg(strerror(errno), errno);
	else
	{
		line = get_next_line(fd);
		while (line != NULL)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

static void	fill_tab(int row, int column, int i, t_vars *vars)
{
	char	*line;

	line = get_next_line(vars->mapinfo.fd);
	while (line != NULL)
	{
		vars->mapinfo.file[row] = ft_calloc(ft_strlen(line) + 1, sizeof(char));
		if (!vars->mapinfo.file[row])
		{
			err_msg("Malloc error", 0);
			return (free_tab((void **)vars->mapinfo.file));
		}
		while (line[i] != '\0')
			vars->mapinfo.file[row][column++] = line[i++];
		vars->mapinfo.file[row++][column] = '\0';
		column = 0;
		i = 0;
		free(line);
		line = get_next_line(vars->mapinfo.fd);
	}
	vars->mapinfo.file[row] = NULL;
}

int	parse_data(char *path, t_vars *vars)
{
	int		row;
	int		i;
	size_t	column;

	i = 0;
	row = 0;
	column = 0;
	vars->mapinfo.line_count = count_lines(path);
	if (vars->mapinfo.line_count == 0)
		return (err_msg("Map file is empty", 1));
	vars->mapinfo.path = path;
	vars->mapinfo.file = ft_calloc(vars->mapinfo.line_count \
			+ 1, sizeof(char *));
	if (!(vars->mapinfo.file))
		return (err_msg("Malloc error", 1));
	vars->mapinfo.fd = open(path, O_RDONLY);
	if (vars->mapinfo.fd < 0)
		err_msg(strerror(errno), 1);
	else
	{
		fill_tab(row, column, i, vars);
		close(vars->mapinfo.fd);
	}
	return (0);
}
