/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:58:33 by manumart          #+#    #+#             */
/*   Updated: 2024/09/14 13:31:19 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	raycasting(&cub3d);
	mlx_put_image_to_window(cub3d.mlx, cub3d.win, cub3d.scrn.img, 0, \
		0);
	mlx_hook(cub3d.win, 2, 1L << 0, key_hook_press, &cub3d);
	mlx_hook(cub3d.win, 3, 1L << 1, key_hook_release, &cub3d);
	mlx_hook(cub3d.win, 17, 1L << 17, end_game, &cub3d);
	mlx_loop_hook(cub3d.mlx, choose_move, &cub3d);
	mlx_loop(cub3d.mlx);
}
