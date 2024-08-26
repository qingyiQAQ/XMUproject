#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(lib,"Ws2_32.lib" )
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock.h>
#define SIZE 1024

char ip[] = "127.0.0.1";
int port = 8080;
void send_file(FILE* fp, int sockfd) {
    int n;
    char data[SIZE] = { 0 };

    while (fgets(data, SIZE, fp) != NULL) {
        if (send(sockfd, data, sizeof(data), 0) == -1) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        // bzero(data, SIZE);
        ZeroMemory(data, SIZE);
    }
}

void start()
{
    WORD version(0);
    WSADATA wsadata;
    int socket_return(0);
    version = MAKEWORD(2, 0);
    socket_return = WSAStartup(version, &wsadata);//开始对套接字库的使用。
    if (socket_return != 0)
        exit(0);
    //这些不能少，如果少的话，就无法正确创建socket。
}

int main() {
    start();
    int e;
    int sockfd;
    struct sockaddr_in server_addr;
    FILE* fp;
    char filename[] = "send.txt";
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e == -1) {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Connected to Server.\n");

    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("[-]Error in reading file.");
        exit(1);
    }
    send_file(fp, sockfd);
    printf("[+]File data sent successfully.\n");
    printf("[+]Closing the connection.\n");
    closesocket(sockfd);
    char response[SIZE];
    int recv_size = recv(sockfd, response, sizeof(response), 0);
    if (recv_size == -1) {
        printf("[-]Server %s:%d lost connection.\n", ip, port);
    }
    else {
        printf("[+]Closing the connection.\n");
    }
    return 0;
}
