#include <sys/select.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "msg_parser.h"


int main()
{
    MParser* p = MParser_New();
    char buf[] = {0x00, 0x01, 0x00, 0x02, 0x00};
    char another[] = {0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04};
    char data[] = {0x04, 0x11, 0x12, 0x13, 0x14};
    Message* m = MParser_ReadMem(p, buf, sizeof(buf));

    if(!m)
    {
        printf("parse again...\n");

        m = MParser_ReadMem(p, another, sizeof(another));
    }

    if(!m)
    {
        printf("parse again again...\n");

        m = MParser_ReadMem(p, data, sizeof(data));
    }

    printf("m = %p\n", m);

    if(m)
    {
        printf("type   = %d\n", m->type);
        printf("cmd    = %d\n", m->cmd);
        printf("index  = %d\n", m->index);
        printf("total  = %d\n", m->total);
        printf("length = %d\n", m->length);

        for(int i=0; i<m->length; i++)
        {
            printf("0x%02X\n", m->paylod[i]);
        }

        printf("\n");

        free(m);
    }

    MParser_Del(p);

    return 0;
}

