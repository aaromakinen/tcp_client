#ifndef SOCKET_H
#define SOCKET_H
#include <stdbool.h>

int init_socket(char* ip_addr, int port, bool udp);
char* read_from_port(int socket_fd, int port, char *msg, size_t len);


#endif
