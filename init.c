/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:47:32 by manumart          #+#    #+#             */
/*   Updated: 2024/09/14 13:37:25 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	nullcub3d(t_cub3d *cub3d)
{
	cub3d->map.map = NULL;
	cub3d->map.floor.color.color = -1;
	cub3d->map.ceiling.color.color = -1;
	cub3d->map.floor.color.r = -1;
	cub3d->map.floor.color.g = -1;
	cub3d->map.floor.color.b = -1;
	cub3d->map.ceiling.color.r = -1;
	cub3d->map.ceiling.color.g = -1;
	cub3d->map.ceiling.color.b = -1;
	cub3d->map.n_texture = NULL;
	cub3d->map.s_texture = NULL;
	cub3d->map.w_texture = NULL;
	cub3d->map.e_texture = NULL;
	cub3d->plr.dirx = 0;
	cub3d->plr.diry = 0;
}

// Loads the given textures into mlx imgs. Returns an error if it fails.
void	load_txts(t_cub3d *cub3d, t_map *map)
{
	map->no.img = mlx_xpm_file_to_image(cub3d->mlx, map->n_texture, \
		&map->no.w, &map->no.h);
	if (!map->no.img)
		error_end_game(cub3d, "Error loading NO textures.\n");
	map->no.addr = mlx_get_data_addr(map->no.img, &map->no.bpp, \
			&map->no.l_lgt, &map->no.endian);
	map->so.img = mlx_xpm_file_to_image(cub3d->mlx, map->s_texture, \
		&map->so.w, &map->so.h);
	if (!map->so.img)
		error_end_game(cub3d, "Error loading SO textures.\n");
	map->so.addr = mlx_get_data_addr(map->so.img, &map->so.bpp, \
			&map->so.l_lgt, &map->so.endian);
	map->we.img = mlx_xpm_file_to_image(cub3d->mlx, map->w_texture, \
		&map->we.w, &map->we.h);
	if (!map->we.img)
		error_end_game(cub3d, "Error loading WE textures.\n");
	map->we.addr = mlx_get_data_addr(map->we.img, &map->we.bpp, \
			&map->we.l_lgt, &map->we.endian);
	map->ea.img = mlx_xpm_file_to_image(cub3d->mlx, map->e_texture, \
		&map->ea.w, &map->ea.h);
	if (!map->ea.img)
		error_end_game(cub3d, "Error loading EA textures.\n");
	map->ea.addr = mlx_get_data_addr(map->ea.img, &map->ea.bpp, \
			&map->ea.l_lgt, &map->ea.endian);
}

// Initializes the mlx, the window, and the screen img
void	init_mlx(t_cub3d *cub3d)
{
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		error_end_game(cub3d, "Error loading mlx.\n");
	else
	{
		load_txts(cub3d, &cub3d->map);
		cub3d->win = mlx_new_window(cub3d->mlx, cub3d->wn_w, cub3d->wn_h, \
			"cub3D");
		if (!cub3d->win)
			error_end_game(cub3d, "Error loading mlx.\n");
		cub3d->scrn.img = mlx_new_image(cub3d->mlx, cub3d->wn_w, cub3d->wn_h);
		if (!cub3d->scrn.img)
			error_end_game(cub3d, "Error loading mlx.\n");
		else
			cub3d->scrn.addr = mlx_get_data_addr(cub3d->scrn.img, \
				&cub3d->scrn.bpp, &cub3d->scrn.l_lgt, &cub3d->scrn.endian);
	}
}

// Initializes some values needed for raycasting as well as the mlx
void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->ws_flag = 0;
	cub3d->ad_flag = 0;
	cub3d->lr_flag = 0;
	cub3d->win = NULL;
	cub3d->scrn.img = NULL;
	cub3d->map.no.img = NULL;
	cub3d->map.so.img = NULL;
	cub3d->map.we.img = NULL;
	cub3d->map.ea.img = NULL;
	cub3d->wn_w = 1024;
	cub3d->wn_h = 768;
	cub3d->plr.rot_spd = 0.01;
	cub3d->plr.mv_spd = 0.015;
	cub3d->plr.planex = -cub3d->plr.diry * tan(33 * PI / 180);
	cub3d->plr.planey = cub3d->plr.dirx * tan(33 * PI / 180);
	init_mlx(cub3d);
}
