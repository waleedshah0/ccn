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

// Function to swap even and odd indexed characters
void swap_even_odd_indexes(char *str) {
    int len = strlen(str);
    for (int i = 0; i < len - 1; i += 2) {
        char temp = str[i];
        str[i] = str[i + 1];
        str[i + 1] = temp;
    }
}

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

        printf("Client : %s\n", buffer);

        // Swap even and odd indexed characters
        swap_even_odd_indexes(buffer);

        printf("Modified string : %s\n", buffer);

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *) &cliaddr, len); 
        printf("Modified string sent.\n"); 
    }

    close(sockfd);
    return 0; 
} 
