#define _CRT_SECURE_NO_DEPRECATE
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"Ws2_32.lib" )
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <WinSock2.h>
#include <Ws2tcpip.h>
#define SIZE 1024
struct sockaddr_in server_addr, new_addr;
char filename[] = "recv.txt";
//写入文件
void write_file(int sockfd) {
    int n;
    FILE* fp;
    char buffer[SIZE];
    fp = fopen(filename, "w");
    while (1) {
        n = recv(sockfd, buffer, SIZE, 0);
        if (n<=0)
        {
            if (n == 0) {
                // Connection closed normally
                break;
            }
            else if (errno == ECONNRESET) {
                // Connection reset by peer
                perror("Connection reset by peer");
                remove(filename); // Delete the partially received file
                return;
            }
            else {
                // Other errors
                printf("IP：%s 发来文件过程中失去连接。\n", inet_ntoa(new_addr.sin_addr));
                remove(filename); // Delete the partially received file
                return;
            }
            break;
        }
        fprintf(fp, "%s", buffer);
        ZeroMemory(buffer, SIZE);
    }
    printf("[+]Data written in the file successfully.\n");
    return;
}

//启动函数
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

int main()
{
    start();
    char ip[] = "127.0.0.1";
    int port = 8080;
    int e;
    int sockfd, new_sock;
    int addr_size;
    char buffer[SIZE];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        perror("[-]Invalid address/ Address not supported");
        exit(1);
    }

    e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e < 0) {
        perror("[-]Error in bind");
        exit(1);
    }
    printf("[+]Binding successfull.\n");

    if (listen(sockfd, 10) == 0) {
        printf("[+]Listening....\n");
    }
    else {
        perror("[-]Error in listening");
        exit(1);
    }

    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    if (new_sock < 0) {
        printf("IP：%s 发来文件过程中失去连接。\n", inet_ntoa(new_addr.sin_addr));
        remove(filename);
    }
    else {
        write_file(new_sock);
        
    }
    

    return 0;
}
