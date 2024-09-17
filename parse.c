/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 19:57:34 by manumart          #+#    #+#             */
/*   Updated: 2024/09/15 10:48:17 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_values(int fd, t_cub3d *cub3d)
{
	char	*line;
	int		foundtex;
	int		foundcolor;

	foundcolor = 0;
	foundtex = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!isempty(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (parse_loop1(cub3d, line, &foundtex, &foundcolor))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (check_value(cub3d, foundcolor, foundtex, line))
		return (1);
	if (ft_mapmain(fd, line, cub3d))
		return (1);
	return (0);
}

int	separate_values(int fd, t_cub3d *cub3d)
{
	if (find_values(fd, cub3d))
		return (1);
	if (get_plr(cub3d))
		return (1);
	if (mainfloodfill(cub3d))
		return (1);
	return (0);
}

int	parse(char *file, t_cub3d *cub3d)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (exit_error("Fd error."), 1);
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4))
	{
		close(fd);
		return (exit_error("File is not .cub"), 1);
	}
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (exit_error("Fd error"), 1);
	if (separate_values(fd, cub3d))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
