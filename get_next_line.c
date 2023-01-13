/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2023/01/10 23:29:54 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t ft_bufflen(t_buff buf, ssize_t len)
{
	if (len == -1)
		len = ft_buffchr_nextpos('\n', buf, BUFFER_SIZE) + 1;
	if (len == -1)
		len = ft_buffchr_nextpos('\0', buf, BUFFER_SIZE) + 1;
	if (len == 0 && buf.cur != 0 && buf.cur < BUFFER_SIZE)
		len = BUFFER_SIZE;
	if (len == -1)
        len = 0;
	return (len);
}

static void ft_append_line(t_line *line, t_buff *buf, ssize_t len)
{
	len = ft_bufflen(*buf, len);
	if (line->len + len >= BUFFER_SIZE)
		line->str = ft_realloc(line->str, (line->len + len) * sizeof(char));
	else if (len != 0)
		line->str = malloc((line->len + len - buf->cur) * sizeof(char));
	if (!line->str)
		return ;
	while (buf->cur < len)
	{
		line->str[line->len + buf->cur] = buf->str[buf->cur];
		buf->cur++;
	}
	if (buf->cur >= BUFFER_SIZE)
		buf->cur = 0;
	line->len += len;
}

static char *ft_slinefrombuff(t_buff *buf)
{
	t_line	line = { 0, NULL };
	ssize_t pos;
	// ssize_t stop;
	// ssize_t i;
	// char *line;

	pos = -1;
	pos = ft_bufflen(*buf, pos);
	// line.str = malloc((pos - buf->cur + 1) * sizeof(char));
    ft_append_line(&line, buf, -1);
	if (!line.str)
		return (NULL);
	return (line.str);
	// pos = -1;
	// pos = ft_bufflen(*buf, pos);
	// line->str = malloc((pos - buf->cur + 1) * sizeof(char));
	// if (!line->str)
	// 	return (NULL);
	// i = 0;
	// stop = pos - buf->cur + 1;
	// while (i < stop && buf->cur < BUFFER_SIZE)
	// 	line[i++] = buf->str[buf->cur++];
	// if (buf->cur >= BUFFER_SIZE)
	// 	buf->cur = 0;
	// return (line);
 }

char *get_next_line(int fd)
{
	static t_buff buff[MAX_OPEN];
	t_line line;
	// t_line *line;
	ssize_t numread;
	// ssize_t len;

	line.len = 0;
	line.str = NULL;
	// line = &li;
    numread = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || MAX_OPEN <= 0 || BUFFER_SIZE > __SIZE_MAX__ / 2 || MAX_OPEN > __SIZE_MAX__ / 2 || !ft_getbuf(buff, fd))
		return (NULL);
	// if (ft_buffchr_nextpos('\n', *ft_getbuf(buff, fd), BUFFER_SIZE) != -1)
	// 	return (ft_slinefrombuff(ft_getbuf(buff, fd)));
	while (line.len == 0 || ft_buffchr_nextpos('\n', *ft_getbuf(buff, fd), BUFFER_SIZE) == -1)
	{
		// len = ft_bufflen(*ft_getbuf(buff, fd), -1);
		ft_append_line(&line, ft_getbuf(buff, fd), -1);
		if (line.len != 0 && !line.str)
			return (NULL);
		if (line.len > 0)
			return (line.str);
		numread = read(fd, ft_getbuf(buff, fd)->str, BUFFER_SIZE);
		if (numread <= 0)
		{
			ft_getbuf(buff, fd)->fd = -1;
			return (line.str);
		}
		ft_append_line(&line, ft_getbuf(buff, fd), -1);
	}
	return (line.str);
}
