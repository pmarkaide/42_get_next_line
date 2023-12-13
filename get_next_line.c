/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaide <pmarkaid@student.hive.fi>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:56:05 by pmarkaid          #+#    #+#             */
/*   Updated: 2023/12/13 14:26:51 by pmarkaide        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

char *load_buffer(int fd, char *reminder)
{
	ssize_t	bytes_read;
	ssize_t	reminder_len;
	char buffer[BUFFER_SIZE];
	char *new_buffer;
	
	reminder_len = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while(bytes_read > 0)
	{
		if(reminder)
			reminder_len = ft_strlen(reminder);
		new_buffer = malloc(sizeof(char) * (reminder_len + BUFFER_SIZE + 1));
		if (!new_buffer)
			return(NULL);
		ft_memcpy(new_buffer, reminder, reminder_len);
		ft_memcpy(new_buffer + reminder_len, buffer, BUFFER_SIZE + 1);
		new_buffer[reminder_len + BUFFER_SIZE] = '\0';
		if (ft_strchr(new_buffer, '\n') != NULL)
			break;
		free(reminder);
		reminder = new_buffer;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(reminder);
	return (new_buffer);
}

char *get_next_line(int fd)
{
	static char *reminder;

	reminder = NULL;
	reminder = load_buffer(fd, reminder);
	return(reminder);
}
