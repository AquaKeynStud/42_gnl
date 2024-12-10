/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arocca <arocca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:58:14 by arocca            #+#    #+#             */
/*   Updated: 2024/12/10 15:41:34 by arocca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*clean_line(char **newline)
{
	if (*newline)
	{
		free(*newline);
		*newline = NULL;
	}
	return (NULL);
}

char	*check_line(char **line, char **temp, char **newline)
{
	if (!line || (!*line && !*temp))
	{
		clean_line(line);
		clean_line(temp);
		return (clean_line(newline));
	}
	free(*newline);
	*newline = *temp;
	if (!*newline || !**newline)
		clean_line(newline);
	return (*line);
}

char	*update_buffer(int fd, char buffer[], char **newline)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read && !ft_strchr(*newline, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_line(newline));
		buffer[bytes_read] = '\0';
		temp = *newline;
		*newline = ft_strjoin(*newline, buffer);
		if (!*newline)
		{
			free(temp);
			return (clean_line(newline));
		}
		free(temp);
	}
	return (*newline);
}

char	*extract_newline(char **newline)
{
	char	*endline_pos;
	char	*line;
	char	*temp;

	if (!*newline || !**newline)
		return (clean_line(newline));
	endline_pos = ft_strchr(*newline, '\n');
	if (endline_pos || **newline)
	{
		if (endline_pos)
		{
			line = ft_substr(*newline, 0, (endline_pos - *newline) + 1);
			temp = ft_strdup(endline_pos + 1);
		}
		else
		{
			line = ft_strdup(*newline);
			temp = NULL;
		}
		return (check_line(&line, &temp, newline));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*newline = NULL;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (!newline)
		newline = ft_strdup("");
	if (!newline)
		return (clean_line(&buffer));
	newline = update_buffer(fd, buffer, &newline);
	free(buffer);
	if (!newline)
		return (NULL);
	return (extract_newline(&newline));
}
