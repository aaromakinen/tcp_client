#ifndef LIST_H
#define LIST_H

int init_socket(char* ip_addr, int port);
char* read_from_port(int socket_fd, int port, char *msg, size_t len);


#endif
