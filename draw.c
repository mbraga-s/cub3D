/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:23:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/12 22:29:27 by mbraga-s         ###   ########.fr       */
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

//Retrieves the color corresponding to the given coords on the texture.
//Corrects for mlx ajustments.
int	get_color(t_img *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->l_lgt + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

//Draws a scalable minimap on the corner of the map.
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
			{
				color = 0x000f0f0f;
				draw_square(cub3d, (f * scale) + (scale / 2 + 1), (i \
						* scale) + (scale / 2 + 1), color, scale);
			}
			else if (cub3d->map.map[i][f] != ' ' && cub3d->map.map[i][f])
			{
				color = 0xff44f044;
				draw_square(cub3d, (f * scale) + (scale / 2 + 1), (i \
						* scale) + (scale / 2 + 1), color, scale);
			}
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
