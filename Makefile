CC=gcc
CFlAGS=-I.

movelist:
	$(CC) -c movelist.c

actions:
	$(CC) -c actions.c

conv: 
	$(CC) -c conv.c

client: conv.o
	$(CC) -o bin/client client.c conv.o

server: conv.o movelist.o actions.o
	$(CC) -o bin/server server.c conv.o

