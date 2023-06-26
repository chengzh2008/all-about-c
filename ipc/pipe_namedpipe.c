#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <ctype.h>

int main()
{
    int fd = open("namedpipe", O_RDONLY);
    char c;

    while (read(fd, &c, 1) > 0)
    {
        printf("%c", toupper(c));
    }
    close(fd);
}