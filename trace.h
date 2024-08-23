/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:38:09 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/08/23 18:15:52 by mbraga-s         ###   ########.fr       */
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
#  define P2 PI/2
#  define P3 3*PI/2
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
	int		w3d_color;	//wall 3d color
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

typedef struct s_raydata
{
	int		r;	//number of rays
	int		mx;
	int		my;
	int		mp;
	int		dof; //depth of field
	float	rx; //ray intersect with grid x coord
	float	ry; //ray intersect with grid y coord
	float	ra; //ray angle
	float	xo; //x offset
	float	yo; //y offset
	float	vx; //ray intersect with grid x coord on vertical check
	float	vy; //ray intersect with grid y coord on vertical check
	float	hx; //ray intersect with grid x coord on horizontal check
	float	hy; //ray intersect with grid y coord on horizontal check
	float	dist; //final ray distance
}				t_raydata;

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