#include "header.h"

void check_error(int result, const char *msg)
{
	if(result == -1){
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

ssize_t write_data_to_socket(int sockfd, const void *buf, size_t len, int flags,
		const struct sockaddr *dest_addr, socklen_t addrlen)
{
	ssize_t bytes_written = sendto(sockfd, buf, len, flags, dest_addr, addrlen);

	check_error(bytes_written, "writing to socket");

	return bytes_written;
}


ssize_t read_data_from_socket(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
	ssize_t bytes_read = recvfrom(sockfd, buf, len, flags, src_addr, addrlen);

	check_error(bytes_read, "reading socket");

	return bytes_read;
}
