/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:35:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/08/23 18:36:11 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

void	check_longer(t_data *data, int color, t_raydata *rd)
{
	float	total_h;
	float	total_v;

	total_h = fabs(rd->hx - data->px) + fabs(rd->hy - data->py);
	total_v = fabs(rd->vx - data->px) + fabs(rd->vy - data->py);
	// printf("Tot H: %f\n", total_h);
	// printf("Tot V: %f\n\n", total_v);
	if ((total_h > total_v && fabs(total_v) > 0.0001) || fabs(total_h) < 0.0001)
	{
		ft_draw_line(data, data->px, data->py, rd->vx, rd->vy, color);
		data->w3d_color = 0xFFFF0000;
		rd->dist = total_v;
	}
	else
	{
		ft_draw_line(data, data->px, data->py, rd->hx, rd->hy, color);
		data->w3d_color = 0xFF0000FF;
		rd->dist = total_h;
	}
}

void	depth_field(t_data *data, int color, t_raydata *rd, int flag)
{
	while (rd->dof < 8)
	{
		rd->mx = abs((int)rd->rx / 64);
		rd->my = abs((int)rd->ry / 64);
		rd->mp = rd->my * data->map_w + rd->mx;
		if (rd->mp < data->map_w * data->map_h && data->map[rd->my][rd->mx] == 'X')
			rd->dof = 8;
		else
		{
			rd->rx += rd->xo;
			rd->ry += rd->yo;
			rd->dof += 1;
		}
	}
	if (flag == 1) //means horizontal
	{
		rd->hx = rd->rx;
		rd->hy = rd->ry;
	}
	else
	{
		rd->vx = rd->rx;
		rd->vy = rd->ry;
	}
}

// Check horizontal lines
void	check_hor(t_data *data, int color, t_raydata *rd)
{
	float		atan;

	atan = -1 / tan(rd->ra);
	if (rd->ra < PI) //looking up
	{
		rd->ry = (((int)data->py >> 6) << 6) - 0.0001;
		rd->rx = (data->py - rd->ry) * atan + data->px;
		rd->yo = -64;
		rd->xo = -rd->yo * atan;
	}
	if (rd->ra > PI) //looking down 
	{
		rd->ry = (((int)data->py >> 6) << 6) + 64;
		rd->rx = (data->py - rd->ry) * atan + data->px;
		rd->yo = 64;
		rd->xo = -rd->yo * atan;
	}
	if (fabs(rd->ra) < 0.0001 || fabs(rd->ra - PI) < 0.0001)
	{
		rd->rx = data->px;
		rd->ry = data->py;
		rd->dof = 8;
	}
	depth_field(data, 0xFF00FF00, rd, 1);
}

// Check vertical lines
void	check_ver(t_data *data, int color, t_raydata *rd)
{
	float		ntan;

	ntan = -tan(rd->ra);
	if (rd->ra < P2 || rd->ra > P3) //looking right
	{
		rd->rx = (((int)data->px >> 6) << 6) - 0.0001;
		rd->ry = (data->px - rd->rx) * ntan + data->py;
		rd->xo = -64;
		rd->yo = -rd->xo * ntan;
	}
	if (rd->ra > P2 && rd->ra < P3) //looking left
	{
		rd->rx = (((int)data->px >> 6) << 6) + 64;
		rd->ry = (data->px - rd->rx) * ntan + data->py;
		rd->xo = 64;
		rd->yo = -rd->xo * ntan;
	}
	if (fabs(rd->ra - P2) < 0.0001 || fabs(rd->ra - P3) < 0.0001)
	{
		rd->rx = data->px;
		rd->ry = data->py;
		rd->dof = 8;
	}
	depth_field(data, 0xFFFF0000, rd, 0);
}

void	draw_3dray(t_data *data, int color)
{
	t_raydata	rd;
	float		incr;
	float		line_h;
	float		line_off;
	int			width;
	float		ca; //fixing fish eye
	int			i;

	width = 3;
	incr = 0.0174533; //one degree in radians
	rd.r = 0;
	rd.ra = data->pa - (incr * 5);
	if (rd.ra < 0)
		rd.ra += 2 * PI;
	if (rd.ra > 2 * PI)
		rd.ra -= 2 * PI;
	printf("NEW\n\n");
	while (rd.r < 10)
	{
		i = width;
		rd.dof = 0;
		check_hor(data, color, &rd);
		rd.dof = 0;
		check_ver(data, color, &rd);
		check_longer(data, color, &rd);
		ca = data->pa - rd.ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		printf("cos: %f\n", cos(ca));
		printf("rd: %f\n\n", rd.dist);
		rd.dist = (rd.dist * cos(ca));
		line_h = ((64 * 512) / rd.dist);
		if (line_h > (512))
			line_h = 512;
		line_off = 256 - (line_h / 2);
		while (i >= 0)
		{
			ft_draw_line(data, rd.r * 4 + (64 * data->map_w) + i, line_off, rd.r * 4 + (64 * data->map_w) + i, line_h + line_off, data->w3d_color);
			i--;
		}
		rd.ra += incr;
		if (rd.ra < 0)
			rd.ra += 2 * PI;
		if (rd.ra > 2 * PI)
			rd.ra -= 2 * PI;
		rd.r++;
	}
}
