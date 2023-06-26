#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>

#define MAX_TEXT 50

struct my_msg
{
    long int msg_type;
    char some_text[MAX_TEXT];
};

int main()
{
    int msgid;
    struct my_msg some_data;
    msgid = msgget((key_t)12345, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        perror("message queue creation error\n");
    }

    long int msg_to_rec = 0;

    while (1)
    {
        if (msgrcv(msgid, (void *)&some_data, MAX_TEXT, msg_to_rec, 0) == -1)
        {
            perror("msg receive error\n");
        }

        printf("message is: %s\n", some_data.some_text);

        if (strncmp(some_data.some_text, "end", 3) == 0)
        {
            printf("quiting the process. \n");
        }
    }
}