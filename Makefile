CC=gcc
CFLAGS=-Wall 

all: client1 client2
clean: 
	rm client1 client1.o client2 client2.o

.PHONY: all

client1: client1.o socket.o socket_handler.o
	$(CC) -o client1 client1.o socket.o socket_handler.o
client2: client2.o socket.o socket_handler.o
	$(CC) -o client2 client2.o socket.o socket_handler.o
