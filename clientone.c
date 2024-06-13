// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT 1024
#define PORT2 1025
#define MAXLINE 1024 

// Driver code 
int main() { 
	int sockfd; 
	char buffer[MAXLINE]; 
	char *hello = "From Server"; 
	struct sockaddr_in	 servaddr; 

	// Creating socket file descriptor 
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
    if(fork()==0){
	// Filling server information 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	connect (sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)); 
	int n, len; 
	
	send(sockfd, (const char *)hello, strlen(hello),0); 
	//printf("Hello message sent.\n"); 
		
	n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
	buffer[n] = '\0'; 
	printf("Server with port %d: %s\n",PORT, buffer); 
	
	
	close(sockfd); 
    }
    else
    {
    servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	
	connect (sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr)); 
	int n, len; 
	
	send(sockfd, (const char *)hello, strlen(hello),0); 
	//printf("Hello message sent.\n"); 
		
	n = recv(sockfd, (char *)buffer, MAXLINE, 0); 
	buffer[n] = '\0'; 
	printf("Server with port %d: %s\n",PORT2, buffer); 
	
	
	close(sockfd); 
    }
	return 0; 
} 
