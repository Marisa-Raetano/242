#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
  int ffd[2];
  char buff[20];
  FILE *file;
  const char *myarg = NULL;
  char filename[100], c;
  int input;
  int num;
  char string[20];
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

//take in argv[1] which is the filename
  //need to count the characters of the filename so I know where to place the .in and .out

  myarg = argv[1];
  int fd = open("filename", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR     | S_IRGRP | S_IWGRP);
//open myarg which is filename 

  file = fopen("test.txt", "r+");

  //next want to be able to read the file
  fscanf(file, "%d", buff);
  printf("Reading from filename: %d\n", buff);

//test if to see if I can open the file

  if(fd == -1)
  {
    fprintf(stderr, "Can't open file \n");
    exit(0);
  }
//while the file is open read in each number and double it 

  while(argc!=2)
  {

    printf("Please enter a partial filename: ");
    scanf("%s\n", filename);
    strcpy(string, filename);
    printf("Please enter what you want to double: \n");
    scanf("%d\n", &input);
    num = input + input;
    printf("%d\n",num);
    if(string == "end")
      exit(1);
  }

  close(ffd[0]);

  strncpy(buff, "Welcome", sizeof(buff));
  printf("Parent is sending '%s'\n", buff);
  write(ffd[1], buff, sizeof(buff));
  wait(NULL);
  printf("Child plz print message\n");


  close(fd);
  fclose(file);




} 

