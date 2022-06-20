#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include "message.h"


static void hton(Message* m)
{
    m->type   = htons(m->type);
    m->cmd    = htons(m->cmd);
    m->index  = htons(m->index);
    m->total  = htons(m->total);
    m->length = htonl(m->length);
}


int main()
{
    printf("I'm client\n");
    int sock = 0;
    int len = 0;
    struct sockaddr_in addr = {0};
    char rev[128] = {0};
    char input[32] = {0};

    int r = 0;
    int i = 0;
    char* test = "Hello net!";
    Message* pm = NULL;
    
    
    sock = socket(PF_INET, SOCK_STREAM, 0);

    if(sock == -1)
    {
        printf("Create socket faild!\n");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(8888);


    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) == -1)
    {
        printf("Faild to connect \n");
        return -1;
    }

    printf("connect success\n");

    for (i=0; i<strlen(test); i++)
    {
        char buf[2] = {0};

        buf[0] = test[i];

        pm = Message_New(121, 122, i, strlen(test), 2, buf);

        hton(pm);
        send(sock, pm, sizeof(Message) + 2, 0);
        free(pm);
    }

    getchar();

    close(sock);
    
    return 0;
}