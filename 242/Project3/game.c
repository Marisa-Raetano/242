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
#include <stdio.h>
#include "game.h"
#define SIZE 6


int main(int argc, char const *argv[])
{

  const char *hostname = argv[1];
  const char *port = argv[2];
  gameID = strtol(argv[3], NULL, 10);

  /*
     while(argc < 3)
     if(argc != 3){
     printf("No gameID given : %d\n", argv[3]);
     continue;
     }
   */

  struct addrinfo hints, *res;

  //Socket Information
  memset(&hints, 0, sizeof(hints));
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_family = AF_INET;
  hints.ai_protocol = 0;

  //Error if no address info
  if((err = getaddrinfo(hostname, port, &hints, &res)) != 0)
  {
    printf("error");
    exit(1);
  }

  //Connect to socket and check all returns
  for(struct addrinfo* rp = res; rp != NULL; rp = rp->ai_next)
  {
    sock = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

    if(sock == -1)
      continue;


    if (connect(sock, rp->ai_addr, rp->ai_addrlen) < 0)
      close(sock);

    else
      break;
  }



  freeaddrinfo(res);

  initializeBoard(gameBoard);
  //Get info for the game

  read(sock, &playerID, 2);
  printf("Players ID is: %d\n", playerID);

  write(sock, &gameID, 2);
  printf("Game ID is: %d\n", gameID);

  read(sock, hello, 4);
  printf("Response message is %s\n", hello);

  read(sock, &gameID, 2);
  printf("Game ID is: %d\n", gameID);

  read(sock, &playerID, 2);
  printf("Players ID is: %d\n", playerID);

  read(sock, &oppID,2);
  printf("Opponents ID is: %d\n", oppID);

  read(sock, &turn, 1);
  printf("Your turn is: %d\n", turn);

  while(1){
    //Draw the board
   for(;turn;){
   playMove();
   handleResponse(response);
   {
    if(turn == 16 ){
      gameBoard[placeMove[0]][placeMove[1]] = 'x';
    }

    if (turn == 17)
    {
      gameBoard[placeMove[0]][placeMove[1]] = 'o';
    }

    drawBoard(gameBoard);
   }
   }
    exit(0);
  }


  return 0;
}


