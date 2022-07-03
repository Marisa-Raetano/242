#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<sys/wait.h>


int main ( int argc, char *argv[] )
{
  FILE *file;
  int ffd[2];
  char buff[20];
  const char *myarg = NULL;
  char filename[100], c;
  memset (buff, 0, sizeof(buff));


  //Create the child process

  pid_t child_pid = fork();
  assert(child_pid >= 0);
  if(child_pid == 0)
  {
    //Child will close write, then read
    close(ffd[1]);
    ssize_t bytes_read = read(ffd[0], buff, 10);
    if(bytes_read <= 0)
      exit(0);

    printf("Child got: '%s'\n", buff);
    exit(0);

  }
  //test to ensure you have a partial filename
  if(argc!=2)
  {printf("please enter a partial filename");
    exit(1);}


  myarg = argv[1];

  char temp[strlen(myarg) + 1];
  strcpy(filename, myarg);

  printf("filename to open %s \n", filename);

  // count characters of the filename
  printf("filename length is: %d \n", strlen(myarg));


  // Open file 
  file = fopen(filename, "r"); 
  if (file == NULL) 
  { 
    printf("Cannot open file \n"); 
    exit(0); 
  } 

  // Read contents from file 
  c = fgetc(file); 
  while (c != EOF) 
  { 
    printf ("%c", c); 
    c = fgetc(file); 
  } 

  fclose(file); 
  return 0; 
}
