/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:12 by manumart          #+#    #+#             */
/*   Updated: 2024/09/15 11:19:45 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	compare_textures(t_map *map, char **split)
{
	if (ft_strncmp(split[0], "NO", 3) == 0)
	{
		if (!map->n_texture)
			map->n_texture = ft_strtrim(split[1], "\n ");
	}
	else if (ft_strncmp(split[0], "SO", 3) == 0)
	{
		if (!map->s_texture)
			map->s_texture = ft_strtrim(split[1], "\n ");
	}
	else if (ft_strncmp(split[0], "WE", 3) == 0)
	{
		if (!map->w_texture)
			map->w_texture = ft_strtrim(split[1], "\n ");
	}
	else if (ft_strncmp(split[0], "EA", 3) == 0)
	{
		if (!map->e_texture)
			map->e_texture = ft_strtrim(split[1], "\n ");
	}
	else
		return (1);
	return (0);
}

int	set_texture(char *line, t_map *map)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	i = 0;
	while (split && split[i])
		i++;
	if (i != 2)
		return (free_array(split), 1);
	if (compare_textures(map, split))
		return (free_array(split), 1);
	else
		return (free_array(split), 0);
}
