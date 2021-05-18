#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUF_SIZE 1024

int main(void)
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);

    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    struct hostent *hp;

    SOCKADDR_IN addr_serv, my_addr, from;
    memset(&addr_serv, 0, sizeof(addr_serv));
    int from_len, length = sizeof(addr_serv);

    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(1234);
    inet_pton(AF_INET, "127.0.0.1", &addr_serv.sin_addr);

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(1200);
    inet_pton(AF_INET, "127.0.0.1", &my_addr.sin_addr);

    if (bind(sock, (SOCKADDR*) &my_addr, sizeof(my_addr)) == 0)
        printf("Binded Correctly\n");

    else
        printf("Unable to bind\n"); 

    char message[BUF_SIZE];
    char exit;
    do {
        printf("Enter Message : ");
        fgets(message, BUF_SIZE, stdin);
        sendto(sock, message, BUF_SIZE, 0,(SOCKADDR*)&addr_serv, length);
        recvfrom(sock, message, BUF_SIZE, 0,(SOCKADDR*)&from, &from_len);
        printf("Message from server: %s\n", message);
        printf("1 - Exit  2 - Continue :");
        scanf("%c", &exit);
        char c;
        do {
            c = getchar();
        } while (c != EOF && c != '\n');

    } while (exit != '1');

    closesocket(sock );

    return 0;
}
