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

static ssize_t	ft_bufflen(t_buff buf, ssize_t len)
{
	if (len == -1)
		len = ft_buffchr_nextpos('\n', buf.str, buf.cur, buf.nr) + 1;
	if (len == 0 && buf.cur < buf.nr)
		len = buf.nr;
	if (len == -1)
		len = 0;
	return (len);
}

static void	ft_append_line(t_line *line, t_buff *buf, ssize_t len)
{
	size_t	size;

	len = ft_bufflen(*buf, len);
	if (buf->cur == buf->nr || buf->nr == 0)
		return ;
	size = line->cur + len - buf->cur;
	line->str = ft_realloc(line->str, size * sizeof(char));
	if (!line->str)
		return ;
	while (buf->cur < buf->nr && buf->str[buf->cur] != '\n')
		line->str[line->cur++] = (char)buf->str[buf->cur++];
	if (buf->str[buf->cur] == '\n')
		line->str[line->cur++] = (char)buf->str[buf->cur++];
}

char	*get_next_line(int fd)
{
	static t_buff	buff[MAX_OPEN];
	t_buff			*bufptr;
	t_line			line;

	line.cur = 0;
	line.str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || MAX_OPEN <= 0
		|| BUFFER_SIZE > __SIZE_MAX__ / 2 || MAX_OPEN > __SIZE_MAX__ / 2
		|| !ft_getbuf(buff, fd))
		return (NULL);
	bufptr = ft_getbuf(buff, fd);
	while (ft_buffchr_nextpos('\n', line.str, 0, line.cur) == -1
		|| ft_buffchr_nextpos('\n', bufptr->str, bufptr->cur, bufptr->nr) == -1)
	{
		ft_append_line(&line, bufptr, -1);
		if (line.cur != 0 && !line.str)
			return (NULL);
		if (line.cur > 0 && bufptr->cur != bufptr->nr)
			return (line.str);
		bufptr->nr = read(fd, bufptr->str, BUFFER_SIZE);
		bufptr->cur = 0;
		if (bufptr->nr <= 0)
		{
			ft_cleanbuf(buff, fd);
			return (line.str);
		}
	}
	return (line.str);
}
