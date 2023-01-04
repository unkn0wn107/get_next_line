/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 22:26:27 by agaley            #+#    #+#             */
/*   Updated: 2023/01/04 23:36:10 by agaley           ###   ########lyon.fr   */
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
static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s2;

	s2 = (unsigned char *)s;
	while (n--)
		s2[n] = (unsigned char)c;
	return (s);
}

char	**ft_freemany(char **tab, size_t wn)
{
	while (wn--)
		if (tab[wn])
			free(tab[wn]);
	free(tab);
	return (NULL);
}

/**
 * Allocate a string at strpos index in an array if not occupied.
 *
 * @param strpos The index of the string to allocate.
 * @param size The length of the allocated strings.
 *
 * @returns zeroed char at arr[strpos]
 **/
char	**ft_alloczero_chararr(char **arr, int arrsize, int strpos, int strsize)
{
	if (!arr)
		arr = (char **)malloc((arrsize + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!arr[strpos])
		arr[strpos] = (char *)malloc((strsize + 1) * sizeof(char));
	if (!arr[strpos])
	{
		ft_freemany(arr, arrsize);
		return (NULL);
	}
	ft_memset(arr[arrsize], '0', strsize + 1);
	return (arr);
}

size_t	ft_buffchr_nextpos(int c, char *buff)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (buff[i++] == (char)c)
			return (i);
	}
	return (0);
}

// A implémenter
void	*ft_realloc(void *p, size_t size)
{
	return (realloc(p, size));
}
