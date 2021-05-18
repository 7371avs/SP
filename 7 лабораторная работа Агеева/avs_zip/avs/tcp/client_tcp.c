#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUF_SIZE 1024

int main(void) {

    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);

    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addr_serv;
    memset(&addr_serv, 0, sizeof(addr_serv));

    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(1234);
    inet_pton(AF_INET, "127.0.0.1", &addr_serv.sin_addr);

    connect(sock, (SOCKADDR*) &addr_serv, sizeof(addr_serv));

    char message[BUF_SIZE];
    char exit;
    do {
        printf("Enter Message : ");
        fgets(message, BUF_SIZE, stdin);
        send(sock, message, BUF_SIZE, 0);
        recv(sock, message, BUF_SIZE, 0);
        printf("Message from server: %s\n", message);
        printf("1 - Exit  2 - Continue :");
        scanf("%c", &exit);
        char c;
        do {
            c = getchar();
        } while (c != EOF && c != '\n');

    } while (exit != '1');

    closesocket(sock);

    return 0;
}
