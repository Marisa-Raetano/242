#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define PORT 8080 
#define DOMAIN AF_INET6







int main(int argc, char const *argv[]) 
{

  struct addrinfo* address = NULL;
  getaddrinfo("localhost", PORT, NULL, &address);


  int sock;
  for(struct addrinfo* sd = addr; sd != NULL; sd = sd->ai_next)
  {
    sock = socket(sd->ai_family, sd->ai_socktype, sd->ai_protocol);

    if(sock == -1)
      continue;

    if(connect(sock, sd->ai_addr, sd->ai_addrlen) < 0)
      close(sock);

    else
      break;

  }

  freeaddrinfor(address);
  write(sock, argv[1], strlen(argv[1]));
  return 0;

}



