/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:38:09 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/07/17 16:08:44 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRACE_H
# define TRACE_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <X11/keysym.h>
// # include <X11/X.h>
# include "./minilibx-linux/mlx.h"
# include "./getnextline/get_next_line.h"

# ifndef SQR_SIZE
#  define SQR_SIZE 64
# endif

# ifndef PI
#  define PI 3.14159
# endif

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	void	*img;
	char	*addr;
	int		p_color;	//player color
	int		w_color;	//wall color
	int		bpp;		//bits per pixel
	int		l_lgt;		//line length
	int		endian;
	int		map_h;
	int		map_w;
	float	px;			//player x coord
	float	py;			//player y coord
	float	pdx;		//player delta x
	float	pdy;		//player delta y
	float	pa;			//player angle
}				t_data;

char	*ft_strdup(const char *s);

int		map_free(char **maparray);

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

int		map_getheight(char *file);

void	draw_map(t_data *data);

int		draw_player(t_data *data, int color);

void	ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color);

int		draw_square(t_data *data, int x, int y, int color, int size);

void	draw_3dray(t_data *data, int color);

#endif