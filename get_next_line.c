/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2023/01/07 02:23:44 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static void	ft_slide_buffer_to_pos(char *buf, ssize_t pos, ssize_t size)
{
	ssize_t	i;

	i = 0;
	while (pos < size)
	{
		buf[i] = buf[pos];
		buf[pos] = 0;
		i++;
		pos++;
	}
}

static ssize_t	ft_bufflen(char *buf, ssize_t len, char *line)
{
	if (line && len == -1)
		len = BUFFER_SIZE;
	if (len == -1)
		len = ft_buffchr_nextpos('\n', buf, BUFFER_SIZE);
	if (len == -1)
		len = ft_buffchr_nextpos('\0', buf, BUFFER_SIZE);
	if (len == -1)
		len = 0;
	return (len);
}

static char	*ft_append_line(char *line, char *buf, ssize_t len)
{
	size_t	offset;
	ssize_t	i;

	offset = 0;
	while (line && line[offset] && line[offset] != '\n')
		offset++;
	len = ft_bufflen(buf, len, line);
	line = ft_realloc(line, (offset + len) * sizeof(char));
	if (!line)
	{
		free(buf);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		line[offset + i] = buf[i];
		i++;
	}
	ft_slide_buffer_to_pos(buf, len, BUFFER_SIZE);
	return (line);
}

static char	*ft_slinefrombuff(char *buf)
{
	ssize_t	len;
	char	*line;

	len = ft_buffchr_nextpos('\n', buf, BUFFER_SIZE);
	if (len == -1)
		len = ft_buffchr_nextpos('\0', buf, BUFFER_SIZE);
	line = malloc(len * sizeof(char));
	if (!line)
		return (NULL);
	if (len + 1 < BUFFER_SIZE)
		ft_slide_buffer_to_pos(buf, len + 1, BUFFER_SIZE);
	else
		buf[0] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	**buff = NULL;
	ssize_t		numread;
	ssize_t		len;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > SSIZE_MAX)
		return (NULL);
	buff = ft_alloczero_chararr(buff, MAX_OPEN, fd, BUFFER_SIZE);
	if (!buff)
		return (NULL);
	if (ft_buffchr_nextpos('\n', buff[fd], BUFFER_SIZE) != -1)
		return (ft_append_line(line, buff[fd], -1));
	while (ft_buffchr_nextpos('\n', buff[fd], BUFFER_SIZE) == -1)
	{
		len = ft_buffchr_nextpos('\0', buff[fd], BUFFER_SIZE);
		if (len == -1 && line)
			len = BUFFER_SIZE;
		line = ft_append_line(line, buff[fd], len);
		if (!line)
			return (NULL);
		numread = read(fd, buff[fd], BUFFER_SIZE);
		if (numread <= 0)
			return (ft_freemany(buff, MAX_OPEN));
		line = ft_append_line(line, buff[fd], -1);
	}
	return (line);
}
