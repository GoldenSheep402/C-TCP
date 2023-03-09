#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define PORT 8888

int main()
{
    // create socket
    // int socket(int domain, int type, int protocol);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    /*
    struct sockaddr_in {
        short sin_family;          // 协议族
        unsigned short sin_port;   // 端口号
        struct in_addr sin_addr;   // IP地址
        char sin_zero[8];          // 填充
    }; */
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // bind with local address
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // start to listen for connection
    listen(server_fd, SOMAXCONN);

    // accpect link
    struct sockaddr_in client_addr; // cilent
    socklen_t client_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);

    // buf
    char buffer[1024];
    int n = recv(client_fd, buffer, sizeof(buffer), 0);
    send(client_fd, buffer, n, 0);

    close(client_fd);
}
