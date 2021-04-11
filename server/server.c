// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#define PORT 1170
#define MAP_W 220
#define MAP_H 110
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

void send_message(char *message, int new_socket){
	send(new_socket , message , strlen(message) , 0 );
}
void send_message(int message[16][32], int new_socket){
	int size = 32 * 16;
	int m_encode2[size];
	for(int y = 0;y < 16;++y){
		for(int x = 0;x < 32;++x){
			m_encode2[(y * 32) + x] = message[y][x];
			std::cout << message[y][x];
		}	
		printf("\n");
	}
	send(new_socket , m_encode2 , 5120 , 0 );
}
int read_message(int new_socket, char buffer[1024]){
	return(read( new_socket , buffer, 1024));
}
int main(int argc, char const *argv[])
{
	int map[110][220] = {
		{1,0,0,0,2,2,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,1},
		{2,0,0,0,0,0,0,0,0,2},
		{3,0,0,0,0,0,0,0,0,3},
		{0,0,0,3,0,0,3,0,0,0},
		{0,0,0,3,0,0,3,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{1,0,0,0,2,2,0,0,0,1}
	};
	int server_fd, new_socket, valread;
	struct sockaddr_in address;
	int opt = 1;
	int addrlen = sizeof(address);
	char buffer[1024] = {0};
	char *hello = "Hello from server";
	
	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	// Forcefully attaching socket to the port 8080
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
												&opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons( PORT );
	
	// Forcefully attaching socket to the port 8080
	if (bind(server_fd, (struct sockaddr *)&address,
								sizeof(address))<0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	//while(true){
	for(int i = 0; i < 10; ++i){
		if (listen(server_fd, 3) < 0)
		{
			perror("listen");
			exit(EXIT_FAILURE);
		}
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
					(socklen_t*)&addrlen))<0)
		{
			perror("accept");
			exit(EXIT_FAILURE);
		}
		valread = read_message( new_socket , buffer);
		
		const char* string_read = buffer;
		printf("Message: ");
		printf( string_read );
		if(char_cmp(string_read,"!r map")){
			char temp[] = {string_read[6],string_read[7],string_read[8]};
			int startx = atoi(temp);
			char temp2[] = {string_read[9],string_read[10],string_read[11]};
			int starty = atoi(temp2);
			std::cout << startx;
			std::cout << starty;
			int send_map[16][32];
			for(int y = 0;y < 16;++y){
				for(int x = 0;x < 32;++x){
					send_map[y][x] = map[y + starty][x + startx];
				}	
			}
			send_message(send_map,new_socket);
			printf("map data sent\n");
		}
		else{
			send_message("Hello",new_socket);
			printf("Hello message sent\n");
		}
	}
	close(server_fd);
	return 0;
}
