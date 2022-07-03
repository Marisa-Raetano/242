#include <stdio.h>
#include <string.h>
//#include "word,h"

  //LENGTH OF STRING
void Length(char string[20][11], int n)
{
  int stringi;
  int longest;
  int j;
  int length;
  char stringnum = 10;

  longest= strlen(string[0]);
  for(stringi = 1; stringi < n; ++stringi)
  {
    length = strlen(string[stringi]);
    if(length > longest)
    {
      j = stringi;
      longest = length;
    }
  }
  
  if(strlen(string[stringi]) > strlen(string[stringnum]))
	printf("Error \n");
 
  printf("The longest word is: \"%s\", \n", string[j]);

}
/*
void Sort(char string[20][11],int n)
{
  int stringl;
  int temp_word;
  int stringm;
  int count;

  for(stringl = 0; stringl < strlen[n]; ++stringl)
  {
    for(stringm = 0; stringm < strlen[n]; ++stringm)
    {
      if(strcmp(string[stringl], [stringm] > 0)

	  strcpy(temp_word, string[stringl]);
	  strcpy(string[stringl, string[stringm]);
	  strcpy(string[stringm], temp_word);
	  }

	    }
}
*/
int main()
{
  //GET THE STRINGS

  char string[20][11];
  int i;
  int n =5;
  int wordCount;
  printf("Please type %d words here: \n", n);
  for( i = 0; i<n; ++i)
  {
    scanf("%s",string[i]);

  }


  Length(string,n);

  printf("The first word is: \n");
}


