/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:35:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/12 18:51:14 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->l_lgt + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

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

//Calculates and assigns the distance of the ray from the player to
//the first intersection with the axis (x or y), as well as the 
//distance from the camera plane
void	calc_raylength(t_cub3d *cub3d, t_raydata *rd)
{
	if (rd->raydirx < 0)
	{
		rd->stepx = -1;
		rd->sidedistx = (cub3d->plr.px - rd->mapx) * fabs(1 / rd->raydirx);
	}
	else
	{
		rd->stepx = 1;
		rd->sidedistx = (rd->mapx + 1 - cub3d->plr.px) * fabs(1 / rd->raydirx);
	}
	if (rd->raydiry < 0)
	{
		rd->stepy = -1;
		rd->sidedisty = (cub3d->plr.py - rd->mapy) * fabs(1 / rd->raydiry);
	}
	else
	{
		rd->stepy = 1;
		rd->sidedisty = (rd->mapy + 1 - cub3d->plr.py) * fabs(1 / rd->raydiry);
	}
}

//Runs the dda algorithm.
//This algorithm checks which distance is smallest (going to next horiz line or
//going to the next vert line) and moves the map coord, accordingly.
//Then checks if a wall was reached. If not, continues running.
void	dda_algorithm(t_cub3d *cub3d, t_raydata *rd)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (rd->sidedistx < rd->sidedisty)
		{
			rd->sidedistx += fabs(1 / rd->raydirx);
			rd->mapx += rd->stepx;
			rd->side = 1;
		}
		else
		{
			rd->sidedisty += fabs(1 / rd->raydiry);
			rd->mapy += rd->stepy;
			rd->side = 0;
		}
		if (cub3d->map.map[rd->mapy][rd->mapx] == '1')
			hit = 1;
	}
}

void	calc_text(t_cub3d *cub3d, t_raydata *rd, t_img *text, int x)
{
	int		textx;
	int		texty;
	double	wallx;
	double	step;
	double	textpos;

	if (rd->side == 1)
		wallx = cub3d->plr.py + rd->perpwalldist * rd->raydiry;
	else
		wallx = cub3d->plr.px + rd->perpwalldist * rd->raydirx;
	wallx -= floor(wallx);
	textx = (int)(wallx * (double)text->width);
	if ((rd->side == 0 && rd->raydirx > 0) || (rd->side == 1 && rd->raydiry < 0))
		textx = text->width - textx - 1;
	step = (double)text->height / (double)rd->lineh;
	textpos =(double)(rd->drawbegin - cub3d->wn_h / 2 + rd->lineh / 2) * step;
	for (int y = rd->drawbegin; y < rd->drawend; y++)
	{
		texty = (int)textpos & (text->height - 1);
		textpos += step;
		cub3d->colors.mm_w3dcolor = get_texture_pixel(text, textx, texty);
		put_pixel(cub3d, x, y, cub3d->colors.mm_w3dcolor);
	}
}

void	draw_rays(t_cub3d *cub3d, t_raydata *rd, int x)
{
	rd->drawbegin = -rd->lineh / 2 + cub3d->wn_h / 2;
	if (rd->drawbegin < 0)
		rd->drawbegin = 0;
	rd->drawend = rd->lineh / 2 + cub3d->wn_h / 2;
	if (rd->drawend >= cub3d->wn_h)
		rd->drawend = cub3d->wn_h - 1;
	if (rd->side == 1)
	{
		if (rd->raydirx < 0)
		{
			calc_text(cub3d, rd, &cub3d->map.we, x);
			// cub3d->colors.mm_w3dcolor = 0xff0000ff;
			// ft_draw_vline(cub3d, x, rd->drawbegin, rd->drawend);
		}
		else
		{
			calc_text(cub3d, rd, &cub3d->map.ea, x);
			// cub3d->colors.mm_w3dcolor = 0xffff00ff;
			// ft_draw_vline(cub3d, x, rd->drawbegin, rd->drawend);
		}
	}
	else
	{
		if (rd->raydiry < 0)
		{
			// cub3d->colors.mm_w3dcolor = 0xffffff00;
			// ft_draw_vline(cub3d, x, rd->drawbegin, rd->drawend);
			calc_text(cub3d, rd, &cub3d->map.no, x);
		}
		else
		{
			// cub3d->colors.mm_w3dcolor = 0xffff0000;
			// ft_draw_vline(cub3d, x, rd->drawbegin, rd->drawend);
			calc_text(cub3d, rd, &cub3d->map.so, x);
		}
	}
}

// The raycasting algorithm. Calculates the rays and renders the 3D view.
void	raycasting(t_cub3d *cub3d)
{
	t_raydata	rd;
	int			x;

	x = 0;
	while (x < cub3d->wn_w)
	{

		init_raydata(cub3d, &rd, x);
		calc_raylength(cub3d, &rd);
		dda_algorithm(cub3d, &rd);
		if (rd.side == 1)
			rd.perpwalldist = (rd.sidedistx - fabs(1 / rd.raydirx));
		else
			rd.perpwalldist = (rd.sidedisty - fabs(1 / rd.raydiry));
		if (rd.perpwalldist != 0)
			rd.lineh = (int)(cub3d->wn_h / rd.perpwalldist);
		else
			rd.lineh = cub3d->wn_h;
		draw_rays(cub3d, &rd, x);
		x++;
	}
}
