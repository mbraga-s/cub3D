/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:35:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/12 12:15:47 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->l_lgt + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
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

// The raycasting algorithm. Calculates the rays and renders the 3D view.
void	raycasting(t_cub3d *cub3d)
{
	t_raydata	rd;
	int			x;

	x = 0;
	while (x < cub3d->wn_w)
	{
		rd.camerax = 2 * x / (double)cub3d->wn_w - 1;
		rd.raydirx = cub3d->plr.dirx + cub3d->plr.planex * rd.camerax;
		rd.raydiry = cub3d->plr.diry + cub3d->plr.planey * rd.camerax;

		rd.mapx = (int)(cub3d->plr.px);
		rd.mapy = (int)(cub3d->plr.py);

		rd.sidedistx = 0;
		rd.sidedisty = 0;

		//length of ray from one x or y-rd.side to next x or y-rd.side
		double deltaDistX = 0;
		double deltaDistY = 0;
		rd.perpwalldist = 0;
		deltaDistX = fabs(1 / rd.raydirx);
		deltaDistY = fabs(1 / rd.raydiry);
		if (rd.raydirx < 0)
		{
			rd.stepx = -1;
			rd.sidedistx = (cub3d->plr.px - rd.mapx) * fabs(1 / rd.raydirx);
		}
		else
		{
			rd.stepx = 1;
			rd.sidedistx = (rd.mapx + 1 - cub3d->plr.px) * fabs(1 / rd.raydirx);
		}
		if (rd.raydiry < 0)
		{
			rd.stepy = -1;
			rd.sidedisty = (cub3d->plr.py - rd.mapy) * fabs(1 / rd.raydiry);
		}
		else
		{
			rd.stepy = 1;
			rd.sidedisty = (rd.mapy + 1 - cub3d->plr.py) * fabs(1 / rd.raydiry);
		}
		//perform DDA
		dda_algorithm(cub3d, &rd);
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(rd.side == 1)
			rd.perpwalldist = (rd.sidedistx - deltaDistX);
		else
			rd.perpwalldist = (rd.sidedisty - deltaDistY);
		//Calculate height of line to draw on screen
		if (rd.perpwalldist != 0)
			rd.lineh = (int)(cub3d->wn_h / rd.perpwalldist);
		else
			rd.lineh = cub3d->wn_h;
		//calculate lowest and highest pixel to fill in current stripe
		rd.drawbegin = -rd.lineh / 2 + cub3d->wn_h / 2;
		if(rd.drawbegin < 0)
			rd.drawbegin = 0;
	  	rd.drawend = rd.lineh / 2 + cub3d->wn_h / 2;
	  	if(rd.drawend >= cub3d->wn_h)
			rd.drawend = cub3d->wn_h - 1;
		double wallx = 0;
		int	textx = 0;
		int	texty = 0;
		double step = 0;
		double textpos = 0;
		if (rd.side == 1 && rd.raydirx < 0)
		{
			wallx = cub3d->plr.py + rd.perpwalldist * rd.raydiry;
			wallx -= floor(wallx);
			textx = (int)(wallx * (double)cub3d->map.we.width);
			textx = cub3d->map.we.width - textx - 1;
			step = (double)cub3d->map.we.height / (double)rd.lineh;
			textpos =(double)(rd.drawbegin - cub3d->height / 2 + rd.lineh / 2) * step;
			for (int y = rd.drawbegin; y < rd.drawend; y++)
			{
				texty = (int)textpos & (cub3d->map.we.height - 1);
				textpos += step;
				cub3d->colors.mm_w3dcolor = get_texture_pixel(&cub3d->map.we, textx, texty);
				put_pixel(cub3d, x, y, cub3d->colors.mm_w3dcolor);
			}
			// cub3d->colors.mm_w3dcolor = 0xFF0000FF; //blue west
		}
		else if (rd.side == 1 && rd.raydirx > 0)
		{
			cub3d->colors.mm_w3dcolor = 0xFFFFFFFF; //wrd.hite east
			ft_draw_vline(cub3d, x, rd.drawbegin, rd.drawend);
		}
		else if (rd.side == 0 && rd.raydiry > 0)
		{
			cub3d->colors.mm_w3dcolor = 0xFFf0FF0f; //yellow south
			ft_draw_vline(cub3d, x, rd.drawbegin, rd.drawend);
		}
		else if (rd.side == 0 && rd.raydiry < 0)
		{
			cub3d->colors.mm_w3dcolor = 0xFFFF0000; //RED north
			ft_draw_vline(cub3d, x, rd.drawbegin, rd.drawend);
		}
		x++;
	}
}
