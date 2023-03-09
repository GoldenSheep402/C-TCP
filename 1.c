#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <server_ip>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *server_ip = argv[1];

    // create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // get server IP address
    struct hostent *server = gethostbyname(server_ip);
    if (server == NULL)
    {
        fprintf(stderr, "Error: no such host: %s\n", server_ip);
        exit(EXIT_FAILURE);
    }

    // set server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);
    server_addr.sin_port = htons(SERVER_PORT);

    // connect to server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // send message to server
    char buffer[BUFFER_SIZE];
    printf("Enter message: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // remove newline character
    int n = send(client_socket, buffer, strlen(buffer), 0);
    if (n < 0)
    {
        perror("send");
        exit(EXIT_FAILURE);
    }

    // receive message from server
    memset(buffer, 0, BUFFER_SIZE);
    n = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (n < 0)
    {
        perror("recv");
        exit(EXIT_FAILURE);
    }

    printf("Server message: %s\n", buffer);

    close(client_socket);

    return 0;
}
