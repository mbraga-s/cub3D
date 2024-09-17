/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:47:08 by manumart          #+#    #+#             */
/*   Updated: 2024/09/15 10:47:48 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = 0;
	while (str && str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_str(char *str)
{
	if (str == NULL)
		return ;
	free(str);
}

void	exit_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}

void	free_textures(t_cub3d *cub3d)
{
	if (cub3d->map.n_texture)
		free(cub3d->map.n_texture);
	if (cub3d->map.s_texture)
		free(cub3d->map.s_texture);
	if (cub3d->map.w_texture)
		free(cub3d->map.w_texture);
	if (cub3d->map.e_texture)
		free(cub3d->map.e_texture);
}
