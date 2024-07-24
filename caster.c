/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:35:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/07/24 12:03:09 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

void	draw_3dray(t_data *data, int color)
{
	int	r;
	int	mx;
	int	my;
	int	mp;
	int	dof; //depth of field
	float rx; //ray intersect with grid x coord
	float ry; //ray intersect with grid y coord
	float ra; //ray angle
	float xo; // x offset
	float yo; //y offset

	ra = data->pa;
	for (r = 0; r < 1; r++)
	{
		// Check horizontal lines
		dof = 0;
		float aTan = -1/tan(ra);
		if(ra < PI) //looking up
		{
			ry = (((int)data->py>>6)<<6)-0.0001;
			rx = (data->py - ry) * aTan + data->px;
			yo = -64;
			xo = -yo * aTan;
		}
		if(ra > PI) //looking down 
		{
			ry = (((int)data->py>>6)<<6) + 64;
			rx = (data->py - ry) * aTan + data->px;
			yo = 64;
			xo = -yo * aTan;
		}
		if(ra == 0 || ra == PI)
		{
			rx = data->px;
			ry = data->py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = abs((int)rx / 64);
			my = abs((int)ry / 64);
			mp = my * data->map_w + mx;
			if (mp < data->map_w * data->map_h && data->map[my][mx] == 'X')
				dof = 8;
			else
			{
				rx += xo;
				ry += yo;
				dof +=1;
			}
		}
		ft_draw_line(data, data->px, data->py, rx, ry, color);
	}
}
