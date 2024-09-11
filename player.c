/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:48:37 by manumart          #+#    #+#             */
/*   Updated: 2024/09/05 20:24:45 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	lookforplayer(t_cub3d *cub3d, int i, int j)
{
	char	*player;
	char	*player_chars;

	player_chars = "WNES";
	player = ft_strchr(player_chars, cub3d->map.map[i][j]);
	if (!player)
		return (1);
	cub3d->player.pa = (player - player_chars) * (PI / 2);
	cub3d->player.px = i * cub3d->size;
	cub3d->player.py = j * cub3d->size;
	printf("Player found at %d, %d\n", i, j);
	printf("Player angle: %f\n", cub3d->player.pa);
	return (0);
}

int	get_player(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	found;

	i = 0;
	j = 0;
	found = 0;
	while (cub3d->map.map[i])
	{
		j = 0;
		while (cub3d->map.map[i][j])
		{
			if (!lookforplayer(cub3d, i, j))
				found++;
			j++;
		}
		i++;
	}
	if (!found)
		return (exit_error("Player not found"), 1);
	else if (found > 1)
		return (exit_error("Multiple players found"), 1);
	return (0);
}
