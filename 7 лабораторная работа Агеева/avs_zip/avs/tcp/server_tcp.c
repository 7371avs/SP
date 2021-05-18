#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 1024
#define QUEUE_SIZE 50
#define MAX_COUNT 1000

void error(const char *msg) {
	perror(msg);
	exit(1);
}

void *start_func(void *arg) {
	printf("%s\n","The connection is created!");
	char buffer[BUF_SIZE];
	while (1) {
		if (recv(*((int*)arg), buffer, BUF_SIZE, 0) <= 0) {
			printf("%s\n","The connection is disabled!");
			pthread_exit(NULL);
		}
		send(*((int*)arg), buffer, BUF_SIZE, 0);
	}
}

int main(int argc, char *argv[]) {

	int sock_serv;
	socklen_t client_len;
	int port = 1234;
	if (argc == 2) {
		port = atoi(argv[1]);
	}

	struct sockaddr_in serv_addr;
	struct sockaddr_in client_addr;
	int n;
	sock_serv = socket(AF_INET, SOCK_STREAM, 0);
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

	listen(sock_serv, QUEUE_SIZE);
	client_len = sizeof(client_addr);

	printf("%s\n", "The server works, waits for connecting!" );
	pthread_t pthread_arr[MAX_COUNT];
	int tmp_sock_client[MAX_COUNT];
	int i = 0;
	while(1) {
		if (i == MAX_COUNT) {
			break;
		}
		(tmp_sock_client[i]) = accept(sock_serv, NULL, NULL);
		pthread_create(&(pthread_arr[i]), NULL, start_func, (void *) &(tmp_sock_client[i]));
		i++;
	}
	
	for (int j = 0; j < i; j++) {
		close(tmp_sock_client[j]);
		pthread_join(pthread_arr[j], NULL);
	}

	close(sock_serv);
	return 0;
}
