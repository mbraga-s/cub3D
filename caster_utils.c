/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:25:39 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/13 10:42:51 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//Initializes some of the values in raydata struct.
void	init_raydata(t_cub3d *cub3d, t_raydata *rd, int x)
{
	rd->camerax = 2 * x / (double)cub3d->wn_w - 1;
	rd->raydirx = cub3d->plr.dirx + cub3d->plr.planex * rd->camerax;
	rd->raydiry = cub3d->plr.diry + cub3d->plr.planey * rd->camerax;
	rd->mapx = (int)(cub3d->plr.px);
	rd->mapy = (int)(cub3d->plr.py);
	rd->sidedistx = 0;
	rd->sidedisty = 0;
	rd->perpwalldist = 0;
}

// Frees the map array Probably a duplicate function, will delete later.
int	map_free(char **maparray)
{
	int	i;

	i = 0;
	while (maparray && maparray[i])
	{
		free(maparray[i]);
		i++;
	}
	free(maparray);
	exit(0);
}

// Frees mlx allocated stuff, the map, and exits.
int	end_game(t_cub3d *cub3d)
{
	mlx_destroy_image(cub3d->mlx, cub3d->map.no.img);
	mlx_destroy_image(cub3d->mlx, cub3d->map.so.img);
	mlx_destroy_image(cub3d->mlx, cub3d->map.we.img);
	mlx_destroy_image(cub3d->mlx, cub3d->map.ea.img);
	mlx_destroy_image(cub3d->mlx, cub3d->scrn.img);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	free_array(cub3d->map.map);
	free_textures(cub3d);
	exit(0);
}

// Draws an area starting at (x1, y1) to (x2, y2) of color set in cub3D struct.
int	draw_area(t_cub3d *cub3d, int x2, int y2)
{
	int	xinc;
	int	yinc;

	yinc = 0;
	while (yinc < (y2 / 2))
	{
		xinc = 0;
		while (xinc < x2)
		{
			put_pixel(cub3d, xinc, yinc, cub3d->map.ceiling.color.color);
			xinc++;
		}
		yinc++;
	}
	while (yinc < y2)
	{
		xinc = 0;
		while (xinc < x2)
		{
			put_pixel(cub3d, xinc, yinc, cub3d->map.floor.color.color);
			xinc++;
		}
		yinc++;
	}
	return (0);
}
