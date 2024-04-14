CC=gcc
CFLAGS=-Wall

client1: client1.o socket.o
	$(CC) -o client1 client1.o socket.o
