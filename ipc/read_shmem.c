#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/semaphore.h>
#include <sys/ipc.h>

#include "shared_memory.h"

#define BLOCK_SIZE 4096

int main(int argc, char **argv)
{
    if (argc != 1)
    {
        printf("usage - %s // no args", argv[0]);
        return -1;
    }

    // setup same semaphores
    sem_unlink(SEM_CONSUMER_FNAME);
    sem_unlink(SEM_PRODUCER_FNAME);

    sem_t *sem_prod = sem_open(SEM_PRODUCER_FNAME, IPC_CREAT, 0660, 0);
    if (sem_prod == SEM_FAILED)
    {
        perror("sem_open/producer failed");
    }

    sem_t *sem_cons = sem_open(SEM_CONSUMER_FNAME, IPC_CREAT, 0660, 1);
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

    while (true)
    {
        sem_wait(sem_prod);
        if (strlen(block) > 0)
        {
            printf("Reading: %s \n", block);
            bool done = (strcmp(block, "quit") == 0);
            block[0] = 0;
            if (done)
            {
                break;
            }
        }
        sem_post(sem_cons);
    }

    sem_close(sem_prod);
    sem_close(sem_cons);

    detach_memory_block(block);
    return 0;
}