/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 14:42:06 by manumart          #+#    #+#             */
/*   Updated: 2024/09/12 22:11:36 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_copy(t_cub3d *cub3d)
{
	char	**copy;
	int		i;
	int		j;

	i = -1;
	copy = ft_calloc(cub3d->height + 1, sizeof(char *));
	if (!copy)
		return (0);
	while (++i < cub3d->height)
	{
		copy[i] = ft_calloc(cub3d->width + 1, sizeof(char));
		if (!copy[i])
		{
			free_array(copy);
			return (0);
		}
		j = 0;
		while (j < cub3d->width && cub3d->map.map[i][j] != '\0')
		{
			copy[i][j] = cub3d->map.map[i][j];
			j++;
		}
		copy[i][cub3d->width] = '\0';
	}
	return (copy);
}

int	flood_fill(t_cub3d *cub3d, int x, int y, char **temp)
{
	if (x <= 0 || y <= 0 || y >= cub3d->height - 1 || x >= cub3d->width - 1)
		return (1);
	if (temp[y][x] == '1' || temp[y][x] == 'x')
		return (0);
	if (temp[y][x] == '0')
	{
		temp[y][x] = 'x';
		if (flood_fill(cub3d, x + 1, y, temp))
			return (1);
		if (flood_fill(cub3d, x - 1, y, temp))
			return (1);
		if (flood_fill(cub3d, x, y + 1, temp))
			return (1);
		if (flood_fill(cub3d, x, y - 1, temp))
			return (1);
	}
	return (0);
}

int	mainfloodfill(t_cub3d *cub3d)
{
	char	**temp;

	temp = map_copy(cub3d);
	if (!temp)
		return (1);
	else if (flood_fill(cub3d, (int)cub3d->plr.px, (int)cub3d->plr.py, temp))
	{
		free_array(temp);
		return (1);
	}
	free_array(temp);
	return (0);
}
