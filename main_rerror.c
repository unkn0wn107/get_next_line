#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	char	*line;

	char *name = "read_error.txt";
	int fd = open(name, O_RDONLY);	
	line = get_next_line(fd);
	printf("%lu|%s", strlen(line), line);
	free(line);
	line = get_next_line(fd);
	printf("%lu|%s", strlen(line), line);
	free(line);
		char *temp;
		do {
			temp = get_next_line(fd);
			free(temp);
		} while (temp != NULL);
	close(fd);
	fd = open(name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%lu|%s", strlen(line), line);
		free(line);
		line = get_next_line(fd);
	}
}
