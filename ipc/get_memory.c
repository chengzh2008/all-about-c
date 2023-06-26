#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

#define PAGESIZE 4096

int main()
{
    for (int i = 0; i < 5; i++)
    {
        char *ptr = malloc(50000);
        printf("Got memory! address=%p \n", ptr);
    }

    uint8_t *first = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    uint8_t *second = mmap(NULL, PAGESIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    printf("First: %p \n", first);
    printf("Secind: %p \n", second);
}