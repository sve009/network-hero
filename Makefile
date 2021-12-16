CC=gcc
CFlAGS=-I.

cyberparser:
	$(CC) -o tools/cyberparser tools/cyberparser.c

movelist:
	$(CC) -c movelist.c

actions:
	$(CC) -c actions.c

client: 
	$(CC) -o bin/client client.c

server: movelist.o actions.o
	$(CC) -o bin/server server.c actions.o movelist.o -lpthread -lm

