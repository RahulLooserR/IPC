/* ************************************************************************
 * Created by    : Rahul Kumar Nonia
 * File name     : server.c
 * Created on    : Saturday 29 August 2020 08:46:38 PM IST
 * Last modified : Thursday 03 September 2020 09:52:12 PM IST
 * Description   : 
 * 1. socket()
 * 2. bind ()
 * 3. listen ()
 * 4. accept ()
 * 5. recv/read()
 * 6. send/write()
 * ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <sys/types.h>

#define SOCKET_NAME "/tmp/simple_socket"


int main()
{
	int master_socket; // connection socket
	int data_socket, ret, result;
	char buff[100];
	int data;

	struct sockaddr_un name;
	/* struct sockaddr_un {
	 * 		sa_family_t sun_family;   // AF_UNIX
	 * 		char sun_path[100];       // pathname
	 * 		};
	 */

	// unlink existing scoket with same name
	unlink(SOCKET_NAME);

	/* 1. creating socket
	 * int socket(int domain, int type, int protocol);
	 */
	master_socket = socket(AF_UNIX, SOCK_STREAM, 0);

	if (master_socket == -1){
		perror("Creating master socket");
		exit(EXIT_FAILURE);
	}

	printf("Master Socket created\n");

	/* initializing */
	memset(&name, 0, sizeof(struct sockaddr_un));
	name.sun_family = AF_UNIX;
	strncpy(name.sun_path, SOCKET_NAME, sizeof(SOCKET_NAME));

	/* 2. bind */
	ret = bind(master_socket, (const struct sockaddr *)&name, sizeof(struct sockaddr_un));

	if (ret == -1){
		perror("Binding");
		exit(EXIT_FAILURE);
	}

	/*  listen() */
	ret = listen(master_socket, 10);

	if (ret == -1){
		perror("listen");
		exit(EXIT_FAILURE);
	}

	for(;;){
		printf("waiting for connection(accept)..\n");
		/* 3. accept() -> blocking system call */
		data_socket = accept(master_socket, NULL, NULL);
		if (data_socket == -1){
			perror("data_socket");
			exit(EXIT_FAILURE);
		}

		printf("Clietn connected..\n");

		result = 0;
		/* processing each clinet */
		for(;;){
			memset(buff, 0, 100);
			printf("waiting for data from client..\n");

			/* 4. read() */
			ret = read(data_socket, buff, 100);
			if (ret == -1){
				perror("read");
				exit(EXIT_FAILURE);
			}
			data = 0;
			printf("Data recieved in buffer: %s\n", buff);	
		//	memcpy((char *)&data, buff, strlen(buff)-1);
		//	printf("atoi value: %d\n", strlen(buff));
		//	printf("data recieved: %d\n", data);
		    data = atoi(buff);
			if(data == 0) break;
			result += data;

		}
		memset(buff, 0, 100);
		sprintf(buff, "Result = %d", result);
		printf("sending final result to the client\n");

		/* 5. write */
		ret = write(data_socket, buff, 100);
		if (ret == -1){
			perror("read");
			exit(EXIT_FAILURE);
		}

	}

	return 0;
}
