/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keyn <keyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 15:00:37 by arocca            #+#    #+#             */
/*   Updated: 2024/12/17 11:55:14 by keyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>

t_fd_list	*get_node(t_fd_list **head, int fd)
{
	t_fd_list	*current;
	t_fd_list	*new;

	current = *head;
	while (current)
	{
		if (current -> fd == fd)
			return (current);
		current = current->next;
	}
	new = malloc(sizeof(t_fd_list));
	if (!new)
		return (NULL);
	new -> fd = fd;
	new -> buffer = NULL;
	new -> next = *head;
	*head = new;
	return (new);
}

char	*free_node(t_fd_list **head, int fd)
{
	t_fd_list	*previous;
	t_fd_list	*current;

	current = *head;
	previous = NULL;
	while (current)
	{
		if (current -> fd == fd)
		{
			if (previous)
				previous -> next = current -> next;
			else
				*head = current -> next;
			free(current -> buffer);
			free(current);
			current = NULL;
			return (NULL);
		}
		previous = current;
		current = current -> next;
	}
	return (NULL);
}

char	*update_buffer(int fd, char buffer[], char **node_buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read && !ft_strchr(*node_buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(*node_buffer);
			*node_buffer = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		temp = *node_buffer;
		*node_buffer = ft_strjoin(*node_buffer, buffer);
		if (!*node_buffer)
		{
			free(*node_buffer);
			return (NULL);
		}
		free(temp);
	}
	return (*node_buffer);
}

char	*extract_newline(char **node_buffer)
{
	char	*endline_pos;
	char	*line;
	char	*temp;

	if (!*node_buffer || !**node_buffer)
		return (NULL);
	endline_pos = ft_strchr(*node_buffer, '\n');
	if (endline_pos || **node_buffer)
	{
		if (endline_pos)
		{
			line = ft_substr(*node_buffer, 0, (endline_pos - *node_buffer) + 1);
			temp = ft_strdup(endline_pos + 1);
		}
		else
		{
			line = ft_strdup(*node_buffer);
			temp = NULL;
		}
		return (check_line(&line, &temp, node_buffer));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*head = NULL;
	char				*buffer;
	t_fd_list			*node_fd;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	node_fd = get_node(&head, fd);
	if (!node_fd)
		return (NULL);
	if (node_fd -> buffer == NULL)
		node_fd -> buffer = ft_strdup("");
	if (!node_fd -> buffer || !update_buffer(fd, buffer, &node_fd->buffer))
	{
		free(buffer);
		return (free_node(&head, fd));
	}
	line = extract_newline(&node_fd -> buffer);
	free(buffer);
	if (line)
		return (line);
	return (free_node(&head, fd));
}
