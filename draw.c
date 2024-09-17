/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:23:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/14 18:58:55 by manumart         ###   ########.fr       */
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

// Retrieves the color corresponding to the given coords on the texture.
// Corrects for mlx ajustments.
int	get_color(t_img *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->l_lgt + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

// Draws the given texture as well as the ceiling and floor for the X strip
void	draw_text(t_cub3d *cub3d, t_raydata *rd, t_img *text, int x)
{
	int	y;

	y = 0;
	while (y < rd->drawbegin)
	{
		put_pixel(cub3d, x, y, cub3d->map.ceiling.color.color);
		y++;
	}
	while (y <= rd->drawend)
	{
		rd->texty = (int)rd->textpos & (text->h - 1);
		rd->textpos += rd->step;
		cub3d->colors.mm_w3dcolor = get_color(text, rd->textx, rd->texty);
		put_pixel(cub3d, x, y, cub3d->colors.mm_w3dcolor);
		y++;
	}
	while (y < cub3d->wn_h)
	{
		put_pixel(cub3d, x, y, cub3d->map.floor.color.color);
		y++;
	}
}
