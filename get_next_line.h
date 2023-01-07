/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:35:03 by agaley            #+#    #+#             */
/*   Updated: 2023/01/07 02:23:13 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# ifndef MAX_OPEN
#  define MAX_OPEN 5
# endif

char	*ft_setchar(char *s, char c, size_t n);
char	*ft_freemany(char **tab, size_t wn);
char	**ft_alloczero_chararr(char **arr, int size, int strpos, int len);
ssize_t	ft_buffchr_nextpos(int c, char *buff, ssize_t size);
char	*ft_realloc(char *p, size_t size);

char	*get_next_line(int fd);

#endif
