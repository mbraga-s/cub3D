/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:35:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/14 18:59:00 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Calculates and assigns the distance of the ray from the player to
// the first intersection with the axis (x or y), as well as the
// distance from the camera plane
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

// Runs the dda algorithm.
// This algorithm checks which distance is smallest (going to next horiz line or
// going to the next vert line) and moves the map coord, accordingly.
// Then checks if a wall was reached. If not, continues running.
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

// Calculates all the needed variables for drawing the texture
void	calc_text(t_cub3d *cub3d, t_raydata *rd, t_img *text, int x)
{
	double	wallx;

	if (rd->side == 1)
		wallx = cub3d->plr.py + rd->perpwalldist * rd->raydiry;
	else
		wallx = cub3d->plr.px + rd->perpwalldist * rd->raydirx;
	wallx -= floor(wallx);
	rd->textx = (int)(wallx * (double)text->w);
	if (rd->side == 0 && rd->raydiry > 0)
		rd->textx = text->w - rd->textx - 1;
	if (rd->side == 1 && rd->raydirx < 0)
		rd->textx = text->w - rd->textx - 1;
	rd->step = 1.0 * text->h / rd->lineh;
	rd->textpos = (double)(rd->drawbegin - cub3d->wn_h / 2 + rd->lineh / 2)
		* rd->step;
	draw_text(cub3d, rd, text, x);
}

// Calculates the starting and ending pixels to draw the vertical strip
// Depending on the rays direction, calls calc_text with the right text.
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
			calc_text(cub3d, rd, &cub3d->map.we, x);
		else
			calc_text(cub3d, rd, &cub3d->map.ea, x);
	}
	else
	{
		if (rd->raydiry < 0)
			calc_text(cub3d, rd, &cub3d->map.no, x);
		else
			calc_text(cub3d, rd, &cub3d->map.so, x);
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
		rd.lineh = (int)(cub3d->wn_h / rd.perpwalldist);
		draw_rays(cub3d, &rd, x);
		x++;
	}
}
