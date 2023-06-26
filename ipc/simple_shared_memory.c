#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define PAGESIZE 4096

// not shared
int v = 5;

int main(int argc, char **argv)
{

    // shared memory.
    // it is easy to bind the shared memory using mmap
    uint8_t *shared_memory = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE,
                                  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *shared_memory = 34;
    if (fork() == 0)
    {
        *shared_memory = 15;
        v = 80;
    }
    else
    {
        wait(NULL);
    }

    printf("Not shared. %i\n", v);
    printf("Shared. %i\n", *shared_memory);
}
