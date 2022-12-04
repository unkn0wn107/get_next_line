/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:26:27 by alex              #+#    #+#             */
/*   Updated: 2022/12/04 22:56:41 by alex             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_buffchr_nextpos(int c, char *buff, size_t start)
{
	while (start < BUFFER_SIZE)
	{
		if (buff[start] == (char)c)
			return (start);
		start++;
	}
	return (0);
}

// A implémenter
void	*ft_realloc(void *p, size_t size)
{
	return (realloc(p, size));
}
