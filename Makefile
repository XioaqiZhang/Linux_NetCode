.PHONY : rebuild clean all

CC := gcc
MKDIR := mkdir
RM := rm -rf

DIR_OBJS := objs
DIR_TARGET := target

DIRS := ${DIR_OBJS} ${DIR_TARGET}

TARGET := ${DIR_TARGET}/out
SRCS := ${wildcard *.c}
OBJS := $(SRCS:.c=.o)
OBJS :=${addprefix ${DIR_OBJS}/, ${OBJS}}

${TARGET} : ${DIRS} ${OBJS}
	${CC} -o $@ ${OBJS}
	@echo "Target file ==> $@"

${DIRS} :
	${MKDIR} $@

${DIR_OBJS}/%.o : %.c
	${CC} -o $@ -c $^


client : ${DIRS}
	gcc client.c message.c -o ${DIR_TARGET}/client

server : ${DIRS}
	gcc server.c message.c msg_parser.c -o ${DIR_TARGET}/server


clean :
	${RM} ${DIRS}

rebuild : clean client server

all : ${TARGET}