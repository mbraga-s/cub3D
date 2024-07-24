/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:53:01 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/07/24 11:41:47 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

int	end_game(t_data *data);

void	store_map(char *file, t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	data->map_h = map_getheight(file);
	data->map = malloc((data->map_h + 1) * sizeof(char *));
	fd = open(file, O_RDONLY);
	if (!data->map || fd < 0)
	{
		printf("Error allocating map space...\n");
		close(fd);
		map_free(data->map);
		exit(1);
	}
	while (data->map_h > i)
	{
		data->map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	data->map[i] = NULL;
	data->map_w = ft_strlen(data->map[0]) - 1;
}

void	init_data(t_data *data, char *file)
{
	data->px = 128;
	data->py = 128;
	data->pa = PI / 2;
	data->pdx = cos(data->pa) * 5;
	data->pdy = sin(data->pa) * 5;
	data->p_color = 0xFFFFFF00;
	data->w_color = 0xFFFFFFFF;
	store_map(file, data);
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->map_w * 64, data->map_h * 64, "Tester");
	data->img = mlx_new_image(data->mlx, data->map_w * 64, data->map_h * 64);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->l_lgt, &data->endian);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == XK_a || keycode == XK_w || keycode == XK_s || \
		keycode == XK_d)
	{
		draw_3dray(data, 0x00000000);
		draw_player(data, 0x00000000);
	}
	if (keycode == XK_Escape)
		end_game(data);
	else if (keycode == XK_w)
	{
		data->px -= data->pdx;
		data->py -= data->pdy;
	}
	else if (keycode == XK_a)
	{
		data->pa -= 0.05;
		if (data->pa < 0)
			data->pa += 2 * PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	else if (keycode == XK_s)
	{
		data->px += data->pdx;
		data->py += data->pdy;
	}
	else if (keycode == XK_d)
	{
		data->pa += 0.05;
		if (data->pa > 2 * PI)
			data->pa -= 2 * PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	else
		return (0);
	draw_map(data);
	draw_player(data, data->p_color);
	draw_3dray(data, 0xFF00FF00);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	end_game(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	map_free(data->map);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		printf("Too many / few arguments.\n");
		return (0);
	}
	init_data(&data, argv[1]);
	printf("\nMap height: %d\n", data.map_h);
	printf("Map width: %d\n", data.map_w);
	draw_map(&data);
	draw_player(&data, data.p_color);
	draw_3dray(&data, 0xFF00FF00);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_hook(data.win, 17, 1, end_game, &data);
	mlx_hook(data.win, 2, 1L, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
