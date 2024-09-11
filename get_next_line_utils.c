/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:27:17 by manumart          #+#    #+#             */
/*   Updated: 2024/08/01 19:20:49 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen_gnl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int	stashfree(char *buff)
{
	int	i;
	int	j;
	int	true;

	i = 0;
	j = 0;
	true = 0;
	while (buff[i])
	{
		if (true)
			buff[j++] = buff[i];
		if (buff[i] == '\n')
			true = 1;
		buff[i++] = '\0';
	}
	return (true);
}

char	*ft_strjoin_gnl(char *str1, char *str2)
{
	int		j;
	int		i;
	char	*mem;

	j = 0;
	i = 0;
	mem = malloc(ft_strlen_gnl(str1) + ft_strlen_gnl(str2) + 1);
	if (!mem)
		return (NULL);
	while (str1 && str1[i])
	{
		mem[i] = str1[i];
		i++;
	}
	free(str1);
	while (str2[j])
	{
		mem[i++] = str2[j];
		if (str2[j++] == '\n')
			break ;
	}
	mem[i] = '\0';
	return (mem);
}
