/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2023/03/02 20:36:44 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static ssize_t	ft_bufflen(t_buff *buf, ssize_t len)
{
	if (len == -1)
		len = ft_buffeol_nextpos(buf->str, buf->cur, buf->nr) + 1;
	if (len == 0 && buf->cur < buf->nr)
		len = buf->nr;
	if (len == -1)
		len = 0;
	return (len);
}

static void	ft_append_line(t_line *line, t_buff *buf, ssize_t len)
{
	ssize_t	size;

	len = ft_bufflen(buf, len);
	if (buf->cur == buf->nr || buf->nr == 0)
		return ;
	size = line->cur + len - buf->cur + 1;
	line->str = ft_realloc(line->str, size * sizeof(char));
	if (!line->str)
		return ;
	while (buf->cur < buf->nr && buf->str[buf->cur] != '\n')
		line->str[line->cur++] = buf->str[buf->cur++];
	if (buf->cur < buf->nr && line->cur < size && buf->str[buf->cur] == '\n')
	{
		line->str[line->cur++] = '\n';
		buf->cur++;
	}
	if (line->cur < size && buf->nr < BUFFER_SIZE)
		line->str[line->cur++] = '\0';
}

char	*get_next_line(int fd)
{
	static t_buff	buff[MAX_OPEN];
	t_buff			*buf;
	t_line			line;

	line.cur = 0;
	line.str = NULL;
	buf = ft_getbuf(buff, fd);
	if (fd < 0 || !buf || BUFFER_SIZE <= 0 || MAX_OPEN <= 0
		|| BUFFER_SIZE > __SIZE_MAX__ / 2 || MAX_OPEN > __SIZE_MAX__ / 2)
		return (NULL);
	while (ft_buffeol_nextpos(line.str, 0, line.cur + 1) == -1)
	{
		ft_append_line(&line, buf, -1);
		if (line.cur != 0 && !line.str)
			return (NULL);
		if (line.cur > 0 && ((buf->nr < BUFFER_SIZE)
				|| ft_buffeol_nextpos(line.str, 0, line.cur + 1) >= 0))
			return (line.str);
		buf->nr = read(fd, buf->str, BUFFER_SIZE);
		buf->cur = 0;
		if (buf->nr <= 0)
			return (ft_cleanbuf(buf, &line));
	}
	return (line.str);
}
