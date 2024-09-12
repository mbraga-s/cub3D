/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:23:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/11 16:23:28 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculates the memory offset using the line length set by mlx
// and places a colored pixel at the given coords
void	put_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || y <= 0 || x >= (cub3d->wn_w) || y >= cub3d->wn_h)
		return ;
	dst = cub3d->scrn.addr + (y * cub3d->scrn.l_lgt + x * (cub3d->scrn.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_map(t_cub3d *cub3d)
{
	int	i;
	int	f;
	int	color;
	int	scale;

	i = 0;
	if ((cub3d->wn_w / cub3d->width) < (cub3d->wn_h / cub3d->height))
		scale = cub3d->wn_w / cub3d->width / 4;
	else
		scale = cub3d->wn_h / cub3d->height / 4;
	while (i < (cub3d->height))
	{
		f = 0;
		while (f < (cub3d->width))
		{
			if (cub3d->map.map[i][f] == '1')
				color = 0x000f0f0f;
			else
				color = 0xff44f044;
			draw_square(cub3d, (f * scale) + (scale / 2 + 1), (i
					* scale) + (scale / 2 + 1), color, scale);
			f++;
		}
		i++;
	}
	draw_square(cub3d, cub3d->plr.px * scale, cub3d->plr.py * scale, 0xFFFFFF00, scale - 2);
}

// Draws a line between the two given points (x1, y1) and (x2, y2).
void	ft_draw_vline(t_cub3d *cub3d, int x, int y1, int y2)
{
	int	lesser;
	int	greater;

	if (y1 < y2)
	{
		lesser = y1;
		greater = y2;
	}
	else
	{
		lesser = y2;
		greater = y1;
	}
	while (lesser <= greater)
	{
		put_pixel(cub3d, x, lesser, cub3d->colors.mm_w3dcolor);
		lesser++;
	}
}

// Draws a square with a little line indicating it's "direction" (in 2D)
int	draw_plr(t_cub3d *cub3d, int color, int scale)
{
	int	dx;
	int	dy;
	int	l_length;
	int	l_thick;

	l_length = ((scale * 30) / cub3d->size);
	l_thick = scale * 2 / cub3d->size;
	dx = (cub3d->plr.px - cos(cub3d->plr.pa) * l_length)
		- cub3d->plr.px;
	dy = (cub3d->plr.py - sin(cub3d->plr.pa) * l_length)
		- cub3d->plr.py;
	draw_square(cub3d, cub3d->plr.px, cub3d->plr.py, color, scale);
}

int	draw_square(t_cub3d *cub3d, int x, int y, int color, int size)
{
	int	xinc;
	int	yinc;
	int	xstart;
	int	ystart;

	yinc = 0;
	xstart = x - (size / 2);
	ystart = y - (size / 2);
	if ((size % 2) == 0)
	{
		xstart--;
		ystart--;
	}
	while (yinc < size)
	{
		xinc = 0;
		while (xinc < size)
		{
			put_pixel(cub3d, xstart + xinc, ystart + yinc, color);
			xinc++;
		}
		yinc++;
	}
	return (0);
}
