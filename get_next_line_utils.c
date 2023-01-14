/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:26:27 by agaley            #+#    #+#             */
/*   Updated: 2023/01/08 17:57:11 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Sets the first n bytes of the memory pointed to by s to the value of c.
 *
 * @param s The memory area to set.
 * @param c The value to set the memory area to.
 * @param n The number of bytes to set.
 *
 * @returns A pointer to s.
 **/
char	*ft_setchar(char *s, char c, size_t n)
{
	while (n > 0)
		s[--n] = c;
	return (s);
}

// Vérifier pour fd = 0 si appelé en premier ou ensuite
t_buff	*ft_getbuf(t_buff *buff, ssize_t fd)
{
	ssize_t	i;

	i = 0;
	while (i < MAX_OPEN)
	{
		if (buff[i].fd == fd)
			return (&(buff[i]));
		i++;
	}
	i = 0;
	while (i < MAX_OPEN)
	{
		if (buff[i].fd == 0 && buff[i].cur == 0 && !buff[i].str[0])
		{
			buff[i].fd = fd;
			return (&(buff[i]));
		}
		i++;
	}
	return (NULL);
}

void	ft_cleanbuf(t_buff *buff, ssize_t fd)
{
	t_buff	*buf;
	ssize_t	i;

	buf = ft_getbuf(buff, fd);
	buf->cur = 0;
	buf->fd = 0;
	buf->nr = 0;
	i = 0;
	while (i < BUFFER_SIZE)
		buf->str[i++] = '\0';
}

/**
 * Find the position of a character in a char buffer from start till size.
 *
 * @param c The character to find.
 * @param buf The buffer to seek.
 * @param start The buffer size.
 * @param size The buffer size.
 *
 * @return The position of c in buff or -1 if not found.
 **/
ssize_t	ft_buffchr_nextpos(int c, char *buf, ssize_t start, ssize_t size)
{
	while (start < size)
	{
		if (buf[start] == (char)c)
			return (start);
		start++;
	}
	return (-1);
}

// A implémenter
char	*ft_realloc(char *p, size_t size)
{
	if (!p)
		p = malloc(sizeof(char));
	return (realloc(p, size));
}
