/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 17:25:39 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/09 19:55:39 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Keeps the given angle between 0 and 2PI.
void	limit_angle(float *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	else if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

// Frees the map array. Probably a duplicate function, will delete later.
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
	mlx_destroy_image(cub3d->smlx.mlx, cub3d->smlx.img);
	mlx_destroy_window(cub3d->smlx.mlx, cub3d->smlx.win);
	mlx_destroy_display(cub3d->smlx.mlx);
	free(cub3d->smlx.mlx);
	free_array(cub3d->map.map);
	free_textures(cub3d);
	exit(0);
}

// Draws an area starting at (x1, y1) to (x2, y2) of color set in cub3D struct.
int	draw_area(t_cub3d *cub3d, int x1, int y1, int x2, int y2)
{
	int	xinc;
	int	yinc;

	yinc = y1;
	while (yinc < (y2 / 2))
	{
		xinc = x1;
		while (xinc < x2)
		{
			put_pixel(cub3d, x1 + xinc, y1 + yinc, 0xFF00FFFF);
			xinc++;
		}
		yinc++;
	}
	while (yinc < y2)
	{
		xinc = x1;
		while (xinc < x2)
		{
			put_pixel(cub3d, x1 + xinc, y1 + yinc, 0xFF00FF00);
			xinc++;
		}
		yinc++;
	}
	return (0);
}

// void	depth_field(t_cub3d *cub3d, t_raydata *rd, int flag)
// {
// 	while (rd->dof < (cub3d->width - 2))
// 	{
// 		rd->mx = abs((int)rd->rx / cub3d->size);
// 		rd->my = abs((int)rd->ry / cub3d->size);
// 		rd->mp = rd->my * cub3d->width + rd->mx;
// 		if (rd->mp < cub3d->width * cub3d->height
// 			&& cub3d->map.map[rd->my][rd->mx] == '1')
// 			rd->dof = (cub3d->width - 2);
// 		else
// 		{
// 			rd->rx += rd->xo;
// 			rd->ry += rd->yo;
// 			rd->dof += 1;
// 		}
// 	}
// 	if (flag == 1) // means horizontal
// 	{
// 		rd->hx = rd->rx;
// 		rd->hy = rd->ry;
// 	}
// 	else
// 	{
// 		rd->vx = rd->rx;
// 		rd->vy = rd->ry;
// 	}
// }
