#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define HTONS_VALUE 6036


int main(){
    
    /*
    int socket(int af, int type, int protocol);

    af 为地址族（Address Family），也就是 IP 地址类型，常用的有 AF_INET 和 AF_INET6

    type 为数据传输方式，常用的有 SOCK_STREAM 和 SOCK_DGRAM

    protocol 表示传输协议，常用的有 IPPROTO_TCP 和 IPPTOTO_UDP
    */

    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(HTONS_VALUE);  //端口

    // 设置套接字选项避免地址使用错误  
    int resuse = 1;  
    if(setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&resuse,sizeof(resuse))<0) {
        perror("setsockopt");
        exit(1);
    }

    ///bind，成功返回0，出错返回-1
    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        perror("bind");
        exit(1);
    }
    printf("服务器挂起\n");

    /*
    sock 为需要进入监听状态的套接字
    backlog 为请求队列的最大长度  如果设定 SOMAXCONN 则是由系统来决定队列长度 
    */
    //进入监听状态，等待用户发起请求 listen，成功返回0，出错返回-1
     if(listen(serv_sock,20) == -1)
     {
         perror("listen");
         exit(1);
     }


    while(1)
    {

        //接收客户端请求
        struct sockaddr_in clnt_addr;
        socklen_t clnt_addr_size = sizeof(clnt_addr);
        char buffer[BUFFER_SIZE];

        int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if(clnt_sock<0){
            perror("connect");
            exit(1);
        }

        memset(buffer,0,sizeof(buffer));
        int len = recv(clnt_sock, buffer, sizeof(buffer),0);
        printf("服务器接收数据%s\n",buffer);
        if(strcmp(buffer,"exit\n")==0)
         break;
        fputs(buffer, stdout);
        send(clnt_sock, buffer, len, 0);
        printf("服务器发送数据%s\n",buffer);
        //关闭套接字
        close(clnt_sock);
    }


    close(serv_sock);
    printf("关闭服务器\n");

    return 0;
}
