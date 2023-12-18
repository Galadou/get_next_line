/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:47:04 by gmersch           #+#    #+#             */
/*   Updated: 2023/12/18 15:47:09 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	str_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*verif_line(char **str)
{
	int		j;
	char	*line;
	char	*temp;

	j = 0;
	if (!(*str) || str[0][0] == '\0')
		return (NULL);
	while (str[0][j] != '\0')
	{
		if (str[0][j] == '\n')
		{
			line = ft_substr(str[0], 0, j + 1);
			if (ft_strlen(str[0]) != (j + 1))
				temp = ft_substr(str[0], j + 1, ft_strlen(str[0]) - (j));
			else
				temp = NULL;
			free(str[0]);
			str[0] = temp;
			return (line);
		}
		j++;
	}
	line = ft_substr(str[0], 0, j);
	return (line);
}

static int	str_creator(int fd, char **str, int *len)
{
	char	*buffer;
	char	*temp;

	*len = BUFFER_SIZE;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	while (*len == BUFFER_SIZE)
	{
		*len = read(fd, buffer, BUFFER_SIZE);
		if (*len < 0)
		{
			free(buffer);
			return (0);
		}
		if (*len == 0)
			break ;
		buffer[*len] = '\0';
		temp = ft_strjoin(str[0], buffer);
		str[0] = temp;
		if (str_check(buffer) == 1)
			break ;
	}
	free(buffer);
	return (1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[1024];
	int			len;
	int			verif;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	len = 0;
	verif = 0;
	if (!str[fd] || str_check(str[fd]) == 0)
		verif = str_creator(fd, &str[fd], &len);
	if (str[fd] == NULL || verif == -1)
		return (NULL);
	line = verif_line(&str[fd]);
	if ((len < BUFFER_SIZE && str[fd] && (ft_strcmp(str[fd], line) == 0
				&& verif == 1)) || BUFFER_SIZE == 1)
	{
		free(str[fd]);
		str[fd] = NULL;
	}
	if (line)
		return (line);
	return (NULL);
}
