CC = gcc
PORT=30001
CFLAGS = -DPORT=$(PORT) -g -Wall

all: countdown client

countdown: countdown.o wrapsock.o
	${CC} ${CFLAGS} -o $@ countdown.o  wrapsock.o

client: client.o wrapsock.o
	${CC} ${CFLAGS} -o $@ client.o wrapsock.o

countdown.o: countdown.c wrapsock.h
	${CC} ${CFLAGS}  -c $<

client.o: client.c wrapsock.h
	${CC} ${CFLAGS}  -c $<

%.o: %.c
	${CC} ${CFLAGS}  -c $<

clean:
	rm *.o countdown client
