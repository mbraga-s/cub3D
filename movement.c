/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:15:03 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/13 11:39:24 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Handles the behaviour of certain keys.
// Part 5 of 5. A and D.
int	key_hook5(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_d)
	{
		if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px + \
				cub3d->plr.planex * cub3d->plr.mv_spd)] != '1')
			cub3d->plr.px += cub3d->plr.planex * cub3d->plr.mv_spd;
		if (cub3d->map.map[(int)(cub3d->plr.py + cub3d->plr.planey * \
				cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
			cub3d->plr.py += cub3d->plr.planey * cub3d->plr.mv_spd;
		return (1);
	}
	else if (keycode == XK_a)
	{
		if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px - \
				cub3d->plr.planex * cub3d->plr.mv_spd)] != '1')
			cub3d->plr.px -= cub3d->plr.planex * cub3d->plr.mv_spd;
		if (cub3d->map.map[(int)(cub3d->plr.py - cub3d->plr.planey * \
				cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
			cub3d->plr.py -= cub3d->plr.planey * cub3d->plr.mv_spd;
		return (1);
	}
	else
		return (0);
	return (1);
}

// Handles the behaviour of certain keys.
// Part 4 of 5. Right Arrow.
int	key_hook4(int keycode, t_cub3d *cub3d)
{
	double	olddirx;
	double	oldplanex;

	if (keycode == XK_Right)
	{
		olddirx = cub3d->plr.dirx;
		oldplanex = cub3d->plr.planex;
		cub3d->plr.dirx = cub3d->plr.dirx * cos(cub3d->plr.rot_spd) - \
			cub3d->plr.diry * sin(cub3d->plr.rot_spd);
		cub3d->plr.diry = olddirx * sin(cub3d->plr.rot_spd) + \
			cub3d->plr.diry * cos(cub3d->plr.rot_spd);
		cub3d->plr.planex = cub3d->plr.planex * cos(cub3d->plr.rot_spd) - \
			cub3d->plr.planey * sin(cub3d->plr.rot_spd);
		cub3d->plr.planey = oldplanex * sin(cub3d->plr.rot_spd) + \
			cub3d->plr.planey * cos(cub3d->plr.rot_spd);
		return (1);
	}
	else if (key_hook5(keycode, cub3d))
		return (1);
	return (0);
}

// Handles the behaviour of certain keys.
// Part 3 of 5. Left Arrow.
int	key_hook3(int keycode, t_cub3d *cub3d)
{
	double	olddirx;
	double	oldplanex;

	if (keycode == XK_Left)
	{
		olddirx = cub3d->plr.dirx;
		oldplanex = cub3d->plr.planex;
		cub3d->plr.dirx = cub3d->plr.dirx * cos(-cub3d->plr.rot_spd) - \
			cub3d->plr.diry * sin(-cub3d->plr.rot_spd);
		cub3d->plr.diry = olddirx * sin(-cub3d->plr.rot_spd) + cub3d->plr.diry \
			* cos(-cub3d->plr.rot_spd);
		cub3d->plr.planex = cub3d->plr.planex * cos(-cub3d->plr.rot_spd) - \
			cub3d->plr.planey * sin(-cub3d->plr.rot_spd);
		cub3d->plr.planey = oldplanex * sin(-cub3d->plr.rot_spd) + \
			cub3d->plr.planey * cos(-cub3d->plr.rot_spd);
		return (1);
	}
	else if (key_hook4(keycode, cub3d))
		return (1);
	return (0);
}

// Handles the behaviour of certain keys.
// Part 2 of 5. W, S, Up Arrow and Down Arrow.
int	key_hook2(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_w || keycode == XK_Up)
	{
		if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px + \
				cub3d->plr.dirx * cub3d->plr.mv_spd)] != '1')
			cub3d->plr.px += cub3d->plr.dirx * cub3d->plr.mv_spd;
		if (cub3d->map.map[(int)(cub3d->plr.py + cub3d->plr.diry * \
				cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
			cub3d->plr.py += cub3d->plr.diry * cub3d->plr.mv_spd;
		return (1);
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px - \
				cub3d->plr.dirx * cub3d->plr.mv_spd)] != '1')
			cub3d->plr.px -= cub3d->plr.dirx * cub3d->plr.mv_spd;
		if (cub3d->map.map[(int)(cub3d->plr.py - cub3d->plr.diry * \
				cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
			cub3d->plr.py -= cub3d->plr.diry * cub3d->plr.mv_spd;
		return (1);
	}
	else if (key_hook3(keycode, cub3d))
		return (1);
	return (0);
}

// Handles the behaviour of certain keys.
// Part 1 of 5. Esc. Calls the rendering functions.
int	key_hook(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
		end_game(cub3d);
	else if (key_hook2(keycode, cub3d))
	{
		raycasting(cub3d);
		// draw_map(cub3d);
		mlx_put_image_to_window(cub3d->mlx, cub3d->win, \
			(cub3d->scrn).img, 0, 0);
	}
	return (0);
}
