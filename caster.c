/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:35:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/10 23:08:43 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// The raycasting algorithm. Calculates the rays and renders the 3D view.
void	raycasting(t_cub3d *cub3d)
{
	int	mapx = 0;
	int	mapy = 0;

	for(int x = 0; x < cub3d->wn_w; x++)
	{
		double	camerax = 2 * x / (double)cub3d->wn_w - 1;
		double	raydirx = cub3d->dirx + cub3d->planex * camerax;
		double	raydiry = cub3d->diry + cub3d->planey * camerax;

		//which box of the map we're in
		int mapX = (int)(cub3d->player.px);
		int mapY = (int)(cub3d->player.py);

		//length of ray from current position to next x or y-side
		double sideDistX = 0;
		double sideDistY = 0;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = 0;
		double deltaDistY = 0;
		double perpWallDist = 0;
		deltaDistX = fabs(1 / raydirx);
		deltaDistY = fabs(1 / raydiry);
		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		
		if (raydirx < 0)
		{
			stepX = -1;
			sideDistX = (cub3d->player.px - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cub3d->player.px) * deltaDistX;
		}
		if (raydiry < 0)
		{
			stepY = -1;
			sideDistY = (cub3d->player.py - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cub3d->player.py) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 1;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 0;
			}
			//Check if ray has hit a wall
			if (cub3d->map.map[mapY][mapX] == '1') 
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(side == 1)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);
		//Calculate height of line to draw on screen
		int lineHeight;
		if (perpWallDist != 0)
			lineHeight = (int)(cub3d->wn_h / perpWallDist);
		else
			lineHeight = cub3d->wn_h;
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + cub3d->wn_h / 2;
		if(drawStart < 0)
			drawStart = 0;
	  	int drawEnd = lineHeight / 2 + cub3d->wn_h / 2;
	  	if(drawEnd >= cub3d->wn_h)
			drawEnd = cub3d->wn_h - 1;
		if (side == 0 && raydiry < 0)
			cub3d->colors.mm_w3dcolor = 0xFFFF0000; //RED west
		else if (side == 0 && raydiry > 0)
			cub3d->colors.mm_w3dcolor = 0xFFf0FF0f; //yellow east
		else if (side == 1 && raydirx < 0)
			cub3d->colors.mm_w3dcolor = 0xFF0000FF; //blue north
		else if (side == 1 && raydirx > 0)
			cub3d->colors.mm_w3dcolor = 0xFFFFFFFF; //white south
		//draw the pixels of the stripe as a vertical line
		ft_draw_vline(cub3d, x, drawStart, drawEnd);
	}
}
