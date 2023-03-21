/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:26:27 by agaley            #+#    #+#             */
/*   Updated: 2023/03/21 00:28:30 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * Reinitialize and clean the buffer and return line string.
 *
 * @param buff The buffer to clean up.
 * @param line To return line->str.
 *
 * @returns line->str, which could be NULL.
 **/
char	*ft_cleanbuf(t_buff *buff, t_line *line)
{
	ssize_t	i;

	if (buff->nr == -1 && line->str)
	{
		free(line->str);
		line->str = NULL;
	}
	buff->cur = 0;
	buff->nr = 0;
	i = 0;
	while (i < BUFFER_SIZE)
		buff->str[i++] = '\0';
	return (line->str);
}

/**
 * Find the position of an EOL in a char buffer from start till size.
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
