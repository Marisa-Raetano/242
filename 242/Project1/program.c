#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <sys/stat.h>

#define MAX_LENGTH 256

const char *get_filename_ext(const char *filename); //function prototype
int endsWith(char *start, char *end); //function prototype

int main(int argc, char* argv[])
{
  //Check to ensure that there are only 3 arguments
  if(argc < 3)
  {
    printf("Too few arguments\n");
    exit(1);
  }

  if(argc > 3)
  {
    printf("Too many arguments\n");
    exit(1);
  }

  const char *filepath = argv[1];

  //This is our current test directory
  char dirName[MAX_LENGTH] = "Tests";
  //Declare the variable that holds the directory name
  char fileName[MAX_LENGTH];
  //This is a variable to hold the user inputed partial filename
  char partial[MAX_LENGTH] = "./";
  //This is the variable that will hold the .in file
  char files[MAX_LENGTH];
  //Copy the first argument after program name into file name
  strcpy(fileName, argv[1]);
  if(strcmp(fileName, dirName) != 0)
  {
    printf("Error no directory found\n");
    exit(1);
  }

  //Copy the second argument after the program name in partial
  strcpy(partial, argv[2]);
  //take the user inputed file name and copy to files
  strcpy(files, fileName);

  //Fork 2 child process
  int child1 = fork();
  // int child2 = fork();

  if(child1 == 0)
  {
    DIR *dir;

    struct dirent *dp;
    int filesDIR = 0;
    dir = opendir("Tests");

    if(dir == NULL)
    {
      perror("Could not open\n");
      return(1);
    }

    //printf("%s\n", get_filename_ext("test1.in"));
    int in_count = 0;
    int expect_count = 0;
    char in_file[MAX_LENGTH];
    char expect_file[MAX_LENGTH];
    //Reads directory contents
    while((dp= readdir(dir)))
    {
      filesDIR++; //writes out file numbers to screen
      //char testing[MAX_LENGTH];
      //int fileNameLength = strlen(testing) - 3;
      //if(strncmp(testing + fileNameLength, ".in", 3) == 0)
      // execl(argv[1], argv[2], filesDIR, NULL);
      //printf("File %3d: %s\n", filesDIR, dp->d_name);

      printf("---------------------------------\n");
      if (endsWith (dp->d_name, ".in"))
      {
	in_count++;
	printf("---------------------------\n");
	printf(in_file, "\n");
      }
      if (endsWith (dp->d_name, ".expect"))
      {       
	expect_count++;
	printf("---------------------------\n");
	printf(expect_file, "\n");
      }

      //print all files
      printf("File %3d: Name %s: type %hhu: length %hu: \n", filesDIR, dp->d_name, dp->d_type, dp->d_reclen);

      if(endsWith(dp->d_name, ".in"))
      {
	//printf(".in filename found: %s\n",dp->d_name);
	strcpy(in_file, dp->d_name);
      }

      //in .expect file, print and copy into variable name expect_file
      if(endsWith(dp->d_name, ".expect"))
      {
	//printf(".expect matching filename found: %s\n",dp->d_name);
	strcpy(expect_file, dp->d_name);
      }
    }

    printf("child process read of directory has successfully completed\n");
    printf("---------------------------------\n");
    printf("Found %d .in files\n", in_count);
    printf("Found %d .expect files\n", expect_count);
    int sinlen = strlen(in_file)-3;
    int sexlen = strlen(expect_file)-7;  
    // compare both files for match
    if(sinlen == sexlen)
    {
      printf("Found matching files: %s <-->  %s\n", in_file, expect_file);
    }

    printf("---------------------------------\n");
    // does the original user input match the .in file?

    printf("original user partial input '%s' to be tested\n", partial);
    printf("string length of in_file =  %lu\n", strlen(in_file)-3);
    printf("string length of partial =  %lu\n", strlen(partial));

    printf("---------------------------------\n");
    if(sinlen == strlen(partial))
    {
      printf("User input matches .in and expect files %s %s %s\n", partial, in_file, expect_file);

      if(sinlen != sexlen)
      {
	printf("---------------------------\n");
	printf("No matching files\n");
      }

      int child2 = fork(); 
      printf("enter the filename \n");
      scanf("%s",&fileName);
  
      FILE *fd = fopen("fileName","w+");
      if(argv[0] == fileName)
      {
	FILE *fd = fopen("fileName","w+");
      }
      /*
	 char ch;
	 FILE *fptr = fopen(argv[1], "r");
	 if(argv[1] == partial)
	 {
	 printf("%s\n", dp->d_name);
	 ch = fgetc(fptr);
	 while(ch != EOF)
	 {
	 printf("%c", ch);
	 ch = fgetc(fptr);
	 }
	 fclose(fptr);
	 execl(argv[1], argv[1], fileName, NULL);
	 }
       */
    }
    closedir(dir);
  }

  else
  {
    char pid_Child[6] = "false";
    execl(argv[1], pid_Child, NULL);
    wait(NULL);
    printf("Program has completed successfully\n");
    printf("---------------------------------\n");
  }
  /*
     char *shared = mmap ( NULL, MAX_LENGTH, PROT_READ | PROT_WRITE,
     MAP_SHARED, mapped_fd, 0 );
     if (shared == MAP_FAILED)
     error();

   */

  wait(NULL);
  return(0);
}

int endsWith(char *start, char *end)
{
  size_t startLength = strlen(start);
  size_t endLength = strlen(end);
  if (startLength < endLength)
    return 0;
  return (strcmp (&(start[startLength - endLength]), end) == 0);
}

const char *get_filename_ext(const char *filename) {
  const char *dot = strrchr(filename, '.');
  if(!dot || dot == filename) return "";
  return dot + 1;
}

