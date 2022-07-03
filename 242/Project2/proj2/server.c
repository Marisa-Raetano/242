#include <stdbool.h>
#include <assert.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#define MAX 80
#define DOMAIN AF_INET
#define BUFF_SIZE 1024
#define MAX_REQUEST 1024
#define _XOPEN_SOURCE 700


char webpage[]= "GET HTTP/1.1 200 OK\r\n"
"Content-Type: text/html; charset=UTF-8\r\n\r\n"
"<!DOCTYPE html>\r\n"
"<html><head><title>Hello</title>\r\n"
"<body><center><h1>hello world!</h1><br></center></body></html>\r\n";


void func(int sock)

{ 
  char buff[MAX];
  int n;

  for(;;) {
    bzero(buff, MAX);
    int res = read(sock, buff, sizeof(buff));
    if(res <= 0)
      break;
    printf("From Client: %s\t To Server: ", buff);
    bzero(buff, MAX);
    n = 0;
    while ((buff[n++] = getchar()) != '\n');

    write(sock, buff, sizeof(buff));
    if(strncmp("exit", buff, 4) == 0)
    { 
      printf("Server Exiting \n");
      break;
    }
  }

}



int main(int argc, char const *argv[])
{
  int sockfd;
  int sock;
  int fd;
  struct sockaddr_in address;
  char *message_format;
  char server_reply[1024];

  int port = strtol(argv[1], NULL, 10);

  FILE *sendFile = fopen("index.html", "w");
  sendFile = strtol(argv[2], NULL, 10);

  //Socket was created and verified
  
  sockfd = socket(DOMAIN, SOCK_STREAM, 0);
  if(sockfd == -1)
  { 
    printf("socket connection failed \n");
    exit(0);
  }
  else
    printf("Socket connection was successful \n");
  
  address.sin_family = DOMAIN;
  address.sin_port = htons(port); 
  address.sin_addr.s_addr = htonl(INADDR_ANY);

  char address_string[255];
  inet_ntop(address.sin_family, &address.sin_addr, &address_string, 255);


  int opt = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
  
//Bind the socket
  if(bind(sockfd,(struct sockaddr*)&address, sizeof(address)) != 0)
  {
    printf("couldnt open, socket failed\n");
    exit(1);

  }
  //Listen on the socket
  if((listen(sockfd, 10)) == -1)
  {
    printf("Listen has failed \n");
    exit(1);
  }

  int addrlen = sizeof(address);
  while(1)
  {
    int connection = accept(sockfd,(struct sockaddr*)&address, &addrlen);
    if(connection < 0)
    {
      printf("Server has failed to accept \n");

    }
    else
    {
      printf("Server has accepted the client %d \n", address.sin_addr.s_addr);
    }

      printf("connection is %d\n",connection);
      func(connection);
    }
    
//Close the socket
  close(sendFile);
  close(sockfd);

  //process response
  //printf("Response:\n%s\n", response);

  //return 0;  
}


