#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include "socket.h"
#include <arpa/inet.h>

#define IP_ADDR "172.17.0.1"
#define BUFFER_LEN 100
#define MODE_1_FREQ ((unsigned char*)"\x00\x02\x00\x02\x00\xFF\x00\x32")
#define MODE_1_AMP ((unsigned char*)"\x00\x02\x00\x01\x00\xaa\x1f\x40")
#define MODE_2_FREQ ((unsigned char*)"\x00\x02\x00\x02\x00\xFF\x07\xd0")
#define MODE_2_AMP ((unsigned char*)"\x00\x02\x00\x01\x00\xaa\x0f\xa0")
#define MODE_1 0
#define MODE_2 1

static long long time_in_ms(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}

static int send_udp_cmd(int socket_fd, int port, short mode) {
	struct sockaddr_in server_addr;
	const unsigned char *udp_command[4] = {
		MODE_1_FREQ,
		MODE_1_AMP,
		MODE_2_FREQ,
		MODE_2_AMP,
	};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(IP_ADDR);
	for (int i = 0; i < 2; i++) {
		if (sendto(socket_fd, udp_command[mode*2 + i], 8,
				0 , (struct sockaddr*)&server_addr,
				sizeof(server_addr)) < 0) {
			printf("Unable to send message\n");
			return -1;
		}
	}
	return 0;
}

int main_loop(unsigned freq_ms, bool server_ctrl) {
	char *msg;
	char output[3][5];
	char buffer[BUFFER_LEN];
	int socket_fd[4], i;
	int ports[4] = { 4000, 4001, 4002, 4003 };
	long converted;
	short mode = -1;

	for (i = 0; i < 4; i++) {
		socket_fd[i] = init_socket(IP_ADDR, ports[i], i ? false : true);
		if (socket_fd[i] == -1)
			return -1;
	}
	while(1) {
		for (i = 1; i < 4; i++) {
			msg = read_from_port(socket_fd[i], ports[i], buffer,
					BUFFER_LEN);
			memcpy(output[i-1], msg, 5);
		}
		/* We assume here that the output of 4003 (out3) will always be
		 * positive number we so don't care that values below zero
		 * wouldn't send a command */
		if (server_ctrl && isdigit(output[2][0])) {
			converted = strtol(output[2], NULL, 10);
			if (converted >= 3 && mode != MODE_1) {
				send_udp_cmd(socket_fd[0], 4000, MODE_1);
				mode = MODE_1;
			}
			else if (converted < 3 && mode != MODE_2) {
				send_udp_cmd(socket_fd[0], 4000, MODE_2);
				mode = MODE_2;
			}
		}

		printf("{\"timestamp\": %lld, \"out1\": \"%s\", \"out2\": \"%s\", \"out3\": \"%s\"}\n",
				time_in_ms(), output[0], output[1], output[2]);
		usleep(freq_ms*1000);
	}
}
