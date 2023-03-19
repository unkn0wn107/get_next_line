/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaley <agaley@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 02:35:03 by agaley            #+#    #+#             */
/*   Updated: 2023/03/19 19:30:07 by agaley           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# ifndef MAX_OPEN
#  define MAX_OPEN 1024
# endif

typedef struct s_buff
{
	int		fd;
	ssize_t	cur;
	ssize_t	nr;
	char	str[BUFFER_SIZE];
}t_buff;

typedef struct s_line
{
	ssize_t	cur;
	char	*str;
}t_line;

t_buff	*ft_getbuf(t_buff *buff, ssize_t fd);
char	*ft_cleanbuf(t_buff *buf, t_line *line);
ssize_t	ft_buffeol_nextpos(char *buf, ssize_t start, ssize_t size);
char	*ft_realloc(char *p, size_t size);

char	*get_next_line(int fd);

#endif
