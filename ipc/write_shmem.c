#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/semaphore.h>

#include "shared_memory.h"

#define BLOCK_SIZE 4096
#define NITERATION 10

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("usage - %s [stuff to write]", argv[0]);
        return -1;
    }

    // setup same semaphores
    sem_t *sem_prod = sem_open(SEM_PRODUCER_FNAME, 0);
    if (sem_prod == SEM_FAILED)
    {
        perror("sem_open/producer failed");
    }

    sem_t *sem_cons = sem_open(SEM_CONSUMER_FNAME, 0);
    if (sem_cons == SEM_FAILED)
    {
        perror("sem_open/consumer failed");
    }

    // grab the sahred memory block
    char *block = attach_memory_block(FILENAME, BLOCK_SIZE);

    if (block == NULL)
    {
        perror("could not get shared memory\n");
    }

    for (int i = 0; i < NITERATION; i++)
    {
        sem_wait(sem_cons);
        printf("Writing: \"%s\"\n", argv[1]);
        strncpy(block, argv[1], BLOCK_SIZE);
        sem_post(sem_prod);
    }

    sem_close(sem_prod);
    sem_close(sem_cons);

    detach_memory_block(block);
    return 0;
}