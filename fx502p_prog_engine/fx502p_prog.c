////////////////////////////////////////////////////////////////////////////////
//
// Executes an FX-502P program, given the state of a calculator
// and the program tokens
//
// One token is executed
// a break is seen (AC key)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fx502p_prog.h"

typedef unsigned char uint8_t;

//--------------------------------------------------------------------------------

// Dump calculator state

void dump_state(CALC_502_STATE *state)
{
  printf("\n");
  printf("\nX:%f",   state->X);
  printf("\nM0F:%f", state->M0F);
  printf("\nM1F:%f", state->M1F);
  printf("\nM00:%f", state->M00);
  printf("\nM01:%f", state->M01);
  printf("\nM02:%f", state->M02);
  printf("\nM03:%f", state->M03);
  printf("\nM04:%f", state->M04);
  printf("\nM05:%f", state->M05);
  printf("\nM06:%f", state->M06);
  printf("\nM07:%f", state->M07);
  printf("\nM08:%f", state->M08);
  printf("\nM09:%f", state->M09);
  printf("\nM10:%f", state->M10);
  printf("\nM11:%f", state->M11);
  printf("\nM12:%f", state->M12);
  printf("\nM13:%f", state->M13);
  printf("\nM14:%f", state->M14);
  printf("\nM15:%f", state->M15);
  printf("\nM16:%f", state->M16);
  printf("\nM17:%f", state->M17);
  printf("\nM18:%f", state->M18);
  printf("\nM19:%f", state->M19);
  printf("\n");  
}


void reset_state(CALC_502_STATE *state)
{
  state->X = 0.0;
  state->M0F = 0.0;
  state->M1F = 0.0;
  state->M00 = 0.0;
  state->M01 = 0.0;
  state->M02 = 0.0;
  state->M03 = 0.0;
  state->M04 = 0.0;
  state->M05 = 0.0;
  state->M06 = 0.0;
  state->M07 = 0.0;
  state->M08 = 0.0;
  state->M09 = 0.0;
  state->M10 = 0.0;
  state->M11 = 0.0;
  state->M12 = 0.0;
  state->M13 = 0.0;
  state->M14 = 0.0;
  state->M15 = 0.0;
  state->M16 = 0.0;
  state->M17 = 0.0;
  state->M18 = 0.0;
  state->M19 = 0.0;

}


//--------------------------------------------------------------------------------

void pfn_null(CALC_502_STATE *state, int token)
{
}

// Program N, do nothing much
void pfn_prog(CALC_502_STATE *state, int token)
{
}

void prog_digit(CALC_502_STATE *state, int token)
{
  int digval;

  switch(token)
    {
    case TOK_0:
    case TOK_1:
    case TOK_2:
    case TOK_3:
      digval -= TOK_0;
      break;

    case TOK_4:
    case TOK_5:
    case TOK_6:
    case TOK_7:
    case TOK_8:
    case TOK_9:
      digval -= TOK_4;
      break;

    default:
      printf("\nShould be a digit: %d", token);
      break;
    }
  
  // Add to the X register
  state->X *= 10.0;
  state->X += digval;
  
}

