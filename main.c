#include    "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	char	*line;

	size_t fd = open("get_next_line.c", O_RDONLY);
	printf("%d\n", fd);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
}
