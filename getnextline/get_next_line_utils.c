/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbraga-s <mbraga-s@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 09:22:59 by mbraga-s          #+#    #+#             */
/*   Updated: 2023/02/13 18:03:58 by mbraga-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (0);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
	{
		ptr[i] = s2[j];
		i++;
		if (s2[j] == '\n')
			break ;
		j++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	ft_clean(char *ptr)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (ptr[i])
	{
		if (flag == 1)
		{
			ptr[j] = ptr[i];
			j++;
		}
		if (ptr[i] == '\n')
			flag = 1;
		ptr[i] = '\0';
		i++;
	}
	return (flag);
}
