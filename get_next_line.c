/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 15:31:52 by gmersch           #+#    #+#             */
/*   Updated: 2023/12/13 15:31:57 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ultimate_free(char *str, int j)
{
	char *buffer;
	
	buffer = ft_substr(str, j + 1, ft_strlen(str) - (j + 1));
	free(str);
	return (buffer);
}

char	*verif_line(char **str)
{
	int		j;
	char	*line;

	j = 0;
	if (!(*str) || str[0][0] == '\0')
		return (0);
	while (str[0][j] != '\0')
	{
		if (str[0][j] == '\n')
		{
			line = ft_substr(str[0], 0, j + 1);
			str[0] = ultimate_free(str[0], j);
			return (line);
		}
		j++;
	}
	if (j != 0)
	{
		line = ft_substr(str[0], 0, j + 1);
		str[0] = ultimate_free(str[0], j);
		return (line);
	}
	free(str);
	return (0);
}

int	str_creator(int fd, char **str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		len;

	len = 1;
	while (len != 0)
	{
		len = read(fd, buffer, BUFFER_SIZE);
		buffer[len] = '\0';
		if (len == 0)
			break ;
		if (len < 0)
			return (len);
		temp = ft_strjoin(str[0], buffer);
		str[0] = temp;
	}
	//if (temp)
	//	free(temp);
	return (0);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			verif;

	static char	*str = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (/* i != 0 && is_loop == 2 */!str)
	{
		verif = str_creator(fd, &str);
		if (verif < 0)
			return (0);
	}
	line = verif_line(&str);
	if (line != 0)
		return (line);
	return (0);
}
