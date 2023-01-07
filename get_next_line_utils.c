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

/**
 * Free all allocated strings in an array of strings and free the array.
 *
 * @param tab Array of strings
 * @param strnum Maxium number of strings
 *
 * @return NULL
 */
char	*ft_freemany(char **tab, size_t strnum)
{
	while (strnum--)
		if (tab[strnum])
			free(tab[strnum]);
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
char	**ft_alloczero_chararr(char **arr, int arrsize, int pos, int strsize)
{
	if (!arr)
		arr = (char **)malloc((arrsize) * sizeof(char *));
	if (!arr)
		return (NULL);
	if (!arr[pos])
	{
		arr[pos] = (char *)malloc((strsize) * sizeof(char));
		if (!arr[pos])
		{
			ft_freemany(arr, arrsize);
			return (NULL);
		}
		ft_setchar(arr[pos], '0', strsize);
	}
	return (arr);
}

/**
 * Find the position of a character in a buffer.
 *
 * @param c The character to find.
 * @param buff The buffer to seek.
 * @param size The buffer size.
 *
 * @return The position of c in buff or -1 if not found.
 **/
ssize_t	ft_buffchr_nextpos(int c, char *buff, ssize_t size)
{
	ssize_t	i;

	i = 0;
	while (i < size)
	{
		if (buff[i++] == (char)c)
			return (i);
	}
	return (-1);
}

// A implémenter
char	*ft_realloc(char *p, size_t size)
{
	return (realloc(p, size));
}
