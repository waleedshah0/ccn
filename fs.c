// Server side implementation of UDP client-server model 
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
#define SURNAME  " Smith"

// Driver code 
int main() { 
    int sockfd; 
    struct sockaddr_in servaddr, cliaddr; 

    // Creating socket file descriptor 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 

    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT); 

    // Bind the socket with the server address 
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
        perror("bind failed"); 
        close(sockfd);
        exit(EXIT_FAILURE); 
    } 

    while (1) {
        char buffer[MAXLINE];
        socklen_t len = sizeof(cliaddr); 
        int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *) &cliaddr, &len); 
        if (n < 0) {
            perror("recvfrom failed");
            continue;
        }
        buffer[n] = '\0';

        printf("Received name: %s\n", buffer);

        // Append surname
        strcat(buffer, SURNAME);

        printf("Modified name: %s\n", buffer);

        // Send back the modified name
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &cliaddr, len); 
        printf("Modified name sent.\n"); 
    }

    close(sockfd);
    return 0; 
} 
