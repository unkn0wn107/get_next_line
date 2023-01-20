/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:26:27 by agaley            #+#    #+#             */
/*   Updated: 2023/01/20 22:54:32 by agaley           ###   ########lyon.fr   */
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

char	*ft_cleanbuf(t_buff *buff, t_line *line)
{
	ssize_t	i;

	buff->cur = 0;
	buff->fd = 0;
	buff->nr = 0;
	i = 0;
	while (i < BUFFER_SIZE)
		buff->str[i++] = '\0';
	return (line->str);
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
	size_t	i;
	char	*str;

	str = malloc(size * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
		str[i++] = '\0';
	if (!p)
		return (str);
	i = 0;
	while (p[i])
	{
		str[i] = p[i];
		i++;
	}
	free(p);
	return (str);
}
