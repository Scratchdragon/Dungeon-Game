// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#define PORT 1170
bool char_cmp(const char *string1,char string2[]){
	bool temp = true;
	for(int i = 0;i < sizeof(string2);++i){
		temp = string1[i] == string2[i];
		if(!temp){
			return temp;
		}
	}
	return temp;
}
int * server_request(char request[1024],int sock){
	int buffer[512];
	send(sock , request , strlen(request) , 0 );
	printf("%s", request);
	printf(" request sent\n");
	int valread = read( sock , buffer, 5120);
	if(char_cmp(request,"!r map")){
		for(int y = 0;y < 16;++y){
			for(int x = 0;x < 32;++x){
				std::cout << buffer[(y * 32) + x];
				printf(" ");
			}
			printf("\n");
		}
	}
	return buffer;
}
int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
	char hello[1024] = "!r map000000";
	int buffer[512];
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}
	
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
	while(true){
		int buffer[512];
		const char * request = "!r map000000";
		send(sock , request , strlen(request) , 0 );
		printf("%s", request);
		printf(" request sent\n");
		int valread = read( sock , buffer, 5120);
		if(char_cmp(request,"!r map")){
			for(int y = 0;y < 16;++y){
				for(int x = 0;x < 32;++x){
					std::cout << buffer[(y * 32) + x];
					printf(" ");
				}	
				printf("\n");
			}
		}
	}
	return 0;
}
