/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 12:18:43 by gmersch           #+#    #+#             */
/*   Updated: 2023/12/01 12:18:44 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*verif_line(char **str, int *back_line)
{
	int	j;
	char	*line;
	
	j = 0;
	while(str[0][j] != '\0')
	{
		if (str[0][j] == '\n')
		{
			*back_line = 1;
			line = ft_substr(str[0], 0, j + 1);
			str[0] = ft_substr(str[0], j + 1, ft_strlen(str[0]) - (j + 1));
			return (line);
		}
		j++;
		*back_line = 0;
	}
	return (0);
}

char *get_next_line(int fd)
{
	int		i;
	char		buffer[BUFFER_SIZE + 1];
	static char	*str;
	char		*line;
	static int		back_line;
	
	back_line = 0;
	if (fd == 0)
		return (NULL);
	while(1)
	{
		if (back_line != 1)
		{
			i = read(fd, buffer, BUFFER_SIZE);
			if (i < 0)
				return (0);
			str = ft_strjoin(str, buffer);
		}
		if (i == 0 && (!str || str[0] == '\0'))
			break ;
		else if (i == 0)
		{
			line = ft_substr(str, 0, ft_strlen(str));
			free(str);
			str = NULL;
			return (line);
		}
		line = verif_line(&str, &back_line);
		if (line != 0)
			return (line);
	}
	return (0);
}

# include <stdio.h>
int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char	*str;
	int	i = 0;
	
	while (i < 5)
	{
		str = get_next_line(fd);
		printf("%s", str);
		free(str);
		i++;
	}
	close(fd);
	return (0);
}
