/* ************************************************************************
 * Created by    : Rahul Kumar Nonia
 * File name     : client.c
 * Created on    : Thursday 03 September 2020 09:18:05 PM IST
 * Last modified : Saturday 12 September 2020 09:53:54 PM IST
 * Description   : 
 * ***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/types.h>

#define SOCKET_NAME "/tmp/simple_socket"
#define SIZE 100

void err_exit(int result, const char *msg)
{
	if (result == -1){
		perror(msg);
		exit(EXIT_FAILURE);
	}
}

int main()
{
	struct sockaddr_un addr;
	int data_socket, i, ret;
	char  buff[SIZE], data[SIZE];
	
	data_socket = socket(AF_UNIX, SOCK_STREAM, 0);
	err_exit(data_socket, "creating Socket");
	
	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path, SOCKET_NAME, sizeof(SOCKET_NAME));

	ret = connect(data_socket, (const struct sockaddr*) &addr,  sizeof(addr));
	err_exit(ret, "connect");

	do{
		printf("Enter the integer to be sent: ");
		scanf("%s", data);
		ret = write(data_socket, data, strlen(data));
		err_exit(ret, "writing to socket");
		printf("number of bytes sent: %d\t data sent: %d\n", ret, atoi(data));

	}while(atoi(data));
	

	memset(buff, 0, SIZE);
	ret = read(data_socket, buff, SIZE);
	err_exit(ret, "read");

	printf("Read from server: %s\n", buff);
	close(data_socket);

	return 0;
}
