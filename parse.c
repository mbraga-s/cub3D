/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:57:34 by manumart          #+#    #+#             */
/*   Updated: 2024/09/11 16:23:28 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	separate_values(int fd, t_cub3d *cub3d)
{
	if (textures(fd, cub3d))
		return (1);
	printf("Textures parsed\n");
	if (colors(fd, cub3d))
		return (1);
	printf("Colors parsed\n");
	if (ft_mapmain(fd, cub3d))
		return (1);
	if (get_plr(cub3d))
		return (1);
	printf("Player found\n");
	if (mainfloodfill(cub3d))
		return (1);
	printf("Map parsed\n");
	return (0);
}

int	parse(char *file, t_cub3d *cub3d)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (exit_error("fd error"), 1);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
	{
		close(fd);
		return (exit_error("file is not .cub"), 1);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (exit_error("fd error"), 1);
	if (separate_values(fd, cub3d))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
