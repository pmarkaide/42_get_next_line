/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmarkaid <pmarkaid@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 14:56:05 by pmarkaid          #+#    #+#             */
/*   Updated: 2023/12/15 13:52:47 by pmarkaid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *load_buffer(int fd, char *remainder)
{
	ssize_t	bytes_read;
	size_t	remainder_len;
	char buffer[BUFFER_SIZE];
	char *new_buffer;
	
	remainder_len = 0;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while(bytes_read > 0)
	{
		if(remainder)
			remainder_len = ft_strlenc(remainder, '\0');
		new_buffer = malloc(sizeof(char) * (remainder_len + bytes_read + 1));
		//printf("bytes read: %zd\n", bytes_read);
		if (!new_buffer)
			return(NULL);
		ft_memmove(new_buffer, remainder, remainder_len);
		ft_memmove(new_buffer + remainder_len, buffer, bytes_read);
		new_buffer[remainder_len + bytes_read] = '\0';
		free(remainder);
		remainder = new_buffer;
		if (ft_strchr(new_buffer, '\n') != NULL || bytes_read < BUFFER_SIZE)
			break;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		//printf("buffer: %s\n", new_buffer);
	}
	//printf("Buffer is: %s\n", new_buffer);
	return (remainder);
}

char *get_line(char *remainder)
{
	size_t line_len;
	char *line;

	line_len = ft_strlenc(remainder, '\n') + 1;
	line = malloc(sizeof(char) * (line_len + 1));
	if (!line)
		return(NULL);
	ft_memmove(line, remainder, line_len);
	line[line_len] = '\0';
	return(line);	
}

char *update_remainder(char *remainder)
{
	char *new_remainder;
	char *new_line;
	size_t remainder_len;
	
	if (ft_strchr(remainder, '\n') == NULL)
		return (NULL);
	new_line = ft_strchr(remainder, '\n');
	remainder_len = ft_strlenc(new_line, '\0');
	new_remainder = malloc(sizeof(char) * (remainder_len + 1));
	if (!new_remainder)
		return(NULL);
	ft_memmove(new_remainder, new_line + 1, remainder_len);
	free(remainder);
	//printf("updated remainder is: %s\n", new_remainder);
	return(new_remainder);	
}

char *get_next_line(int fd)
{
	static char *remainder;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = load_buffer(fd, remainder);
	line = get_line(remainder);
	remainder = update_remainder(remainder);
	if (remainder == NULL)
		return(NULL);
	return(line);
}

// int main()
// {
//    int fd;
//    char *line;

//     fd = open("file.txt", O_RDONLY);
//     if (fd == -1)
//     {
//         perror("Error opening file");
//         return 1; // Return an error code
//     }

//     while ((line = get_next_line(fd)) != NULL)
//     {
//         printf("%s", line);
//         free(line);
//     }

// 	//printf("%s", get_next_line(fd));
	
//     close(fd); // Close the file descriptor after the loop

//     return 0;
// }
