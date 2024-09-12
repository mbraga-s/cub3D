/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:15:03 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/12 10:27:15 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_collision(t_cub3d *cub3d, float angle)
{
	float	xpos;
	float	ypos;
	int		x;
	int		y;

	xpos = cub3d->plr.px - (cos(angle) * 30);
	ypos = cub3d->plr.py - (sin(angle) * 30);
	x = abs((int)xpos / cub3d->size);
	y = abs((int)ypos / cub3d->size);
	if (cub3d->map.map[y] && cub3d->map.map[y][x] == '1')
		return (1);
	return (0);
}

// Handles the behaviour of certain keys.
// Part 4 of 4. D.
/* int	key_hook4(int keycode, t_cub3d *cub3d)
{
	float	tempa;
	float	tempx;
	float	tempy;

	if (keycode == XK_d)
	{
		tempa = cub3d->plr.pa + (PI / 2);
		limit_angle(&tempa);
		if (check_collision(cub3d, tempa))
			return (1);
		tempx = cos(tempa) * 5;
		tempy = sin(tempa) * 5;
		cub3d->plr.px -= tempx;
		cub3d->plr.py -= tempy;
	}
	else
		return (0);
	return (1);
} */

// Handles the behaviour of certain keys.
// Part 3 of 4. Right Arrow and A.
int	key_hook3(int keycode, t_cub3d *cub3d)
{
	double oldDirX;
	double oldPlaneX;

	if (keycode == XK_Left)
	{
		oldDirX = cub3d->plr.dirx;
		oldPlaneX = cub3d->plr.planex;
		cub3d->plr.dirx = cub3d->plr.dirx * cos(-cub3d->plr.rot_spd) - cub3d->plr.diry * sin(-cub3d->plr.rot_spd);
		cub3d->plr.diry = oldDirX * sin(-cub3d->plr.rot_spd) + cub3d->plr.diry * cos(-cub3d->plr.rot_spd);
		cub3d->plr.planex = cub3d->plr.planex * cos(-cub3d->plr.rot_spd) - cub3d->plr.planey * sin(-cub3d->plr.rot_spd);
		cub3d->plr.planey = oldPlaneX * sin(-cub3d->plr.rot_spd) + cub3d->plr.planey * cos(-cub3d->plr.rot_spd);
		return (1);
	}
	else
		return (1);
	return (0);
}

// Handles the behaviour of certain keys.
// Part 2 of 4. W, S, Left Arrow, Up Arrow and Down Arrow.
int	key_hook2(int keycode, t_cub3d *cub3d)
{
	double oldDirX;
	double oldPlaneX;

	if (keycode == XK_w || keycode == XK_Up)
	{
		if (cub3d->map.map[(int)(cub3d->plr.py)]\
			[(int)(cub3d->plr.px + cub3d->plr.dirx * cub3d->plr.mv_spd)] != '1')
			cub3d->plr.px += cub3d->plr.dirx * cub3d->plr.mv_spd;
		if (cub3d->map.map[(int)(cub3d->plr.py + cub3d->plr.diry * cub3d->plr.mv_spd)]\
			[(int)(cub3d->plr.px)] != '1')
			cub3d->plr.py += cub3d->plr.diry * cub3d->plr.mv_spd;
		return (1);
	}
	else if (keycode == XK_Right)
	{
		oldDirX = cub3d->plr.dirx;
		oldPlaneX = cub3d->plr.planex;
		cub3d->plr.dirx = cub3d->plr.dirx * cos(cub3d->plr.rot_spd) - cub3d->plr.diry * sin(cub3d->plr.rot_spd);
		cub3d->plr.diry = oldDirX * sin(cub3d->plr.rot_spd) + cub3d->plr.diry * cos(cub3d->plr.rot_spd);
		cub3d->plr.planex = cub3d->plr.planex * cos(cub3d->plr.rot_spd) - cub3d->plr.planey * sin(cub3d->plr.rot_spd);
		cub3d->plr.planey = oldPlaneX * sin(cub3d->plr.rot_spd) + cub3d->plr.planey * cos(cub3d->plr.rot_spd);
		return (1);
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		cub3d->plr.px -= cub3d->plr.dirx * cub3d->plr.mv_spd;
		cub3d->plr.py -= cub3d->plr.diry * cub3d->plr.mv_spd;
		return (1);
	}
	else if (key_hook3(keycode, cub3d))
		return (1);
	return (0);
}

// Handles the behaviour of certain keys.
// Part 1 of 4. Esc. Calls the rendering functions.
int	key_hook(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
		end_game(cub3d);
	else if (key_hook2(keycode, cub3d))
	{
		draw_area(cub3d, 0, 0, cub3d->wn_w, cub3d->wn_h);
		raycasting(cub3d);
		draw_map(cub3d);
		mlx_put_image_to_window(cub3d->mlx, cub3d->win,	(cub3d->scrn).img, 0, 0);
	}
	return (0);
}
