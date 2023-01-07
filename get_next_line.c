/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2023/01/07 03:02:36 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_bufflen(t_buff buf, ssize_t len)
{
	if (len == -1)
		len = ft_buffchr_nextpos('\n', buf, BUFFER_SIZE);
	if (len == -1)
		len = ft_buffchr_nextpos('\0', buf, BUFFER_SIZE);
	if (len == -1)
		len = 0;
	return (len);
}

static t_line	*ft_append_line(t_line *line, t_buff *buf, ssize_t len)
{
	len = ft_bufflen(*buf, len);
	line->str = ft_realloc(line->str, (line->len + len) * sizeof(char));
	if (!line->str)
		return (line);
	while (buf->cur < len)
	{
		line->str[line->len + buf->cur] = buf->str[buf->cur];
		buf->cur++;
	}
	if (len == BUFFER_SIZE)
		buf->cur = 0;
	return (line);
}

static char	*ft_slinefrombuff(t_buff *buf)
{
	ssize_t	len;
	char	*line;

	len = ft_buffchr_nextpos('\n', *buf, BUFFER_SIZE);
	if (len == -1)
		len = ft_buffchr_nextpos('\0', *buf, BUFFER_SIZE);
	line = malloc(len * sizeof(char));
	if (!line)
		return (NULL);
	if (len < BUFFER_SIZE)
		buf->cur = len;
	return (line);
}

char	*get_next_line(int fd)
{
	static t_buff	buff[MAX_OPEN];
	t_line			*line;
	ssize_t			numread;
	ssize_t			len;

	line->len = 0;
	line->str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || MAX_OPEN <= 0 || BUFFER_SIZE > SSIZE_MAX
		|| MAX_OPEN > SSIZE_MAX || !ft_getbuf(buff, fd))
		return (NULL);
	if (ft_buffchr_nextpos('\n', *ft_getbuf(buff, fd), BUFFER_SIZE) != -1)
		return (ft_slinefrombuff(ft_getbuf(buff, fd)));
	while (ft_buffchr_nextpos('\n', *ft_getbuf(buff, fd), BUFFER_SIZE) == -1)
	{
		len = ft_bufflen(*ft_getbuf(buff, fd), -1);
		line = ft_append_line(line, ft_getbuf(buff, fd), len);
		if (!line->str)
			return (NULL);
		numread = read(fd, ft_getbuf(buff, fd)->str, BUFFER_SIZE);
		if (numread <= 0)
		{
			ft_getbuf(buff, fd)->fd = -1;
			return (line->str);
		}
		line = ft_append_line(line, ft_getbuf(buff, fd), -1);
	}
	return (line->str);
}
