/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manumart <manumart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 20:01:25 by manumart          #+#    #+#             */
/*   Updated: 2024/08/01 19:20:53 by manumart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 0;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		while (stash[i])
			stash[i++] = 0;
		return (NULL);
	}
	line = NULL;
	while (stash[0] || read(fd, stash, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin_gnl(line, stash);
		if (stashfree(stash))
			break ;
	}
	return (line);
}

/*int main()
{
	int fd = 0;
	char *to_free;
	fd = open("./fd.txt", O_RDWR);
	to_free = get_next_line(fd);
	printf("%s", to_free);
	close(fd);
}*/
