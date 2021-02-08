#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8_t;

int main(int argc, char *argv[])
{
  FILE *fp;
  int c;
  char *token_file = "fpe.dat";

  fp = fopen(token_file, "r");

  if( fp == NULL )
    {
      printf("\nCould not open file\n");
      exit(0);
    }
  while( !feof(fp) )
    {
      c = fgetc(fp);

      printf("\n%02X", c);
    }
  
  fclose(fp);
  
}
