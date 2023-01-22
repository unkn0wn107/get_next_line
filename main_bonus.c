#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char	*line;
	char	*line2;

	int fd = open("one_line_no_nl.txt", O_RDONLY);
	int fd2 = open("get_next_line.c", O_RDONLY);

	printf("%d\n", fd);
	printf("%d\n", fd2);

	line = get_next_line(fd);
	printf("%lu|%s", strlen(line), line);
	free(line);
	line2 = get_next_line(fd2);
	printf("%lu|%s", strlen(line2), line2);
	free(line2);

	while (line)
	{
		printf("%lu|%s", strlen(line), line);
		free(line);
		line = get_next_line(fd);
	}

	while (line2)
	{
		printf("%lu|%s", strlen(line2), line2);
		free(line2);
		line2 = get_next_line(fd2);
	}
}
