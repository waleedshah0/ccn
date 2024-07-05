// Client side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

#define PORT     8080 
#define MAXLINE  1024 

// Driver code 
int main() { 
    int sockfd; 
    char buffer[MAXLINE]; 
    struct sockaddr_in servaddr; 

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    memset(&servaddr, 0, sizeof(servaddr)); 

    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 

    socklen_t len = sizeof(servaddr);

    // Read the content from name.txt
    FILE *file = fopen("name.txt", "r");
    if (!file) {
        perror("fopen failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("fgets failed");
        fclose(file);
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    fclose(file);

    // Send the content of the file to the server
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &servaddr, len); 
    printf("File content sent to server: %s\n", buffer);

    // Receive the modified content from the server
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &servaddr, &len); 
    if (n < 0) {
        perror("recvfrom failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';

    printf("Server : %s\n", buffer);

    // Close the socket
    close(sockfd); 
    return 0; 
} 
