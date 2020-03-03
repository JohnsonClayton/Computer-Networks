// Server side implementation of UDP client-server model 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <fcntl.h>

#define PORT	 8080 
#define MAXLINE 1024 

const int MAX_RW = 1024;

void cj_ftp(int sockfd, char *hello, struct sockaddr_in cliaddr, char *buffer) {
  int len, n; 
  void *buf[MAX_RW];

  len = sizeof(cliaddr);  //len is value/resuslt 

  n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, &len); 
  //buffer[n] = '\0'; 

  // Get file descriptor for the file to send 
  buffer = "test1";
  int fd = open(buffer, O_RDONLY);
  
  int size_read;

  // Send bytes to client in MAX_RW chunks
  while( (size_read = read(fd, buf, MAX_RW)) > 0 ) {
    sendto(sockfd, (const void *)buf, size_read, MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
  }
  //printf("Client : %s\n", buffer); 
  //printf("Hello message sent.\n");  
}

// Driver code 
int main() { 
  int sockfd; 
  char buffer[MAXLINE]; 
  char *hello = "Hello from server"; 
  struct sockaddr_in servaddr, cliaddr; 

  // Creating socket file descriptor 
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
    perror("socket creation failed"); 
    exit(EXIT_FAILURE); 
  } 

  memset(&servaddr, 0, sizeof(servaddr)); 
  memset(&cliaddr, 0, sizeof(cliaddr)); 

  // Filling server information 
  servaddr.sin_family = AF_INET; // IPv4 
  servaddr.sin_addr.s_addr = INADDR_ANY; 
  servaddr.sin_port = htons(PORT); 

  // Bind the socket with the server address 
  if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) 
  { 
    perror("bind failed"); 
    exit(EXIT_FAILURE); 
  } 

  cj_ftp(sockfd, hello, cliaddr, buffer);

  return 0; 
} 

