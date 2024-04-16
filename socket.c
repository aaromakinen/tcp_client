#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int init_socket(char* ip_addr, int port) {
	int socket_fd;
	struct sockaddr_in server_addr;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0){
	    printf("Unable to create socket\n");
	    return -1;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr(ip_addr);
	if(connect(socket_fd, (struct sockaddr*)&server_addr,
			sizeof(server_addr)) < 0){
	    printf("Unable to connect\n");
	    return -1;
	}
	return socket_fd;
}

char* read_from_port(int socket_fd, int port, char* msg, size_t len) {
	size_t index;
	int i;
	char *value;

	memset(msg,'\0', len);
	msg[99] = '\0';
	if(recv(socket_fd, msg, len-1, MSG_DONTWAIT) < 0){
		value = "--";
	}
	else {
		/* We only consider value fully sent if it ends with new
		 * line so find the last new line and iterate back to
		 * find the second to last new line or the beginning of
		 * the buffer to get the last value
		 */
		index = strrchr(msg,'\n') - msg;
		msg[index] = '\0';
		for (i = index - 1; i >= 0; i--){
			if (msg[i] == '\n')
				break;
		}
		value = msg + i + 1;
	}
	return value;
}
