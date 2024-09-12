/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 21:48:37 by manumart          #+#    #+#             */
/*   Updated: 2024/09/11 16:24:25 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	lookforplr(t_cub3d *cub3d, int i, int j)
{
	char	*plr;
	char	*plr_chars;

	plr_chars = "WNES";
	plr = ft_strchr(plr_chars, cub3d->map.map[i][j]);
	if (!plr)
		return (1);
	cub3d->plr.pa = (plr - plr_chars) * (PI / 2);
	cub3d->plr.px = i * cub3d->size;
	cub3d->plr.py = j * cub3d->size;
	printf("Player found at %d, %d\n", i, j);
	printf("Player angle: %f\n", cub3d->plr.pa);
	return (0);
}

int	get_plr(t_cub3d *cub3d)
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
			if (!lookforplr(cub3d, i, j))
				found++;
			j++;
		}
		i++;
	}
	if (!found)
		return (exit_error("Player not found"), 1);
	else if (found > 1)
		return (exit_error("Multiple plrs found"), 1);
	return (0);
}
