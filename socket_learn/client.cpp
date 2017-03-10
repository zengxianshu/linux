#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024
#define HTONS_VALUE 6036

int main(){
    
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(HTONS_VALUE);  //端口
    
    printf("连接服务器\n");

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];

    char break_while[BUFFER_SIZE];
    
    while (1)
    {
        //创建套接字
        int sock_cli = socket(AF_INET, SOCK_STREAM, 0);
        if (connect(sock_cli, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0 ){
         perror("connect");
         exit(1);
        }
        printf("input a string:\n");
        gets(sendbuf);
        send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
        printf("客户端发送数据%s\n",sendbuf);
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
        printf("客户端接收数据%s\n",recvbuf);
        // fputs(recvbuf, stdout);
 
        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
        close(sock_cli);
    }

    //关闭套接字
    printf("客户端关闭\n");

    return 0;
}