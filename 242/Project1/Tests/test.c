#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
//#include <sys\stat.h>
#define vfork fork

int main(int argc, char *argv[]){

  int input;
  int num;
  FILE *file;
  char string[10];

  const char *myarg = NULL;
  char* partialFilename = argv[1];
//  char *filename = strcpy(partialFilename, ".in");
  char* fileName, c;  
  //char *fileIN = strcat(partialFilename, ".in");
  //char *fileOUT = strcat(partialFilename, ".out");

  int fd = open("fileName", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
  file = fopen("test.in", "w+");
  myarg = argv[1];
  //  FILE *acutalINFILE = fopen("test.in", "w");
  //  FILE *actualOUTFILE = fopen("test.in", "w");

  //  strcpy(string, fileName );

  if(fd == -1)
  {  
    fprintf(stderr, "Couldn't open");
    exit(1);
  }


//c = fgetc(file);
char buf[20] = "";
while(argc != 2)
{
  scanf("%s\n", &string );
  //  if(strcpy(string, fileName)){
  scanf("%d\n", &input);
  num = input + input;
  sleep(1);
  printf("%d\n",num);
}

if(file == NULL)
{
  printf("Cant open file \n");
  exit(0);
}

close(fd);
//fclose(file);

  }





