#include <stdio.h>
#include <stdlib.h>

#include "fx502p_prog.h"

typedef unsigned char uint8_t;

TOKEN_CODE prog1[] =
  {
    TOK_P0,
    TOK_LBL0,
    TOK_TIMES,
    TOK_1,
    TOK_0,
    TOK_EQUAL,
  };

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

  CALC_502_STATE state;

  reset_state(&state);
  state.X = 3;
  dump_state(&state);
  
}
