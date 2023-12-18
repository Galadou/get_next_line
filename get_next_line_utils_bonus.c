/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmersch <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:35:18 by gmersch           #+#    #+#             */
/*   Updated: 2023/12/18 15:35:22 by gmersch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		i = ft_strlen(src);
		return (i);
	}
	while (size - 1 > i && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	i = ft_strlen(src);
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		f;
	int		len;
	char	*str;

	f = 0;
	if (s2 == 0)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((len +1) * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1) +1);
	i = ft_strlen(s1);
	while (i < len)
	{
		str[i] = s2[f];
		f++;
		i++;
	}
	str[i] = '\0';
	if (s1)
		free(s1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	size_t			j;
	char			*str;

	if (!s)
		return (0);
	if ((start > (unsigned int)ft_strlen(s)))
		return (NULL);
	j = ft_strlen(&s[start]);
	if (j < len)
		len = j;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*pt_s1;
	const unsigned char	*pt_s2;

	pt_s1 = (const unsigned char *)s1;
	pt_s2 = (const unsigned char *)s2;
	if (ft_strlen(s1) == 0 || ft_strlen(s2) == 0)
		return (*pt_s1 - *pt_s2);
	if (*pt_s1 == '\0' || *pt_s2 == '\0')
		return (*pt_s1 - *pt_s2);
	while (*pt_s1 != '\0')
	{
		if (*pt_s1 != *pt_s2)
			return (*pt_s1 - *pt_s2);
		pt_s1++;
		pt_s2++;
	}
	if (*pt_s1 != *pt_s2)
		return (*pt_s1 - *pt_s2);
	return (0);
}
