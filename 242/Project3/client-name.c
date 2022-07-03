#include <netdb.h>
#include <string.h>

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 


// note this is a _string_ with the port number now
#define PORT "8080"

int main(int argc, char const *argv[]) 
{ 
  struct addrinfo* addr = NULL;
  getaddrinfo("localhost", PORT, NULL, &addr);

  int sock;
  for (struct addrinfo* rp = addr; rp != NULL; rp = rp->ai_next)
  {   
    sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sock == -1) 
      continue;

    if (connect(sock, rp->ai_addr, rp->ai_addrlen) < 0)
      close (sock);
    else
      break;
  }   
  freeaddrinfo(addr);

  write(sock, argv[1], strlen(argv[1]));
  return 0;  
} 
