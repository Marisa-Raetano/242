#include <stdio.h> 

#include <stdlib.h> // For exit() 

#include <string.h>



// argc - will be the count of input arguments to your program.

// argv - will be a pointer to all the input arguments.

// argv[0] will be the name of your program "scan"

// argv[1] will be the name of the partial file "Test"



int main ( int argc, char *argv[] )

{

  //test to ensure you have a partial filename

  if(argc!=2){printf("Usage:...please enter a partial filename");exit(1);}



  FILE *fptr; 



  const char *myarg = NULL;    



  char filename[100], c; 



  myarg = argv[1];



  char temp[strlen(myarg) + 1];

  strcpy(filename, myarg);



  printf("filename to open %s \n", filename);

  //scanf("%s", filename); 



  // Open file 

  fptr = fopen(filename, "r"); 

  if (fptr == NULL) 

  { 

    printf("Cannot open file \n"); 

    exit(0); 

  } 



  // Read contents from file 

  c = fgetc(fptr); 

  while (c != EOF) 

  { 

    printf ("%c", (c * 2)); 

    c = fgetc(fptr); 

  } 



  fclose(fptr); 

  return 0; 

}
