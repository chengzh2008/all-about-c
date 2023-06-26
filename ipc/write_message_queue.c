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
    char buffer[20];
    msgid = msgget((key_t)12345, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        perror("message queue creation error\n");
    }

    while (1)
    {
        printf("enter some text info: \n");
        fgets(buffer, 20, stdin);
        if (strncmp(buffer, "end", 3) == 0)
        {
            break;
        }

        some_data.msg_type = 1;
        strcpy(some_data.some_text, buffer);

        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1)
        {
            perror("msg sent error\n");
        }
    }
}