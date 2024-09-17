/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 23:13:39 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/14 18:58:36 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Handles the behaviour of the s and down arrow keys.
void	move_sd(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px
			- cub3d->plr.dirx * cub3d->plr.mv_spd)] != '1')
		cub3d->plr.px -= cub3d->plr.dirx * cub3d->plr.mv_spd;
	if (cub3d->map.map[(int)(cub3d->plr.py - cub3d->plr.diry
			* cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
		cub3d->plr.py -= cub3d->plr.diry * cub3d->plr.mv_spd;
}

// Handles the behaviour of the d key.
void	move_d(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px
			+ cub3d->plr.planex * cub3d->plr.mv_spd)] != '1')
		cub3d->plr.px += cub3d->plr.planex * cub3d->plr.mv_spd;
	if (cub3d->map.map[(int)(cub3d->plr.py + cub3d->plr.planey
			* cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
		cub3d->plr.py += cub3d->plr.planey * cub3d->plr.mv_spd;
}

// Handles the behaviour of the a key.
void	move_a(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px
			- cub3d->plr.planex * cub3d->plr.mv_spd)] != '1')
		cub3d->plr.px -= cub3d->plr.planex * cub3d->plr.mv_spd;
	if (cub3d->map.map[(int)(cub3d->plr.py - cub3d->plr.planey
			* cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
		cub3d->plr.py -= cub3d->plr.planey * cub3d->plr.mv_spd;
}

// Handles the behaviour of the right arrow key.
void	move_right(t_cub3d *cub3d)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub3d->plr.dirx;
	oldplanex = cub3d->plr.planex;
	cub3d->plr.dirx = cub3d->plr.dirx * cos(cub3d->plr.rot_spd)
		- cub3d->plr.diry * sin(cub3d->plr.rot_spd);
	cub3d->plr.diry = olddirx * sin(cub3d->plr.rot_spd) + cub3d->plr.diry
		* cos(cub3d->plr.rot_spd);
	cub3d->plr.planex = cub3d->plr.planex * cos(cub3d->plr.rot_spd)
		- cub3d->plr.planey * sin(cub3d->plr.rot_spd);
	cub3d->plr.planey = oldplanex * sin(cub3d->plr.rot_spd) + cub3d->plr.planey
		* cos(cub3d->plr.rot_spd);
}

// Handles the behaviour of the left arrow key.
void	move_left(t_cub3d *cub3d)
{
	double	olddirx;
	double	oldplanex;

	olddirx = cub3d->plr.dirx;
	oldplanex = cub3d->plr.planex;
	cub3d->plr.dirx = cub3d->plr.dirx * cos(-cub3d->plr.rot_spd)
		- cub3d->plr.diry * sin(-cub3d->plr.rot_spd);
	cub3d->plr.diry = olddirx * sin(-cub3d->plr.rot_spd) + cub3d->plr.diry
		* cos(-cub3d->plr.rot_spd);
	cub3d->plr.planex = cub3d->plr.planex * cos(-cub3d->plr.rot_spd)
		- cub3d->plr.planey * sin(-cub3d->plr.rot_spd);
	cub3d->plr.planey = oldplanex * sin(-cub3d->plr.rot_spd) + cub3d->plr.planey
		* cos(-cub3d->plr.rot_spd);
}
