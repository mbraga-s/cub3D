/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:58:33 by manumart          #+#    #+#             */
/*   Updated: 2024/09/13 11:39:21 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_txts(t_cub3d *cub3d, t_map *map)
{
	map->no.img = mlx_xpm_file_to_image(cub3d->mlx, map->n_texture, \
		&map->no.width, &map->no.height);
	if (!map->no.img)
		exit_error("Error loading NO textures.");
	map->no.addr = mlx_get_data_addr(map->no.img, &map->no.bpp, \
			&map->no.l_lgt, &map->no.endian);
	map->so.img = mlx_xpm_file_to_image(cub3d->mlx, map->s_texture, \
		&map->so.width, &map->so.height);
	if (!map->so.img)
		exit_error("Error loading SO textures.");
	map->so.addr = mlx_get_data_addr(map->so.img, &map->so.bpp, \
			&map->so.l_lgt, &map->so.endian);
	map->we.img = mlx_xpm_file_to_image(cub3d->mlx, map->w_texture, \
		&map->we.width, &map->we.height);
	if (!map->we.img)
		exit_error("Error loading WE textures.");
	map->we.addr = mlx_get_data_addr(map->we.img, &map->we.bpp, \
			&map->we.l_lgt, &map->we.endian);
	map->ea.img = mlx_xpm_file_to_image(cub3d->mlx, map->e_texture, \
		&map->ea.width, &map->ea.height);
	if (!map->ea.img)
		exit_error("Error loading EA textures.");
	map->ea.addr = mlx_get_data_addr(map->ea.img, &map->ea.bpp, \
			&map->ea.l_lgt, &map->ea.endian);
}

// 1024 ou 1600
// 768 ou 1200
void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->wn_w = 1024;
	cub3d->wn_h = 768;
	cub3d->plr.rot_spd = 0.01;
	cub3d->plr.mv_spd = 0.015;
	cub3d->plr.planex = -cub3d->plr.diry * tan(33 * PI / 180);
	cub3d->plr.planey = cub3d->plr.dirx * tan(33 * PI / 180);
	cub3d->mlx = mlx_init();
	if (!cub3d->mlx)
		exit_error("Error loading mlx.\n");
	else
	{
		cub3d->win = mlx_new_window(cub3d->mlx, cub3d->wn_w, cub3d->wn_h, \
			"cub3D");
		if (!cub3d->win)
			exit_error("Error loading mlx.\n");
		cub3d->scrn.img = mlx_new_image(cub3d->mlx, cub3d->wn_w, cub3d->wn_h);
		if (!cub3d->scrn.img)
			exit_error("Error loading mlx.\n");
		else
			cub3d->scrn.addr = mlx_get_data_addr(cub3d->scrn.img, \
				&cub3d->scrn.bpp, &cub3d->scrn.l_lgt, &cub3d->scrn.endian);
	}
	load_txts(cub3d, &cub3d->map);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;

	nullcub3d(&cub3d);
	if (argc != 2)
	{
		printf("Too many / few arguments.\n");
		return (0);
	}
	if (parse(argv[1], &cub3d))
		exit_error("parser error");
	init_cub3d(&cub3d);
	// draw_area(&cub3d, cub3d.wn_w, cub3d.wn_h);
	raycasting(&cub3d);
	// draw_map(&cub3d);
	mlx_put_image_to_window(cub3d.mlx, cub3d.win, cub3d.scrn.img, 0, \
		0);
	mlx_hook(cub3d.win, 17, 1, end_game, &cub3d);
	mlx_hook(cub3d.win, 2, 1L, key_hook, &cub3d);
	mlx_loop(cub3d.mlx);
}
