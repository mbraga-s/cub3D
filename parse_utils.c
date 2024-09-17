/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 10:25:26 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/15 11:19:37 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	isempty(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ismap(char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str && str[i] && (str[i] == '1' || str[i] == '0'))
		return (0);
	return (1);
}

int	parse_loop1(t_cub3d *cub3d, char *line, int *foundtex, int *foundcolor)
{
	if (!line)
		return (1);
	if (!set_texture(line, &cub3d->map))
	{
		*foundtex += 1;
	}
	else if (!check_colors(line, cub3d))
		*foundcolor += 1;
	else if (!ismap(line))
		return (1);
	return (0);
}

int	check_value(t_cub3d *cub3d, int foundcolor, int foundtex, char *line)
{
	if (foundcolor != 2 || foundtex != 4 || cub3d->map.floor.color.color == -1 \
		|| cub3d->map.ceiling.color.color == -1)
	{
		free(line);
		return (exit_error("Couldn't set all colors or textures"), 1);
	}
	return (0);
}
