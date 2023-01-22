#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char	*line;

	int fd = open("one_line_no_nl.txt", O_RDONLY);
	printf("%d\n", fd);
	line = get_next_line(fd);
	while (line)
	{
		printf("%lu|%s", strlen(line), line);
		free(line);
		line = get_next_line(fd);
	}
}
