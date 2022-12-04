/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2022/12/04 23:04:22 by alex             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// read definition
ssize_t	read(int fd, void *buf, size_t count);

// Get next position of c in buffer from start position
size_t	ft_buffchr_nextpos(int c, char *buff, size_t start)
{
	while (start < BUFFER_SIZE)
	{
		if (buff[start] == (char)c)
			return (start);
		start++;
	}
	return (0);
}

// Append to line from BUFF[cur] upto len and reset cur
static size_t	ft_append_line(char *line, char *buff, size_t cur, size_t len)
{
	size_t	offset;

	offset = sizeof(line);
	line = realloc(line, sizeof(char) * (offset + len - cur));
	while (cur++ < len)
		line[offset + cur] = buff[cur];
	if (cur == len - 1)
		cur = 0;
	return (cur);
}

static char	*ft_get_line(int fd, char *buff)
{
	char	*line;
	ssize_t	read_b;
	size_t	size;
	size_t	i;
	size_t	j;

	i = 0;
	read_b = read(fd, buff, BUFFER_SIZE);
	while (read_b > 0)
	{
		j = 0;
		while (buff[i] != '\n' && i++)
			j++;
		if (buff[i] == '\n')
			break ;
		else
			read_b = read(fd, buff, BUFFER_SIZE);
	}
	if (read_b == -1)
		return (0);
	return (i);
}

// Check si -D BUFFER_SIZE=-1 ne plante pas la déclaration
char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	static size_t	cur;
	char		*line;
	size_t		size;
	size_t		i;
	size_t		j;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	if (cur != 0)
		line = (char *)malloc(sizeof(char) * (BUFFER_SIZE - cur));
	while (read(fd, buff, BUFFER_SIZE) > 0)
	{
		i = 0;
		while (buff[i] != '\n')
			i++;
		i = i + BUFFER_SIZE;
		if (read(fd, buff, BUFFER_SIZE) == -1)
		{
			free(buff);
			return (NULL);
		}
		if (buff[i] == '\n')
			i++;
		line = (void *)malloc(sizeof(char) * i + 1);
		if (!line)
		{
			free(buff);
			return (NULL);
		}
		j = 0;
		while (j <= i && line[j] != '\n')
			line[j] = buff[j];
		return (line);
	}
	return (NULL);
}
