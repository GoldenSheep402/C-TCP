#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1" // 服务器IP地址
#define SERVER_PORT             // 服务器端口号
#define BUF_SIZE 1024           // 缓冲区大小

int main()
{
    int sockfd;
    struct sockaddr_in serv_addr;
    char send_buf[BUF_SIZE];
    char recv_buf[BUF_SIZE];
    ssize_t num_bytes;

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构体
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
    serv_addr.sin_port = htons(SERVER_PORT);

    // 连接服务器
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // 发送数据
    while (1)
    {
        printf("Please enter a message: ");
        fgets(send_buf, BUF_SIZE, stdin);
        send_buf[strlen(send_buf) - 1] = '\0'; // 去除换行符

        if (strcmp(send_buf, "quit") == 0)
        {
            break;
        }

        if (send(sockfd, send_buf, strlen(send_buf), 0) == -1)
        {
            perror("send");
            exit(EXIT_FAILURE);
        }

        // 接收数据
        memset(recv_buf, 0, sizeof(recv_buf));
        num_bytes = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
        if (num_bytes == -1)
        {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        recv_buf[num_bytes] = '\0';

        printf("Server response: %s\n", recv_buf);
    }

    // 关闭套接字
    if (close(sockfd) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
