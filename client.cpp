#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>
#define PORT 8080

int main (){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char const *hello = "hello from client";
    char buffer[1024] = {0};
    if((sock = socket(AF_INET, SOCK_STREAM, 0 ))<0){
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0){
        printf("\nConnection Failed \n");
        return -1;
    }

    if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0){
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, hello, strlen(hello),0);
    printf("hello message sent\n");
    valread =read(sock, buffer,1024);
    printf("%s\n", buffer);
    return 0;

}
