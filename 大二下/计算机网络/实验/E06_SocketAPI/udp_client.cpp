#define _CRT_SECURE_NO_DEPRECATE
#pragma comment(lib,"Ws2_32.lib" )
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<winsock.h>
#define SIZE 1024

void send_file_data(FILE* fp, int sockfd, struct sockaddr_in addr)
{
    int n;
    char buffer[SIZE];

    // Sending the data
    while (fgets(buffer, SIZE, fp) != NULL)
    {
        printf("[SENDING] Data: %s", buffer);

        n = sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));
        if (n == -1)
        {
            perror("[ERROR] sending data to the server.");
            exit(1);
        }
        //linux
        //bzero(buffer, SIZE);
        ZeroMemory(buffer, SIZE);
    }

    // Sending the 'END'
    strcpy(buffer, "END");
    sendto(sockfd, buffer, SIZE, 0, (struct sockaddr*)&addr, sizeof(addr));

    fclose(fp);
}


void start()
{
    WORD version(0);
    WSADATA wsadata;
    int socket_return(0);
    version = MAKEWORD(2, 0);
    socket_return = WSAStartup(version, &wsadata);//开始对套接字库的使用。
    if (socket_return != 0)
    {
        exit(0);
    }//这些不能少，如果少的话，就无法正确创建socket。
}
int main(void)
{
    start();
    // Defining the IP and Port
    char ip[] = "127.0.0.1";
    const int port = 8080;

    // Defining variables
    int server_sockfd;
    struct sockaddr_in server_addr;
    char filename[] = "send.txt";
    FILE* fp = fopen(filename, "r");

    // Creating a UDP socket
    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_sockfd < 0)
    {
        perror("[ERROR] socket error");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Reading the text file
    if (fp == NULL)
    {
        perror("[ERROR] reading the file");
        exit(1);
    }

    // Sending the file data to the server
    send_file_data(fp, server_sockfd, server_addr);

    printf("[SUCCESS] Data transfer complete.\n");
    printf("[CLOSING] Disconnecting from the server.\n");

    closesocket(server_sockfd);

    return 0;
}
