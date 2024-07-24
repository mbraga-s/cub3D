/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:53:18 by mbraga-s          #+#    #+#             */
/*   Updated: 2024/07/17 15:27:04 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "trace.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_lgt + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	map_free(char **maparray)
{
	int	i;

	i = 0;
	while (maparray && maparray[i])
	{
		free(maparray[i]);
		i++;
	}
	free(maparray);
	exit (0);
}

int	map_getheight(char *file)
{
	int		count;
	int		fd;
	char	buffer;
	int		flag;

	count = 1;
	flag = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		printf("Error opening file.\n");
		exit(1);
	}
	while (read(fd, &buffer, 1))
	{
		flag = 0;
		if (buffer == '\n')
		{
			flag = 1;
			count++;
		}
	}
	if (flag == 1)
		count--;
	close(fd);
	return (count);
}
