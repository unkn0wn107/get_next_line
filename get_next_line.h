/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:35:03 by agaley            #+#    #+#             */
/*   Updated: 2023/01/08 21:39:46 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# ifndef MAX_OPEN
#  define MAX_OPEN 1
# endif

typedef struct s_buff
{
	int		fd;
	ssize_t	cur;
	char	str[BUFFER_SIZE];
}t_buff;

typedef struct s_line
{
	size_t	len;
	char	*str;
}t_line;

char	*ft_setchar(char *s, char c, size_t n);
t_buff	*ft_getbuf(t_buff *buff, ssize_t fd);
ssize_t	ft_buffchr_nextpos(int c, t_buff buff, ssize_t size);
char	*ft_realloc(char *p, size_t size);

char	*get_next_line(int fd);

#endif
