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

char	*ultimate_free(char **str, int j)
{
	char *buffer;
	
	buffer = ft_substr(str[0], j + 1, ft_strlen(str[0]) - (j + 1));
	free(str[0]);
	return (buffer);
}

char	*verif_line(char **str)
{
	int		j;
	char	*line;
	char	*buffer;

	j = 0;
	if (!(*str) || str[0][0] == '\0')
		return (0);
	while (str[0][j] != '\0')
	{
		if (str[0][j] == '\n')
		{
			line = ft_substr(str[0], 0, j + 1);
			buffer = ultimate_free(str, j);
			str[0] = buffer;
			return (line);
		}
		j++;
	}
	if (j != 0)
	{
		line = ft_substr(str[0], 0, j + 1);
		buffer = ultimate_free(str, j);
		str[0] = buffer;
		return (line);
	}
	free(str);
	return (0);
}

int	str_creator(int *i, int fd, char **str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;

	while (i != 0)
	{
		*i = read(fd, buffer, BUFFER_SIZE);
		buffer[*i] = '\0';
		if (*i == 0)
			break ;
		if (*i < 0)
			return (*i);
		temp = ft_strjoin(str[0], buffer);
		str[0] = temp;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char		*line;
	int			verif;
	static int	i;
	static int	is_loop;
	static char	*str;

	if (!is_loop)
		is_loop = 2;
	if (is_loop == 2)
		i = 1;
	if (fd == 0)
		return (NULL);
	if (i != 0 && is_loop == 2)
	{
		verif = str_creator(&i, fd, &str);
		if (verif < 0)
			return (0);
	}
	is_loop = 1;
	line = verif_line(&str);
	if (line != 0)
		return (line);
	return (0);
}
