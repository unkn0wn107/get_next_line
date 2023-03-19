/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:26:27 by agaley            #+#    #+#             */
/*   Updated: 2023/03/19 20:24:07 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

// Vérifier pour fd = 0 si appelé en premier ou ensuite
t_buff	*ft_getbuf(t_buff *buff, ssize_t fd)
{
	ssize_t	i;

	i = 0;
	while (i < MAX_OPEN)
	{
		if (buff[i].fd == fd)
			return (&(buff[i]));
		if (buff[i].fd == 0 && buff[i].cur == 0 && !buff[i].str[0])
		{
			buff[i].fd = fd;
			return (&(buff[i]));
		}
		i++;
	}
	return (NULL);
}

/**
 * Reinitialize and clean the buffer and return line string.
 *
 * @param buff The buffer to clean up.
 * @param line To return line->str.
 *
 * @returns line->str, which could be NULL.
 **/
char	*ft_cleanbuf(t_buff *buf, t_line *line)
{
	ssize_t	i;

	if (buf->nr == -1 && line->str)
	{
		free(line->str);
		line->str = NULL;
	}
	buf->cur = 0;
	buf->nr = 0;
	i = 0;
	while (i < BUFFER_SIZE)
		buf->str[i++] = '\0';
	return (line->str);
}

/**
 * Find the position of an EOL from the start of a size-long buffer.
 *
 * @param buf The buffer to seek.
 * @param start The buffer size.
 * @param size The buffer size.
 *
 * @return The position of an EOL in buff or -1 if not found.
 **/
ssize_t	ft_buffeol_nextpos(char *buf, ssize_t start, ssize_t size)
{
	if (!buf)
		return (-1);
	while (start < size)
	{
		if (buf[start] == '\n')
			return (start);
		start++;
	}
	return (-1);
}

/**
 * Changes the size of the string pointed to by p to size bytes.
 * 
 * @param p The pointer to reallocate.
 * @param size The new size of the string.
 * 
 * @return The pointer to the reallocated string, filled with '\0'.
 **/
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
