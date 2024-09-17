/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:20:05 by manumart          #+#    #+#             */
/*   Updated: 2024/09/15 10:31:19 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	iscolor(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str && str[i] && (str[i] != '\n'))
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ',' && str[i] != ' ')
			return (1);
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count > 2)
		return (1);
	return (0);
}

int	checkrgb(char **colors, t_color *color)
{
	int	r;
	int	g;
	int	b;

	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		free_array(colors);
		return (1);
	}
	r = atoi(colors[0]);
	g = atoi(colors[1]);
	b = atoi(colors[2]);
	if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
	{
		free_array(colors);
		return (1);
	}
	color->color = (r << 16) + (g << 8) + b;
	free_array(colors);
	return (0);
}

int	validate_colors(char *line, t_color *color)
{
	char	*str;
	char	**split;

	if (iscolor(line))
		return (1);
	str = ft_strtrim(line, "\n");
	split = ft_split(str, ',');
	free(str);
	if (!split || !split[0] || !split[1] || !split[2])
	{
		free_array(split);
		return (1);
	}
	if (checkrgb(split, color))
		return (1);
	return (0);
}

int	check_colors(char *line, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (line && line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F')
	{
		i++;
		if (validate_colors(&line[i], &cub3d->map.floor.color))
			return (1);
	}
	else if (line[i] == 'C')
	{
		i++;
		if (validate_colors(&line[i], &cub3d->map.ceiling.color))
			return (1);
	}
	else
		return (1);
	return (0);
}

int	colors(int fd, t_cub3d *cub3d)
{
	char	*line;
	int		found;

	found = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (found == 2)
			break ;
		if (!check_colors(line, cub3d))
			found++;
		free(line);
		line = get_next_line(fd);
	}
	if (cub3d->map.floor.color.color == -1 || \
		cub3d->map.ceiling.color.color == -1)
	{
		free(line);
		return (free_textures(cub3d), 1);
	}
	free(line);
	return (0);
}
