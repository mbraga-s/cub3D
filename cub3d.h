/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 16:09:28 by manumart          #+#    #+#             */
/*   Updated: 2024/09/15 11:14:42 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./mlx_linux/mlx.h"
# include "libft/libft.h"
# include "mlx_linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define PI 3.14159
# define BUFFER_SIZE 42

// Structure containing all variables pertinent to raycasting:
//» mapx, mapy - position on the map array
//» raydirx, raydiry - direction vector coords of the ray
//» sidedistx, sidedisty - length of ray from current pos to next x or y-side
//» perpwalldist - distance between the camera plane and the ray hit
//» stepx, stepy - direction to move in each axis (1 or -1)
//» side - flag indicating orientation of wall hit (vert or hori)
//» lineh - height of line to draw
//» drawbegin - pos of the first pixel to draw
//» drawend - pos of the last pixel to draw
//» textx, texty - pos of the texture pixel
//» step - pos of the last pixel to draw
//» textpos - pos of the last pixel to draw
typedef struct s_raydata
{
	int				mapx;
	int				mapy;
	double			camerax;
	double			raydirx;
	double			raydiry;
	double			sidedistx;
	double			sidedisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				side;
	int				lineh;
	int				drawbegin;
	int				drawend;
	int				textx;
	int				texty;
	double			step;
	double			textpos;
}					t_raydata;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				l_lgt;
	int				endian;
	int				w;
	int				h;
}					t_img;

//  			color;       // current color (usefull while testing)
// 					mm_w3dcolor; // raycast line color (former w_color)
// 					mm_wcolor;   // minimap wall color (former w_color)
typedef struct s_color
{
	int				color;
	int				mm_w3dcolor;
}					t_color;

typedef struct s_floornceiling
{
	int				width;
	int				height;
	t_color			color;

}					t_floornceiling;

typedef struct s_map
{
	char			**map;
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	t_img			no;
	t_img			so;
	t_img			we;
	t_img			ea;
	t_floornceiling	floor;
	t_floornceiling	ceiling;
}					t_map;

typedef struct s_player
{
	double			px;
	double			py;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			mv_spd;
	double			rot_spd;
}					t_player;

//  t_strmlx 		smlx; // smlx porque há o *mlx na strmlx
//  int 			size; // tile size (usually 64x64 pixels)
//  int 			wn_w; // window width
// 	int 			wn_h; // window width
typedef struct s_cub3d
{
	t_map			map;
	t_img			scrn;
	t_player		plr;
	t_color			colors;
	void			*mlx;
	void			*win;
	int				height;
	int				width;
	int				wn_w;
	int				wn_h;
	int				ws_flag;
	int				ad_flag;
	int				lr_flag;
}					t_cub3d;

char				*get_next_line(int fd);

char				*ft_strjoin_gnl(char *str1, char *str2);

int					stashfree(char *buff);

int					separate_values(int file, t_cub3d *cub3d);

void				free_array(char **str);

void				free_str(char *str);

int					set_texture(char *line, t_map *map);

void				exit_error(char *str);

int					colors(int fd, t_cub3d *cub3d);

int					check_colors(char *line, t_cub3d *cub3d);

int					parse(char *file, t_cub3d *cub3d);

void				free_textures(t_cub3d *cub3d);

int					ft_get_map(int fd, char *line, t_cub3d *cub3d);

int					ft_parse_map(t_cub3d *cub3d);

int					ft_mapmain(int fd, char *line, t_cub3d *cub3d);

int					get_plr(t_cub3d *cub3d);

int					lookforplr(t_cub3d *cub3d, int i, int j);
int					mainfloodfill(t_cub3d *cub3d);
char				**map_copy(t_cub3d *cub3d);

int					flood_fill(t_cub3d *cub3d, int x, int y, char **temp);
char				*skip_newlinenspaces(int fd, char *line);
void				free_textures(t_cub3d *cub3d);

void				nullcub3d(t_cub3d *cub3d);
///////////////////////////////////////////////////////////////

void				init_raydata(t_cub3d *cub3d, t_raydata *rd, int x);

void				init_cub3d(t_cub3d *cub3d);

void				put_pixel(t_cub3d *cub3d, int x, int y, int color);

void				draw_text(t_cub3d *cub3d, t_raydata *rd, t_img *text,
						int x);

void				raycasting(t_cub3d *cub3d);

void				error_end_game(t_cub3d *cub3d, char *str);

int					end_game(t_cub3d *cub3d);

int					key_hook_press(int keycode, t_cub3d *cub3d);

int					key_hook_release(int keycode, t_cub3d *cub3d);

int					choose_move(t_cub3d *cub3d);

void				move_d(t_cub3d *cub3d);

void				move_a(t_cub3d *cub3d);

void				move_right(t_cub3d *cub3d);

void				move_left(t_cub3d *cub3d);

void				move_wu(t_cub3d *cub3d);

void				move_sd(t_cub3d *cub3d);

int					check_value(t_cub3d *cub3d, int foundcolor, int foundtex, \
						char *line);

int					parse_loop1(t_cub3d *cub3d, char *line, int *foundtex, \
						int *foundcolor);

int					ismap(char *str);

int					isempty(char *str);

#endif
