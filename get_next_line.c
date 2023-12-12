/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:56:05 by pmarkaid          #+#    #+#             */
/*   Updated: 2023/12/12 17:03:12 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//read_file, BUFFER_SIZE size, save to buffer
//process buffer
	//A.Scenario: buffer is longer than line
	//search for newline position
		// if no newline
			// return buffer
		// if newline
			// return until newline
			// update buffer pointer
	//B.Scenario: buffer is shorter than line
	//read more buffer and append to buffer
		// if newline
			// return line
			// update buffer pointer

char *load_buffer(int fd)
{
	ssize_t	bytes_read;
	ssize_t	total_len;
	char buffer[BUFFER_SIZE + 1];
	char *old_buffer;
	char *new_buffer;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while(bytes_read > 0)
	{
		total_len = ft_strlen(old_buffer + BUFFER_SIZE);
		new_buffer = malloc(sizeof(char) * (total_len + 1));
		if (!new_buffer)
			return(NULL);
		ft_memcpy(new_buffer, old_buffer, total_len - BUFFER_SIZE);
		ft_memcpy(new_buffer, buffer, BUFFER_SIZE);
		if (ft_strchr(new_buffer, '\n') == NULL)
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (new_buffer);
}




char *get_next_line(int fd)
{
	char *buffer;
	char *line;

	buffer = load_buffer(fd);
	line =	parse_line;
	buffer = update_buffer;
	
	return (line);
}