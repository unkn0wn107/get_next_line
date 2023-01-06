/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:36:15 by agaley            #+#    #+#             */
/*   Updated: 2023/01/06 01:10:44 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_append_line(char *line, char *buf, ssize_t len)
{
	size_t	offset;
	ssize_t	i;

	//offset = sizeof(line);
	offset = 0;
	len = ft_buffchr_nextpos('\n', buf);
	if (len == -1)
		len = ft_buffchr_nextpos('\0', buf);
	if (len == -1)
		len = 0;
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
	return (line);
}

/**static char	*ft_get_line(int fd, char *buff)
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
  }*/

static void	ft_slide_buffer_to_pos(char *buf, ssize_t pos, ssize_t size)
{
	ssize_t	i;

	i = 0;
	while (pos < size)
		buf[i++] = buf[pos++];
	buf[i] = '\0';
}

static char	*ft_slinefrombuff(char *buf)
{
	ssize_t	len;
	char	*line;

	len = ft_buffchr_nextpos('\n', buf);
	if (len == -1)
		len = ft_buffchr_nextpos('\0', buf);
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
	if (ft_buffchr_nextpos('\n', buff[fd]) != -1)
		return (ft_slinefrombuff(buff[fd]));
	while (ft_buffchr_nextpos('\n', buff[fd]) == -1)
	{
		len = ft_buffchr_nextpos('\0', buff[fd]);
		if (len == -1 && line)
			len = BUFFER_SIZE;
		line = ft_append_line(line, buff[fd], len);
		if (!line)
			return (NULL);
		numread = read(fd, buff[fd], BUFFER_SIZE);
		if (numread < 0)
			return (ft_freemany(buff, MAX_OPEN));
		line = ft_append_line(line, buff[fd], numread);
	}
	return (line);
}

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
