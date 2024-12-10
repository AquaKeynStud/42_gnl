/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:07:53 by arocca            #+#    #+#             */
/*   Updated: 2024/12/09 16:35:06 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char			*str;
	unsigned char	ucc;

	str = (char *)s;
	ucc = (unsigned char)c;
	while (*str)
	{
		if (*str == ucc)
			return (str);
		str++;
	}
	if (ucc == '\0')
		return (str);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	len_s;

	len_s = 0;
	while (s[len_s])
		len_s++;
	if (!s || start > len_s)
		return (ft_strdup(""));
	if (len > len_s - start)
		len = len_s - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dest;
	int		i;

	size = 0;
	while (s[size])
		size++;
	i = 0;
	dest = (char *)malloc(sizeof(char) * size + 1);
	if (!dest)
		return (dest);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*start;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = 0;
	len_s2 = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[len_s1])
		len_s1++;
	while (s2[len_s2])
		len_s2++;
	res = (char *)malloc(sizeof(char) * (len_s1 + len_s2) + 1);
	if (!res)
		return (NULL);
	start = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res++ = '\0';
	return (start);
}

char	*check_line(char **line, char **temp, char **newline)
{
	if (!line || (!*line && !*temp))
	{
		free(*line);
		free(*temp);
		*line = NULL;
		*temp = NULL;
		free(*newline);
		*newline = NULL;
		return (NULL);
	}
	free(*newline);
	*newline = *temp;
	if (!*newline || !**newline)
	{
		free(*newline);
		*newline = NULL;
	}
	return (*line);
}
