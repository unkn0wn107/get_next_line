/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:26:27 by agaley            #+#    #+#             */
/*   Updated: 2023/01/07 02:22:59 by agaley           ###   ########lyon.fr   */
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

t_buff	*ft_getbuf(t_buff *buff, ssize_t fd)
{
	t_buff	failed;
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
		if (buff[i].fd == -1)
		{
			buff[i].fd = fd;
			buff[i].cur = 0;
			return (&(buff[i]));
		}
		i++;
	}
	return (NULL);
}

/**
 * Find the position of a character in a buffer.
 *
 * @param c The character to find.
 * @param buf The buffer to seek.
 * @param size The buffer size.
 *
 * @return The position of c in buff or -1 if not found.
 **/
ssize_t	ft_buffchr_nextpos(int c, t_buff buf, ssize_t size)
{
	ssize_t	i;

	i = 0;
	while (i < size)
	{
		if (buf.str[i++] == (char)c)
			return (i);
	}
	return (-1);
}

// A implémenter
char	*ft_realloc(char *p, size_t size)
{
	return (realloc(p, size));
}