TOKEN token_list[] =
  {
    {"P0", 0x00, pfn_prog},       
    {"P1", 0x00, pfn_prog},
    {"P2", 0x00, pfn_prog},
    {"P3", 0x00, pfn_prog},
    {"P4", 0x00, pfn_prog},
    {"P5", 0x00, pfn_prog},
    {"P6", 0x00, pfn_prog},
    {"P7", 0x00, pfn_prog},
    {"P8", 0x00, pfn_prog},
    {"P9", 0x00, pfn_prog},
    {"0", 0x00, pfn_null},
    {"1", 0x00, pfn_null},
    {"2", 0x00, pfn_null},
    {"3", 0x00, pfn_null},
    {".", 0x00, pfn_null},
    {"EXP", 0x00, pfn_null},
    {"RND0", 0x00, pfn_null},
    {"RND1", 0x00, pfn_null},
    {"RND2", 0x00, pfn_null},
    {"RND3", 0x00, pfn_null},
    {"RND4", 0x00, pfn_null},
    {"RND5", 0x00, pfn_null},
    {"RND6", 0x00, pfn_null},
    {"RND7", 0x00, pfn_null},
    {"RND8", 0x00, pfn_null},
    {"RND9", 0x00, pfn_null},
    {"4", 0x00, pfn_null},
    {"5", 0x00, pfn_null},
    {"6", 0x00, pfn_null},
    {"7", 0x00, pfn_null},
    {"8", 0x00, pfn_null},
    {"9", 0x00, pfn_null},
    {"LBL0", 0x00, pfn_null},
    {"LBL1", 0x00, pfn_null},
    {"LBL2", 0x00, pfn_null},
    {"LBL3", 0x00, pfn_null},
    {"LBL4", 0x00, pfn_null},
    {"LBL5", 0x00, pfn_null},
    {"LBL6", 0x00, pfn_null},
    {"LBL7", 0x00, pfn_null},
    {"LBL8", 0x00, pfn_null},
    {"LBL9", 0x00, pfn_null},
    {"HLT", 0x00, pfn_null},
    {"\"", 0x00, pfn_null},
    {"20+", 0x00, pfn_null},
    {"40+", 0x00, pfn_null},
    {"60+", 0x00, pfn_null},
    {"?2F", 0x00, pfn_null},
    {"GOTO0", 0x00, pfn_null},
    {"GOTO1", 0x00, pfn_null},
    {"GOTO2", 0x00, pfn_null},
    {"GOTO3", 0x00, pfn_null},
    {"GOTO4", 0x00, pfn_null},
    {"GOTO5", 0x00, pfn_null},
    {"GOTO6", 0x00, pfn_null},
    {"GOTO7", 0x00, pfn_null},
    {"GOTO8", 0x00, pfn_null},
    {"GOTO9", 0x00, pfn_null},
    {"xD", 0x00, pfn_null},
    {"?3B", 0x00, pfn_null},
    {"ENG", 0x00, pfn_null},
    {"DMS", 0x00, pfn_null},
    {"LOG", 0x00, pfn_null},
    {"LN", 0x00, pfn_null},
    {"GSBP0", 0x00, pfn_null},
    {"GSBP1", 0x00, pfn_null},
    {"GSBP2", 0x00, pfn_null},
    {"GSBP3", 0x00, pfn_null},
    {"GSBP4", 0x00, pfn_null},
    {"GSBP5", 0x00, pfn_null},
    {"GSBP6", 0x00, pfn_null},
    {"GSBP7", 0x00, pfn_null},
    {"GSBP8", 0x00, pfn_null},
    {"GSBP9", 0x00, pfn_null},
    {"+/-", 0x00, pfn_null},
    {"(", 0x00, pfn_null},
    {")", 0x00, pfn_null},
    {"SIN", 0x00, pfn_null},
    {"COS", 0x00, pfn_null},
    {"TAN", 0x00, pfn_null},
    {"X<>M00", 0x00, pfn_null},
    {"X<>M01", 0x00, pfn_null},
    {"X<>M02", 0x00, pfn_null},
    {"X<>M03", 0x00, pfn_null},
    {"X<>M04", 0x00, pfn_null},
    {"X<>M05", 0x00, pfn_null},
    {"X<>M06", 0x00, pfn_null},
    {"X<>M07", 0x00, pfn_null},
    {"X<>M08", 0x00, pfn_null},
    {"X<>M09", 0x00, pfn_null},
    {"*", 0x00, pfn_null},
    {"/", 0x00, pfn_null},
    {"+", 0x00, pfn_null},
    {"-", 0x00, pfn_null},
    {"=", 0x00, pfn_null},
    {"EXE", 0x00, pfn_null},
    {"Min00", 0x00, pfn_null},
    {"Min01", 0x00, pfn_null},
    {"Min02", 0x00, pfn_null},
    {"Min03", 0x00, pfn_null},
    {"Min04", 0x00, pfn_null},
    {"Min05", 0x00, pfn_null},
    {"Min06", 0x00, pfn_null},
    {"Min07", 0x00, pfn_null},
    {"Min08", 0x00, pfn_null},
    {"Min09", 0x00, pfn_null},
    {"?6A", 0x00, pfn_null},
    {"DSZ", 0x00, pfn_null},
    {"X=0", 0x00, pfn_null},
    {"X=F", 0x00, pfn_null},
    {"RND#", 0x00, pfn_null},
    {"PI", 0x00, pfn_null},
    {"MR00", 0x00, pfn_null},
    {"MR01", 0x00, pfn_null},
    {"MR02", 0x00, pfn_null},
    {"MR03", 0x00, pfn_null},
    {"MR04", 0x00, pfn_null},
    {"MR05", 0x00, pfn_null},
    {"MR06", 0x00, pfn_null},
    {"MR07", 0x00, pfn_null},
    {"MR08", 0x00, pfn_null},
    {"MR09", 0x00, pfn_null},
    {"ISZ",  0x00, pfn_null},
    {"x>=0", 0x00, pfn_null},
    {"x>=F", 0x00, pfn_null},
    {"MEANX", 0x00, pfn_null},
    {"SDX", 0x00, pfn_null},
    {"SDXN", 0x00, pfn_null},
    {"M-00", 0x00, pfn_null},
    {"M-01", 0x00, pfn_null},
    {"M-02", 0x00, pfn_null},
    {"M-03", 0x00, pfn_null},
    {"M-04", 0x00, pfn_null},
    {"M-05", 0x00, pfn_null},
    {"M-06", 0x00, pfn_null},
    {"M-07", 0x00, pfn_null},
    {"M-08", 0x00, pfn_null},
    {"M-09", 0x00, pfn_null},
    {"PAUSE", 0x00, pfn_null},
    {"IND", 0x00, pfn_null},
    {"SAVE", 0x00, pfn_null},
    {"LOAD", 0x00, pfn_null},
    {"MAC", 0x00, pfn_null},
    {"SAC", 0x00, pfn_null},
    {"M+00", 0x00, pfn_null},
    {"M+01", 0x00, pfn_null},
    {"M+02", 0x00, pfn_null},
    {"M+03", 0x00, pfn_null},
    {"M+04", 0x00, pfn_null},
    {"M+05", 0x00, pfn_null},
    {"M+06", 0x00, pfn_null},
    {"M+07", 0x00, pfn_null},
    {"M+08", 0x00, pfn_null},
    {"M+09", 0x00, pfn_null},
    {"XDEL", 0x00, pfn_null},
    {"?9B", 0x00, pfn_null},
    {"SENG", 0x00, pfn_null},
    {"SDMS", 0x00, pfn_null},
    {"10^X", 0x00, pfn_null},
    {"e^X", 0x00, pfn_null},
    {"X<>M10", 0x00, pfn_null},
    {"X<>M11", 0x00, pfn_null},
    {"X<>M12", 0x00, pfn_null},
    {"X<>M13", 0x00, pfn_null},
    {"X<>M14", 0x00, pfn_null},
    {"X<>M15", 0x00, pfn_null},
    {"X<>M16", 0x00, pfn_null},
    {"X<>M17", 0x00, pfn_null},
    {"X<>M18", 0x00, pfn_null},       
    {"X<>M19", 0x00, pfn_null},
    {"ABS", 0x00, pfn_null},
    {"INT", 0x00, pfn_null},
    {"FRAC", 0x00, pfn_null},
    {"ASN", 0x00, pfn_null},
    {"ACS", 0x00, pfn_null},
    {"ATN", 0x00, pfn_null},
    {"Min10", 0x00, pfn_null},
    {"Min11", 0x00, pfn_null},
    {"Min12", 0x00, pfn_null},
    {"Min13", 0x00, pfn_null},
    {"Min14", 0x00, pfn_null},
    {"Min15", 0x00, pfn_null},
    {"Min16", 0x00, pfn_null},
    {"Min17", 0x00, pfn_null},
    {"Min18", 0x00, pfn_null},
    {"Min19", 0x00, pfn_null},
    {"X^Y", 0x00, pfn_null},
    {"X^(1/Y)", 0x00, pfn_null},
    {"R>P", 0x00, pfn_null},
    {"P>R", 0x00, pfn_null},
    {"%", 0x00, pfn_null},
    {"SEXE", 0x00, pfn_null},
    {"MR10", 0x00, pfn_null},
    {"MR11", 0x00, pfn_null},
    {"MR12", 0x00, pfn_null},
    {"MR13", 0x00, pfn_null},
    {"MR14", 0x00, pfn_null},
    {"MR15", 0x00, pfn_null},
    {"MR16", 0x00, pfn_null},
    {"MR17", 0x00, pfn_null},
    {"MR18", 0x00, pfn_null},
    {"MR19", 0x00, pfn_null},
    {"GSB(0)", 0x00, pfn_null},
    {"X<>Y", 0x00, pfn_null},
    {"SQR", 0x00, pfn_null},
    {"X^2", 0x00, pfn_null},
    {"1/X", 0x00, pfn_null},
    {"X!", 0x00, pfn_null},
    {"M-10", 0x00, pfn_null},
    {"M-11", 0x00, pfn_null},
    {"M-12", 0x00, pfn_null},
    {"M-13", 0x00, pfn_null},
    {"M-14", 0x00, pfn_null},
    {"M-15", 0x00, pfn_null},
    {"M-16", 0x00, pfn_null},
    {"M-17", 0x00, pfn_null},
    {"M-18", 0x00, pfn_null},
    {"M-19", 0x00, pfn_null},
    {"DEG", 0x00, pfn_null},
    {"RAD", 0x00, pfn_null},
    {"GRA", 0x00, pfn_null},
    {"HYPSIN", 0x00, pfn_null},
    {"HYPCOS", 0x00, pfn_null},
    {"HYPTAN", 0x00, pfn_null},
    {"M+10", 0x00, pfn_null},
    {"M+11", 0x00, pfn_null},
    {"M+12", 0x00, pfn_null},
    {"M+13", 0x00, pfn_null},
    {"M+14", 0x00, pfn_null},
    {"M+15", 0x00, pfn_null},
    {"M+16", 0x00, pfn_null},
    {"M+17", 0x00, pfn_null},
    {"M+18", 0x00, pfn_null},
    {"M+19", 0x00, pfn_null},
    {"?EA", 0x00, pfn_null},
    {"?EB", 0x00, pfn_null},
    {"?EC", 0x00, pfn_null},
    {"HYPASN", 0x00, pfn_null},
    {"HYPACS", 0x00, pfn_null},
    {"HYPATN", 0x00, pfn_null},
    {"X<>MF", 0x00, pfn_null},
    {"MinF", 0x00, pfn_null},
    {"MRF", 0x00, pfn_null},
    {"M-F", 0x00, pfn_null},
    {"M+F", 0x00, pfn_null},
    {"?F5", 0x00, pfn_null},
    {"Min1F", 0x00, pfn_null},
    {"MR1F", 0x00, pfn_null},
    {"M-1F", 0x00, pfn_null},
    {"M+1F", 0x00, pfn_null},
    {"AC", 0x00, pfn_null},
    {"?FB", 0x00, pfn_null},
    {"?FC", 0x00, pfn_null},
    {"?FD", 0x00, pfn_null},
    {"?FE", 0x00, pfn_null},
    {"?FF", 0x00, pfn_null},

  };

////////////////////////////////////////////////////////////////////////////////
//
// Execute one token
//

void exec_token(CALC_502_STATE *state, uint8_t token, uint8_t *token_space)
{

  dump_state(state);
  
  switch(token)
    {
    case TOK_P0:
    case TOK_P1:
    case TOK_P2:
    case TOK_P3:
    case TOK_P4:
    case TOK_P5:
    case TOK_P6:
    case TOK_P7:
    case TOK_P8:
    case TOK_P9:
      // Do nothing, start of a program
      break;

    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      if( state->X <9999999999 )
	{
	  state->X *= 10.0;
	  state->X += digval;
	}
      break;
    }
  
}
