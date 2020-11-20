#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#define PORT 8080

int main (){
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char msg[1024]; 
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
    int count = 0;
    while(true){
    	std::cout << "To send a message first write it and then press enter...\n";
	std::cin >> msg;
	if(msg[0]== '.') break;
	std::cout << "\n Message Sent";
    	send(sock, msg, strlen(msg),0);
    	valread = read(sock, buffer,1024);
    	printf("%s\n", buffer);
	memset(msg, 0, 1024);
	memset(buffer, 0, 1024);
    }
    return 0;

}
