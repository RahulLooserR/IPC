#include "header.h"

int main()
{
	struct sockaddr_in server, client_info;
	int master_sock_fd;   // connection socket
	int comm_sock_fd;     // communication socket
	char buff[BUFFER_SIZE] = {0};
	int client_addrlen = sizeof(client_info);

	// creating master socket
	master_sock_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	check_error(master_sock_fd, "creating Socket");

	// initialize socket structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = PORT;

	// binding socket 
	check_error(bind(master_sock_fd, (const struct sockaddr*) &server, sizeof(server)), "bind");

	//listen
	check_error(listen(master_sock_fd, MAX_CLIENT), "listen");
	printf("waiting for client...\n");
	comm_sock_fd = accept(master_sock_fd, (struct sockaddr *)&client_info, &client_addrlen);
	check_error(comm_sock_fd, "accept");
	printf("Client connected\n");


	while(1){
		memset(buff, 0, BUFFER_SIZE);

		read_data_from_socket(comm_sock_fd, buff, BUFFER_SIZE, 0, (struct sockaddr *)&client_info, &client_addrlen);
		printf("recieved: %s", buff);
		write_data_to_socket(comm_sock_fd, buff, BUFFER_SIZE, 0 , (struct sockaddr *)&client_info, client_addrlen);
		if(strcmp("bye\n", buff) == 0){
			printf("disconnecting client\n");
			close(comm_sock_fd);
		}
	}


	return 0;
}
