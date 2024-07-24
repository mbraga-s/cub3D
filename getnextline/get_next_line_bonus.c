/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:51:44 by mbraga-s          #+#    #+#             */
/*   Updated: 2023/02/17 15:51:44 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	stash[FOPEN_MAX][BUFFER_SIZE + 1];
	int			i;

	i = 0;
	line = 0;
	if (fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0 )
	{
		while (stash[fd][i])
			stash[fd][i++] = 0;
		return (NULL);
	}
	while (stash[fd][0] || read (fd, stash[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, stash[fd]);
		if (ft_clean(stash[fd]))
			break ;
	}
	return (line);
}
