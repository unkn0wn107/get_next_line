/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2023/01/19 00:41:24 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static ssize_t	ft_bufflen(t_buff buf, ssize_t len)
{
	if (len == -1)
		len = ft_buffchr_nextpos('\n', buf.str, buf.cur, buf.nr - 1) + 1;
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
	size = line->cur + len - buf->cur + 1;
	line->str = ft_realloc(line->str, size * sizeof(char));
	if (!line->str)
		return ;
	while (buf->cur < buf->nr && buf->str[buf->cur] != '\n')
		line->str[line->cur++] = buf->str[buf->cur++];
	if (line->cur < size && buf->str[buf->cur] == '\n')
	{
		line->str[line->cur++] = '\n';
		buf->cur++;
	}
	if (line->cur < size && buf->nr < BUFFER_SIZE)
		line->str[line->cur++] = '\0';
}
	// if (line->cur < size)
	// 	line->str[line->cur++] = '\0';
	// if (buf->str[buf->cur] == '\n' && line->cur < size) {
	// 	if (buf->cur == buf->nr - 1 && buf->nr <= BUFFER_SIZE)
	// 	    line->str[line->cur++] = buf->str[buf->cur++];
	// 	else
	// 		line->str[line->cur++] = '\0';
	// }
	// if (line->cur < size)
	// 	line->str[line->cur++] = '\0';

char	*get_next_line(int fd)
{
	static t_buff	buff;
	t_buff			*bufptr;
	t_line			line;

	line.cur = 0;
	line.str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > __SIZE_MAX__ / 2)
		return (NULL);
	bufptr = &buff;
	while (ft_buffchr_nextpos('\n', line.str, 0, line.cur) == -1)
	{
		ft_append_line(&line, bufptr, -1);
		if (line.cur != 0 && !line.str)
			return (NULL);
		if (line.cur > 0 && (ft_buffchr_nextpos('\n', line.str, 0, line.cur) >= 0
			|| bufptr->nr < BUFFER_SIZE))
			return (line.str);
		bufptr->nr = read(fd, bufptr->str, BUFFER_SIZE);
		bufptr->cur = 0;
		if (bufptr->nr <= 0) // en cas d'erreur de lecture ?
		{
			ft_cleanbuf(&buff);
			// line.str = ft_realloc(line.str, (line.cur + 1) * sizeof(char));
			// line.str[line.cur] = '\0';
			return (line.str);
		}
	}
	// line.str = ft_realloc(line.str, (line.cur + 1) * sizeof(char));
	// line.str[line.cur] = '\0';
	return (line.str);
}
