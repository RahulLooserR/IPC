#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

#define PORT htons(20020)
#define MAX_CLIENT 32
#define BUFFER_SIZE 256

void check_error(int result, const char *msg);

ssize_t write_data_to_socket(int sockfd,
	   	const void *buf,
	   	size_t len, int flags,
		const struct sockaddr *dest_addr,
	   	socklen_t addrlen);

ssize_t read_data_from_socket(int sockfd,
	   	void *buf, size_t len,
	   	int flags, struct sockaddr *src_addr,
	   	socklen_t *addrlen);

#endif
