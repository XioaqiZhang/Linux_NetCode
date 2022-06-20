#include "message.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

Message* Message_New(unsigned short type, unsigned short cmd, unsigned short index, unsigned short total, unsigned int length, const char* paylod)
{
    Message* ret = malloc(sizeof(Message) + length);

    if(ret)
    {
        ret->type   = type;
        ret->cmd    = cmd;
        ret->index  = index;
        ret->total  = total;
        ret->length = length;

        if(paylod)
        {
            memcpy(ret + 1, paylod, length);
        }
    }

    return ret;
}