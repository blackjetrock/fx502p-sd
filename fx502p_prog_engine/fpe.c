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
    TOK_Min03,
    TOK_MinF,
    TOK_MR03,
    TOK_TIMES,
    TOK_MRF,
    TOK_EQUAL,
    TOK_Min1F
  };

TOKEN_CODE prog2[] =
  {
    TOK_P0,
    TOK_4,
    TOK_Min00,
    TOK_LBL0,
    TOK_1,
    TOK_M_PLUS_01,
    TOK_DSZ,
    TOK_GOTO0,
  };

int main(int argc, char *argv[])
{
  FILE *fp;
  int c;
  char *token_file = "fpe.dat";
  int i;
  
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

  //  reset_state(&state, prog1, sizeof(prog1)/sizeof(TOKEN_CODE));
  reset_state(&state, prog2, sizeof(prog2)/sizeof(TOKEN_CODE));
  
  state.X = 3;

  for(;;)
    {
      exec_token(&state);

      if( !state.prog_running )
	{
	  break;
	}
    }
  
  dump_state(&state);
  
}
