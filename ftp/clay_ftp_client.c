// Client side implementation of UDP client-server model 
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

void cj_ftp(int sockfd, char *hello, struct sockaddr_in servaddr, char *buffer) {
  int n, len, bytes_recv; 
  void *buf[MAX_RW];

  sendto(sockfd, (char*)buffer, 0, MSG_WAITALL, ( struct sockaddr*) &servaddr, sizeof(servaddr));

  // Get file descriptor for where we are copying the incoming data
  buffer = "test1.copy";
  int fd = open(buffer, O_WRONLY | O_CREAT, 0666);

  // Receive bytes from server
  bytes_recv = MAX_RW;
  while( (bytes_recv >= 1024) && (bytes_recv = recvfrom(sockfd, buf, MAX_RW, MSG_WAITALL, (struct sockaddr *) &servaddr, &len)) > 0 ) {
    write(fd, buf, bytes_recv);
  } 
}

// Driver code 
int main() { 
  int sockfd; 
  char buffer[MAXLINE]; 
  char *hello = "Hello from client"; 
  struct sockaddr_in servaddr; 

  // Creating socket file descriptor 
  if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
    perror("socket creation failed"); 
    exit(EXIT_FAILURE); 
  } 

  memset(&servaddr, 0, sizeof(servaddr)); 

  // Filling server information 
  servaddr.sin_family = AF_INET; 
  servaddr.sin_port = htons(PORT); 
  servaddr.sin_addr.s_addr = INADDR_ANY; 

  // Copy the data over to a new file here
  cj_ftp(sockfd, hello, servaddr, buffer);

  close(sockfd); 
  return 0; 
} 

