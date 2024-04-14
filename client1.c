#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"

#define ip_addr "172.17.0.1"
#define buffer_len 100



int main(int argc, char *argv[]) {
	char *msg;
	char buffer[buffer_len];
	int socket_fd;

	socket_fd = init_socket(ip_addr, 4001);
	if (socket_fd == -1)
		return -1;
	while(1) {
		msg = read_from_port(socket_fd, 4001, buffer,
				buffer_len);
		usleep(100000);
		printf("value: %s\n", msg);
	}
	return 0;
}
