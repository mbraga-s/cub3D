/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:58:33 by manumart          #+#    #+#             */
/*   Updated: 2024/09/10 22:30:45 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 1024 ou 1600
// 768 ou 1200
void	init_cub3d(t_cub3d *cub3d)
{
	cub3d->move_speed = 0.25;
	cub3d->rot_spd = 0.1;
	cub3d->wn_w = 1024;
	cub3d->wn_h = 768;
	cub3d->dirx = 1;
	cub3d->diry = 0;
	cub3d->planex = 0;
	cub3d->planey = 0.66;
	cub3d->smlx.mlx = mlx_init();
	cub3d->smlx.win = mlx_new_window(cub3d->smlx.mlx, cub3d->wn_w, cub3d->wn_h,
			"cub3D");
	cub3d->smlx.img = mlx_new_image(cub3d->smlx.mlx, cub3d->wn_w, cub3d->wn_h);
	cub3d->smlx.addr = mlx_get_data_addr(cub3d->smlx.img, &cub3d->smlx.bpp,
			&cub3d->smlx.l_lgt, &cub3d->smlx.endian);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	int	i;
	int	f;

	i = 0;
	nullcub3d(&cub3d);
	if (argc != 2)
	{
		printf("Too many / few arguments.\n");
		return (0);
	}
	if (parse(argv[1], &cub3d))
		exit_error("parser error");
	// end_game(&cub3d);
	init_cub3d(&cub3d);
	printf("Ratio width: %d\n", cub3d.wn_w / cub3d.width);
	printf("Ratio height: %d\n", cub3d.wn_h / cub3d.height);
	while (i < cub3d.height)
	{
		printf("%s\n", cub3d.map.map[i]);
		i++;
	}
	draw_area(&cub3d, 0, 0, cub3d.wn_w, cub3d.wn_h);
	raycasting(&cub3d);
	draw_map(&cub3d);
	mlx_put_image_to_window(cub3d.smlx.mlx, cub3d.smlx.win, cub3d.smlx.img, 0,
		0);
	mlx_hook(cub3d.smlx.win, 17, 1, end_game, &cub3d);
	mlx_hook(cub3d.smlx.win, 2, 1L, key_hook, &cub3d);
	mlx_loop(cub3d.smlx.mlx);
}
