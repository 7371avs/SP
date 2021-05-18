#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 1024

void error(const char *msg) {
	perror(msg);
	exit(1);
}

int main(int argc, char *argv[]) {
	int sock_serv;
	socklen_t client_len;
	char buffer[BUF_SIZE];
	int port = 1234;
	if (argc == 2) {
		port = atoi(argv[1]);
	}

	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	sock_serv = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_serv < 0) {
		error("ERROR opening socket");
	}
	memset(&serv_addr, 0, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
	
	if (bind(sock_serv, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		error("ERROR on binding");
	}

	client_len = sizeof(client_addr);

	printf("%s\n", "The server works, waits for connecting!" );
	int n;
	while (1) {
		n = recvfrom(sock_serv, buffer, BUF_SIZE, 0,(struct sockaddr *)&client_addr, &client_len);
		if (n < 0) error("recvfrom");
		n = sendto(sock_serv, buffer, BUF_SIZE, 0,(struct sockaddr *)&client_addr, client_len);
		if (n < 0) error("sendto");
		printf("%s\n","Message sent" );
	}
	return 0;
}