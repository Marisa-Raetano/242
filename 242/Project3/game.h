#ifndef GAME_H_
#define GAME_H_
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

int err;
int sock;

uint16_t gameID;
uint16_t playerID;
uint16_t oppID;
uint8_t response;
uint8_t placeMove[2];
char hello[5] = " ";

char gameBoard[6][6];
int row;
int column;

uint8_t turn;
int move[5] = {0, 32, 33, 34, 35};
char answer;
int movesMade = 0;


char DrawBoard(char gameBoard[6][6]);
void initializeBoard(char gameBoard[6][6]);
void playMove();
void handleResponse(uint8_t response);


char drawBoard(char gameboard[6][6])
{

  for( row = 0; row < 5; row++)
    for(column = 0; column < 5; column++)
      gameboard[row][column];

  for ( row = 0 ; row < 6 ; row++ )
  {
    for ( column = 0 ; column < 6; column++)
    {
      printf("%c", gameboard[row][column]);

    }
    printf("\n\n");
  }
}

void initializeBoard(char gameBoard[6][6])
{

  char marker = '*';
  char mark = '|';
  char dash = '-';

  for(row = 0; row < 6; row++)
  {
    for (column = 0; column < 6; column++)
    {
      gameBoard[0][0] = mark;
      gameBoard[1][0] = mark;
      gameBoard[2][0] = mark;
      gameBoard[3][0] = mark;
      gameBoard[4][0] = mark;
      gameBoard[5][0] = mark;
      gameBoard[0][1] = dash;
      gameBoard[0][2] = dash;
      gameBoard[0][3] = dash;
      gameBoard[0][4] = dash;
      gameBoard[0][5] = dash;
      gameBoard[row][column] = marker;

    }
    printf("\n");
    //printf('1', gameBoard[1][0]);
  }
}

void playMove()
{
  int movesMade = 0;
  char answer;
  scanf("%s", &answer);

  if(strcmp(&answer, "whose") == 0){
    printf("It is %d turn\n", turn);
  }
  else if(strcmp(&answer, "board") == 0){
    drawBoard(gameBoard);
  }

  else if(strcmp(&answer, "place") == 0){
    if(turn == 16 || turn == 17);
    scanf("%d %d", &row, &column);
    placeMove[0] = row;
    placeMove[1] = column;
    write(sock, &placeMove,2);
    read(sock, &response, 1);
    movesMade++;

  }

  else if(strcmp(&answer, "stats") == 0){
    printf("Game ID is: %d\n", gameID);
    printf("Players ID is: %d\n", playerID);
    printf("Opponents ID is: %d\n", oppID);
    //	printf("Moves made is : %d\n", &movesMade);
  }
}

void handleResponse(uint8_t response)
{
    if (response == 0)  //Bad move, player needs to re-input!
    {
      printf("%i Invalid move, try again\n", response);
      playMove();
    }

    if (response == 33) //Player input was okay and submitted, now wait for other client to play their move.
    {
      printf("%i Move is ok, await opponent’s next move\n", response);
      read(sock, &response, 1);
   
    }

    if (response == 32) //"Go-ahead" for us to send our next move.
    {
      //Update game board here?
      printf("%i Send next move\n", response);
      playMove();

    }

    if (response == 34) //Self-explanatory
    {
      printf("%i Game is over\n", response);
      close(sock);
      exit(0);
    }

    if (response == 35) //Also self-explanatory
    {
      printf("Opponent has terminated the game\n", response);
      close(sock);
      exit(0);
    }
}
#endif



