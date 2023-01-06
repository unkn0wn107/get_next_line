#include    "get_next_line.h"
#include <fcntl.h>

int main(void)
{
	size_t fd = open("get_next_line.c", O_RDONLY);
	printf("%d\n", fd);
	printf("%s", get_next_line(fd));
}
