/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:25:39 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/14 13:28:57 by mbraga-s         ###   ########.fr       */
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

// Frees mlx allocated stuff, the map, prints error and exits.
void	error_end_game(t_cub3d *cub3d, char *str)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "Error\n", 6);
	}
	end_game(cub3d);
}

// Frees mlx allocated stuff, the map, and exits.
int	end_game(t_cub3d *cub3d)
{
	if (cub3d->map.no.img)
		mlx_destroy_image(cub3d->mlx, cub3d->map.no.img);
	if (cub3d->map.so.img)
		mlx_destroy_image(cub3d->mlx, cub3d->map.so.img);
	if (cub3d->map.we.img)
		mlx_destroy_image(cub3d->mlx, cub3d->map.we.img);
	if (cub3d->map.ea.img)
		mlx_destroy_image(cub3d->mlx, cub3d->map.ea.img);
	if (cub3d->scrn.img)
		mlx_destroy_image(cub3d->mlx, cub3d->scrn.img);
	if (cub3d->win)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	if (cub3d->mlx)
	{
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
	}
	free_array(cub3d->map.map);
	free_textures(cub3d);
	exit(0);
}
