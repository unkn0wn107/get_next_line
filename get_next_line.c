/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2023/01/05 19:41:36 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// read definition
ssize_t	read(int fd, void *buf, size_t count);

static char	*ft_append_line(char *line, char *buf)
{
	size_t	len;
	size_t	offset;
	size_t	i;

	offset = sizeof(line);
	len = ft_buffchr_nextpos('\n', buf);
	line = realloc(line, (offset + len) * sizeof(char));
	if (!line)
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	while (i++ < len)
		line[offset + i] = buf[i];
	return (line);
}

static char	*ft_get_line(int fd, char *buff)
{
	char	*line;
	ssize_t	read_b;
	size_t	size;
	ssize_t	i;
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

char	*get_next_line(int fd)
{
	char		*line;
	static char	**buff;
	ssize_t		numread;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	buff = ft_alloczero_chararr(buff, MAX_OPEN, fd, BUFFER_SIZE);
	if (!buff)
		return (NULL);
	if (ft_buffchr_nextpos('\n', buff[fd]))
	  // reposition buffer after \n and return line
		return (ft_slinefrombuff(buff[fd]));
	while (ft_buffchr_nextpos('\n', buff[fd]) == -1)
	{
		line = ft_append_line(line, buff[fd]);
		if (!line)
			return (NULL);
		numread = ft_readtobuff(buff[fd]);
		if (numread < 0)
			return (ft_freemany(buff, MAX_OPEN));
		if (numread < BUFFER_SIZE)
		  // return line stopping at \0 and free buff[fd]
			return (ft_lastlinefrombuff(buff[fd], line));
	}
	return (line);

// // Check si -D BUFFER_SIZE=-1 ne plante pas la déclaration
// char	*get_next_line(int fd)
// {
// 	static char		buff[BUFFER_SIZE];
// 	static ssize_t	cur;
// 	char			*line;
// 	ssize_t			read_b;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX)
// 		return (NULL);
// 	while (ft_buffchr_nextpos('\n', buff, cur) == -1)
// 	{
// 		read_b = read(fd, buff, BUFFER_SIZE);
// 		if (read_b < 0 || (read_b == 0 && sizeof(line) == 0))
// 			return (NULL);
// 		ft_append_line(line, buff, 0, BUFFER_SIZE);
// 	}
// 	if (ft_buffchr_nextpos('\n', buff, cur) > 0)
// 	{

// 	}
// }
