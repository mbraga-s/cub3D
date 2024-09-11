/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:12 by manumart          #+#    #+#             */
/*   Updated: 2024/09/08 20:12:02 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	free_textures(t_cub3d *cub3d)
{
	if (cub3d->map.n_texture)
		free(cub3d->map.n_texture);
	if (cub3d->map.s_texture)
		free(cub3d->map.s_texture);
	if (cub3d->map.w_texture)
		free(cub3d->map.w_texture);
	if (cub3d->map.e_texture)
		free(cub3d->map.e_texture);
}

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
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
		return (!!ft_free_tab(split));
	if (!ft_strncmp(split[0], "NO", 3) && !map->n_texture)
		map->n_texture = ft_strtrim(split[1], "\n ");
	else if (!ft_strncmp(split[0], "SO", 3) && !map->s_texture)
		map->s_texture = ft_strtrim(split[1], "\n ");
	else if (!ft_strncmp(split[0], "WE", 3) && !map->w_texture)
		map->w_texture = ft_strtrim(split[1], "\n ");
	else if (!ft_strncmp(split[0], "EA", 3) && !map->e_texture)
		map->e_texture = ft_strtrim(split[1], "\n ");
	else
		return (!!ft_free_tab(split));
	ft_free_tab(split);
	return (1);
}

int	trytofindtextures(int fd, t_cub3d *cub3d)
{
	int		found;
	char	*line;

	found = 0;
	line = get_next_line(fd);
	while (line)
	{
		// printf("%d : %s", found, line);
		if (set_texture(line, &cub3d->map))
			found++;
		free(line);
		line = get_next_line(fd);
		if (found == 4)
			break ;
	}
	free(line);
	if (found != 4)
		return (exit_error("Missing textures"), 1);
	return (0);
}

int	textures(int fd, t_cub3d *cub3d)
{
	trytofindtextures(fd, cub3d);
	if (cub3d->map.n_texture == NULL || cub3d->map.s_texture == NULL
		|| cub3d->map.w_texture == NULL || cub3d->map.e_texture == NULL)
	{
		// printf("NO: %s\n", cub3d->map.n_texture);
		// printf("SO: %s\n", cub3d->map.s_texture);
		// printf("WE: %s\n", cub3d->map.w_texture);
		// printf("EA: %s\n", cub3d->map.e_texture);
		return (1);
	}
	// printf("\n\n\nTextures found\n");
	// printf("NO: %s\n", cub3d->map.n_texture);
	// printf("SO: %s\n", cub3d->map.s_texture);
	// printf("WE: %s\n", cub3d->map.w_texture);
	// printf("EA: %s\n", cub3d->map.e_texture);
	return (0);
}
