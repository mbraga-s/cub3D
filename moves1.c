/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 23:15:03 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/09/14 13:31:10 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Handles the behaviour of the w and up arrow keys.
void	move_wu(t_cub3d *cub3d)
{
	if (cub3d->map.map[(int)(cub3d->plr.py)][(int)(cub3d->plr.px + \
			cub3d->plr.dirx * cub3d->plr.mv_spd)] != '1')
		cub3d->plr.px += cub3d->plr.dirx * cub3d->plr.mv_spd;
	if (cub3d->map.map[(int)(cub3d->plr.py + cub3d->plr.diry * \
			cub3d->plr.mv_spd)][(int)(cub3d->plr.px)] != '1')
		cub3d->plr.py += cub3d->plr.diry * cub3d->plr.mv_spd;
}

// Runs the raycaster.
int	redraw_screen(t_cub3d *cub3d)
{
	raycasting(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, \
		(cub3d->scrn).img, 0, 0);
	return (0);
}

// Updates the player move depending on the flag values.
int	choose_move(t_cub3d *cub3d)
{
	if (cub3d->ws_flag == 1)
		move_wu(cub3d);
	if (cub3d->ws_flag == 2)
		move_sd(cub3d);
	if (cub3d->ad_flag == 1)
		move_a(cub3d);
	if (cub3d->ad_flag == 2)
		move_d(cub3d);
	if (cub3d->lr_flag == 1)
		move_left(cub3d);
	if (cub3d->lr_flag == 2)
		move_right(cub3d);
	if (cub3d->ws_flag || cub3d->ad_flag || cub3d->lr_flag)
		redraw_screen(cub3d);
	return (0);
}

// Updates the flag values depending on the keys pressed.
int	key_hook_press(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_Escape)
		end_game(cub3d);
	else if (keycode == XK_w || keycode == XK_Up)
		cub3d->ws_flag = 1;
	else if (keycode == XK_s || keycode == XK_Down)
		cub3d->ws_flag = 2;
	else if (keycode == XK_a)
		cub3d->ad_flag = 1;
	else if (keycode == XK_d)
		cub3d->ad_flag = 2;
	else if (keycode == XK_Left)
		cub3d->lr_flag = 1;
	else if (keycode == XK_Right)
		cub3d->lr_flag = 2;
	return (0);
}

// Updates the flag values depending on the keys pressed.
int	key_hook_release(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_w || keycode == XK_Up)
		cub3d->ws_flag = 0;
	else if (keycode == XK_s || keycode == XK_Down)
		cub3d->ws_flag = 0;
	else if (keycode == XK_a)
		cub3d->ad_flag = 0;
	else if (keycode == XK_d)
		cub3d->ad_flag = 0;
	else if (keycode == XK_Left)
		cub3d->lr_flag = 0;
	else if (keycode == XK_Right)
		cub3d->lr_flag = 0;
	return (0);
}
