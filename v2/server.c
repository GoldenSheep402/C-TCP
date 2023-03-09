#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <netdb.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    struct sockaddr_in sad; // to hold server IP
    struct sockaddr_in cad;

    int welcomeSocket, connectionSocket;

    struct hostent *ptrh; // poniter to host table entry

    // char Sentence[128];
    // char modifiedSentence[128];
    char clientSentence[128];
    char capitalizedSentence[128];

    // char *host = argv[1];
    unsigned short port = atoi(argv[1]);

    welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
    memset((char *)&sad, 0, sizeof(sad));
    sad.sin_family = AF_INET;
    sad.sin_port = htons(port); // translate to network byte order
    sad.sin_addr.s_addr = INADDR_ANY;
    sad.sin_port = htons((unsigned short)port);
    bind(welcomeSocket, (struct sockaddr *)&sad, sizeof(sad));
    // ptrh = gethostbyname(host);
    // memcpy(&sad.sin_addr, ptrh->h_addr_list[0], ptrh->h_length);
    // connect(client_socket, (struct sockaddr *)&sad, sizeof(sad));
    listen(welcomeSocket, 10);

    socklen_t alen = sizeof(cad);
    int n;
    while (1)
    {
        connectionSocket = accept(welcomeSocket, (struct sockaddr *)&cad, &alen);
        n = read(connectionSocket, clientSentence, sizeof(clientSentence));
        for (int i = 0; i < strlen(clientSentence); i++)
        {
            capitalizedSentence[i] = toupper(clientSentence[i]);
        }
        n = write(connectionSocket, capitalizedSentence, strlen(clientSentence) + 1);
        close(connectionSocket);
    }
}
