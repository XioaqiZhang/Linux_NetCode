#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netinet/tcp.h>
#include "message.h"
#include "msg_parser.h"

int main()
{
    printf("I'm server\n");
    int server = 0;
    struct sockaddr_in saddr = {0};
    char rev[128] = {0};
    int client = 0;
    struct sockaddr_in caddr = {0};
    socklen_t asize = 0;
    int len = 0;
    char buf[32] = {0};
    int r = 0;
    MParser* parser = MParser_New();

    server = socket(PF_INET, SOCK_STREAM, 0);

    if(server == -1)
    {
        printf("Create server socket faild!\n");
        return -1;
    }

    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(8888);

    if(bind(server, (struct sockaddr*)&saddr, sizeof(saddr)) == -1)
    {
        printf("server bind faild!\n");
        return -1;
    }

    printf("bind server success!\n");

    /* second param is 1, mean only one client can be connect*/
    if(listen(server, 1) == -1)
    {
        // printf("")
        return -1;
    }

    printf("server start success!\n");

    while(1)
    {
        struct  tcp_info info = {0};
        int l = sizeof(info);
        
        asize = sizeof(caddr);

        client = accept(server, (struct sockaddr*)&caddr, &asize);

        if(client == -1)
        {
            printf("client accept error\n");
            return -1;
        }
        printf("client: %d\n", client);

        do 
        {
            getsockopt(client, IPPROTO_TCP, TCP_INFO, &info, (socklen_t*)&l);
            Message* m = MParser_ReadFd(parser, client);

            if(m)
            {
                // printf("type    = %d\n", m->type);
                // printf("cmd     = %d\n", m->cmd);
                // printf("index   = %d\n", m->index);
                // printf("total   = %d\n", m->total);
                // printf("length  = %d\n", m->length);
                printf("payload = %s", m->paylod);
                printf("\n");
            }

        }while ( info.tcpi_state == TCP_ESTABLISHED);

        close(client);
    }
    
    close(server);

    return 0;
}