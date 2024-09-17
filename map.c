/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:27:29 by manumart          #+#    #+#             */
/*   Updated: 2024/09/15 10:47:43 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**ft_realloc(char **map)
{
	char	**new_map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (map && map[i])
		i++;
	new_map = ft_calloc(i + 2, sizeof(char *));
	if (!new_map)
		return (NULL);
	while (j < i)
	{
		new_map[j] = map[j];
		j++;
	}
	new_map[i] = NULL;
	free(map);
	return (new_map);
}

int	ft_parse_map(t_cub3d *cub3d)
{
	char	*chars;
	int		i;
	int		j;

	i = 0;
	j = 0;
	chars = "01NSEW ";
	while (cub3d->map.map[i])
	{
		j = 0;
		while (cub3d->map.map[i][j])
		{
			if (!ft_strchr(chars, cub3d->map.map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_get_map(int fd, char *line, t_cub3d *cub3d)
{
	int	i;
	int	width;

	width = 0;
	i = 0;
	cub3d->map.map = ft_calloc(2, sizeof(char *));
	while (line)
	{
		cub3d->map.map[i] = ft_strtrim(line, "\n");
		if (ft_strlen(cub3d->map.map[i]) > width)
			width = ft_strlen(cub3d->map.map[i]);
		cub3d->map.map = ft_realloc(cub3d->map.map);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	if (line)
		free(line);
	cub3d->height = i;
	cub3d->width = width;
	return (0);
}

int	ft_mapmain(int fd, char *line, t_cub3d *cub3d)
{
	cub3d->map.map = NULL;
	cub3d->width = 0;
	if (ft_get_map(fd, line, cub3d))
		return (exit_error("Map error."), 1);
	if (ft_parse_map(cub3d))
	{
		return (1);
	}
	return (0);
}
