#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX = 10;
int* stack[10];
int topStack = -1;

int stackEmpty(){
  if(topStack == -1){
    //    printf("stack is empty\n");
    return 1;
  }
  else{

    //  printf("stack isn't empty\n");
    return 0;
  }
}

int stackFull(){
  if(topStack == MAX){
    printf("stack is full\n");
    return 1;
  }
  else{ 
    printf("stack isn't full\n");
    return 0;
  }
}

int* pushStack(int value){

  int* retval;
  retval =(int*)malloc(value * sizeof(int*));
  for(int i = 0; i < 10; ++i)
    if(!stackFull())
    {
      topStack = topStack + 1;
      stack[topStack] = value;
      retval[i] = 0;
    }
    else
    {
      printf("Stack has reached maxsize\n");
    }

  return *retval;


}
int popStack()
{
  int *value;
  if(!stackEmpty())
  {
    value = stack[topStack];
    topStack = topStack - 1;
    return value;
  }
  else
  {
    return 0;
    //    printf("Stack can't be pop, its empty\n");
  }
  free(value);
}

int main()
{
  char str1[5] = "push";
  char str2[4] = "pop";
  char str3[4] = "end";
  int number;
  char *str4;
  printf("Please enter in what you want to do and the int\n");
  scanf("%5s &str4, %d &number");

  while(!stackFull())
  {
    if(strcmp(str1, str4)==0)
    {
      int *value = pushStack(number);
      printf("%d\n", number);
    }
    if(strcmp(str2, str4)==0)
    {
      int value = popStack(number);

      popStack(number);
      printf("%d\n", number);
    }
    if(strcmp(str3, str4)==0)
      break;

    else
      printf("Incorrect word\n");
  }

  return 0;
}












