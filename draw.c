/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 18:23:49 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/08/21 12:04:59 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

void	draw_pixel(t_data *data, int x, int y, int color)
{
	if (x <= 0 || y <= 0)
		return ;
	else if (x >= (data->map_w * 64) || y >= (data->map_h * 64))
		return ;
	else
		my_mlx_pixel_put(data, x, y, color);
}

void	draw_map(t_data *data)
{
	int	i;
	int	f;
	int	color;

	i = 0;
	while (i < (data->map_h))
	{
		f = 0;
		while (f < (data->map_w))
		{
			if (data->map[i][f] == 'X')
				color = data->w_color;
			else
				color = 0XFF545454;
			draw_square(data, (f * SQR_SIZE) + 31, (i * SQR_SIZE) + 31, color, SQR_SIZE);
			f++;
		}
		i++;
	}
}

void	ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
{
	double	pixels;
	double	x;
	double	y;
	double	delta_x;
	double	delta_y;
	int		i;

	i = 0;
	delta_x = x2 - x1;
	delta_y = y2 - y1;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x = delta_x / pixels;
	delta_y = delta_y / pixels;
	x = x1;
	y = y1;
	while (i < pixels)
	{
		draw_pixel(data, x, y, color);
		x += delta_x;
		y += delta_y;
		i++;
	}
}

int	draw_player(t_data *data, int color)
{
	int	dx;
	int	dy;

	dx = (data->px - cos(data->pa) * 20) - data->px;
	dy = (data->py - sin(data->pa) * 20) - data->py;
	draw_pixel(data, data->px, data->py, color);
	draw_square(data, data->px, data->py, color, 13);
	ft_draw_line(data, data->px, data->py, data->px - cos(data->pa) * 20, \
		data->py - sin(data->pa) * 20, color);
	if (abs(dx) < abs(dy))
	{
		ft_draw_line(data, data->px + 1, data->py, data->px + 1 - cos(data->pa) * 20, data->py - sin(data->pa) * 20, color);
		ft_draw_line(data, data->px - 1, data->py, data->px - 1 - cos(data->pa) * 20, data->py - sin(data->pa) * 20, color);
	}
	else
	{
		ft_draw_line(data, data->px, data->py + 1, data->px - cos(data->pa) * 20, data->py + 1 - sin(data->pa) * 20, color);
		ft_draw_line(data, data->px, data->py - 1, data->px - cos(data->pa) * 20, data->py - 1 - sin(data->pa) * 20, color);
	}
	return (0);
}

int	draw_square(t_data *data, int x, int y, int color, int size)
{
	int	xinc;
	int	yinc;
	int	xstart;
	int	ystart;

	yinc = 0;
	xstart = x - (size / 2);
	ystart = y - (size / 2);
	if ((size % 2) == 0)
	{
		xstart--;
		ystart--;
	}
	while (yinc < size)
	{
		xinc = 0;
		while (xinc < size)
		{
			if (xinc == 0 || xinc + 1 == size || yinc == 0 || yinc + 1 == size)
				draw_pixel(data, xstart + xinc, ystart + yinc, 0x000000);
			else
				draw_pixel(data, xstart + xinc, ystart + yinc, color);
			xinc++;
		}
		yinc++;
	}
	return (0);
}
