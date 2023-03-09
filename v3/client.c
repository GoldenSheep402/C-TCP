#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int clientSocket;
    struct sockaddr_in serverAddr;

    char *serverHost = argv[1];
    unsigned short serverPort = atoi(argv[2]);

    char buffer[128];
    memset(buffer, 0, sizeof(buffer));

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverHost, &serverAddr.sin_addr);

    connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    while (1)
    {
        printf("Please enter your message: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(clientSocket, buffer, strlen(buffer));
        memset(buffer, 0, sizeof(buffer));
        read(clientSocket, buffer, sizeof(buffer));
        printf("Server response: %s\n", buffer);
        memset(buffer, 0, sizeof(buffer));
    }
    close(clientSocket);

    return 0;
}
