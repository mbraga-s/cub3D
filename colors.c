/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:20:05 by manumart          #+#    #+#             */
/*   Updated: 2024/09/08 20:08:21 by manumart         ###   ########.fr       */
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

    i = 0;
    while (str[i])
    {
        if ((str[i] < '0' || str[i] > '9') && str[i] != ',')
            return (1);
        i++;
    }
    return (0);
}

int	checkrgb(char **colors, t_color *color)
{
    int	r;
    int	g;
    int	b;

    if (!colors[0] || !colors[1] || !colors[2])
    {
        free_array(colors);
        return (exit_error(" colorsC\n"), 1);
    }
    r = atoi(colors[0]);
    g = atoi(colors[1]);
    b = atoi(colors[2]);
    if ((r < 0 || r > 255) || (g < 0 || g > 255) || (b < 0 || b > 255))
    {
        free_array(colors);
        return (exit_error(" colorsD\n"), 1);
    }
    color->r = r;
    color->g = g;
    color->b = b;
    color->color = (r << 16) + (g << 8) + b;
    free_array(colors);
    return (0);
}

int	setrgb(char *colors, t_color *color)
{
    char	*str;
    char	**split;

    str = ft_strtrim(colors, "\n");
    if (!str)
        return (exit_error(" colorsB\n"), 1);
    if (iscolor(str))
    {
        free(str);
        return (exit_error(" colorsB\n"), 1);
    }
    split = ft_split(str, ',');
    free(str);
    if (!split || !split[0] || !split[1] || !split[2])
    {
        free_array(split);
        return (exit_error(" colorsA\n"), 1);
    }
    if (checkrgb(split, color))
        return (1);
    return (0);
}

int	trytofindcolors(char *line, t_cub3d *cub3d)
{
    char	**split;

    split = ft_split(line, ' ');
    if (!split || !split[0] || !split[1])
    {
        free_array(split);
        return (1);
    }
    if (ft_strncmp(split[0], "F", 2) == 0)
    {
        if (setrgb(split[1], &cub3d->map.floor.color))
        {
            free_array(split);
            return (1);
        }
    }
    else if (ft_strncmp(split[0], "C", 2) == 0)
    {
        if (setrgb(split[1], &cub3d->map.ceiling.color))
        {
            free_array(split);
            return (1);
        }
    }
    else
    {
        free_array(split);
        return (1);
    }
    free_array(split);
    return (0);
}

int	colors(int fd, t_cub3d *cub3d)
{
    char	*line;
    int		found;

    found = 0;
    line = get_next_line(fd);
    while (line && line[0] == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    if (!line)
        return (exit_error(" colorbs"), 1);
    while (line)
    {
        if (found == 2)
            break ;
        if (!trytofindcolors(line, cub3d))
            found++;
        free(line);
        line = get_next_line(fd);
    }
    if (cub3d->map.floor.color.color == -1 || cub3d->map.ceiling.color.color == -1)
    {
        free(line);
        return (exit_error(" colorsa"), 1);
    }
    free(line);
    return (0);
}