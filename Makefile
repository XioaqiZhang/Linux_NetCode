.PHONY : rebuild clean all

CC := gcc
MKDIR := mkdir
RM := rm -rf

DIR_OBJS := objs
DIR_TARGET := target

DIRS := ${DIR_OBJS} ${DIR_TARGET}

TARGET_CLIENT := ${DIR_TARGET}/client
TARGET_SERVER := ${DIR_TARGET}/server
SRCS := ${wildcard *.c}
OBJS := $(SRCS:.c=.o)
OBJS :=${addprefix ${DIR_OBJS}/, ${OBJS}}

all : client server

${DIRS} :
	${MKDIR} $@

${DIR_OBJS}/%.o : %.c
	${CC} -o $@ -c $^

client : ${DIRS}
	gcc client.c message.c -o ${TARGET_CLIENT}

server : ${DIRS}
	gcc server.c message.c msg_parser.c -o ${TARGET_SERVER}

clean :
	${RM} ${DIRS}

rebuild : clean client server
