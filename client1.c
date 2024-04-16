#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include <math.h>
#include <sys/time.h>

#define ip_addr "172.17.0.1"
#define buffer_len 100

long long time_in_ms(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

int main(int argc, char *argv[]) {
	char *msg;
	char val[3][5];
	char buffer[buffer_len];
	int socket_fd[4], i;
	int ports[4] = { 4000, 4001, 4002, 4003 };

	for (i = 1; i < 4; i++) {
		socket_fd[i] = init_socket(ip_addr, ports[i]);
		if (socket_fd[i] == -1)
			return -1;
	}
	while(1) {
		for (i = 1; i < 4; i++) {
			msg = read_from_port(socket_fd[i], ports[i], buffer,
					buffer_len);
			memcpy(val[i-1], msg, 5);
		}

		printf("{\"timestamp\": %lld, \"out1\": \"%s\", \"out2\": \"%s\", \"out3\": \"%s\"}\n", time_in_ms(), val[0], val[1], val[2]);
		usleep(100000);
	}
	return 0;
}
