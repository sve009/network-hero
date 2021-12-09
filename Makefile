CC=gcc
CFlAGS=-I.

conv: 
	$(CC) -c conv.c

client: conv.o
	$(CC) -o bin/client client.c conv.o

server: conv.o
	$(CC) -o bin/server server.c conv.o

