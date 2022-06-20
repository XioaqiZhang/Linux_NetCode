#ifndef MESSAGE_H
#define MESSAGE_H

typedef struct message
{
    unsigned short type;
    unsigned short cmd;
    unsigned short index;
    unsigned short total;
    unsigned int length;
    unsigned char paylod[];
}Message;


Message* Message_New(unsigned short type,
                     unsigned short cmd,
                     unsigned short index,
                     unsigned short total,
                     unsigned int length,
                     const char* paylod);

#endif