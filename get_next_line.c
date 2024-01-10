/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:56:05 by pmarkaid          #+#    #+#             */
/*   Updated: 2024/01/10 11:10:01 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*load_buffer(int fd, char *remainder)
{
	ssize_t	bytes_read;
	size_t	remainder_len;
	char	buffer[BUFFER_SIZE];
	char	*new_buffer;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		remainder_len = ft_strlenc(remainder, '\0');
		new_buffer = malloc(sizeof(char) * (remainder_len + bytes_read + 1));
		if (!new_buffer)
			return (ft_free(&remainder));
		ft_memmove(new_buffer, remainder, remainder_len);
		ft_memmove(new_buffer + remainder_len, buffer, bytes_read);
		new_buffer[remainder_len + bytes_read] = '\0';
		free(remainder);
		remainder = new_buffer;
		if (ft_strchr(new_buffer, '\n') != NULL || bytes_read < BUFFER_SIZE)
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (ft_free(&remainder));
	return (remainder);
}

char	*parse_line(char *remainder)
{
	size_t	line_len;
	char	*newline;
	char	*line;

	if (!remainder)
		return (ft_free(&remainder));
	line_len = ft_strlenc(remainder, '\n');
	newline = ft_strchr(remainder, '\n');
	if (newline)
		line_len += 1;
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return (NULL);
	ft_memmove(line, remainder, line_len);
	line[line_len] = '\0';
	return (line);
}

char	*update_remainder(char *remainder)
{
	char	*new_remainder;
	char	*new_line;
	size_t	remainder_len;

	new_line = ft_strchr(remainder, '\n');
	if (!new_line)
		return (ft_free(&remainder));
	new_line = ft_strchr(remainder, '\n');
	remainder_len = ft_strlenc(new_line, '\0');
	new_remainder = malloc(sizeof(char) * (remainder_len + 1));
	if (!new_remainder)
		return (ft_free(&remainder));
	ft_memmove(new_remainder, new_line + 1, remainder_len);
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = load_buffer(fd, remainder);
	if (!remainder || *remainder == '\0')
		return (ft_free(&remainder));
	line = parse_line(remainder);
	if (!line)
		return (ft_free(&remainder));
	remainder = update_remainder(remainder);
	return (line);
}
