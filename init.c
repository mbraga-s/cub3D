/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:47:32 by manumart          #+#    #+#             */
/*   Updated: 2024/09/12 20:05:23 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	nullcub3d(t_cub3d *cub3d)
{
	cub3d->map.map = NULL;
	cub3d->map.floor.color.color = -1;
	cub3d->map.ceiling.color.color = -1;
	cub3d->map.floor.color.r = -1;
	cub3d->map.floor.color.g = -1;
	cub3d->map.floor.color.b = -1;
	cub3d->map.ceiling.color.r = -1;
	cub3d->map.ceiling.color.g = -1;
	cub3d->map.ceiling.color.b = -1;
	cub3d->map.n_texture = NULL;
	cub3d->map.s_texture = NULL;
	cub3d->map.w_texture = NULL;
	cub3d->map.e_texture = NULL;
	cub3d->plr.dirx = 0;
	cub3d->plr.diry = 0;
}
