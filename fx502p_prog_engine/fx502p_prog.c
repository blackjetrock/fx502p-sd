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

#ifndef ARDUINO
#include "fx502p_prog.h"
#endif

typedef unsigned char uint8_t;


void pfn_null(CALC_502_STATE *state, int token)
{
}

// Program N, do nothing much
void pfn_prog(CALC_502_STATE *state, int token)
{
}

//--------------------------------------------------------------------------------

char *memory_name[NUM_MEMORIES] =
  {
    "M00",
    "M01",
    "M02",
    "M03",
    "M04",
    "M05",
    "M06",
    "M07",
    "M08",
    "M09",
    "M10",
    "M11",
    "M12",
    "M13",
    "M14",
    "M15",
    "M16",
    "M17",
    "M18",
    "M19",
    "M0F",
    "M1F",
  };


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
    {"NONE", 0x00, pfn_null},

  };

char *token_name(int token)
{
  return(token_list[token].name);
}

////////////////////////////////////////////////////////////////////////////////
//
// Given a token, returns the program number
//

int token_to_prognum(int token)
{
  int rc = PROG_NO_PROG;
  
  switch(token)
    {
    case TOK_P0:
      rc = 0;
      break;
    case TOK_P1:
      rc = 1;
      break;
      
    case TOK_P2:
      rc = 2;
      break;
      
    case TOK_P3:
      rc = 3;
      break;
      
    case TOK_P4:
      rc = 4;
      break;
      
    case TOK_P5:
      rc = 5;
      break;
      
    case TOK_P6:
      rc = 6;
      break;
      
    case TOK_P7:
      rc = 7;
      break;
      
    case TOK_P8:
      rc = 8;
      break;
      
    case TOK_P9:
      rc = 9;
      break;
      
    }
  
  return(rc);
}
//--------------------------------------------------------------------------------
//
// Returns the operator corresponding to a token or key

int token_to_op(int token)
{
  int rc = OP_NONE;

  switch(token)
    {
    case TOK_DIVIDE:
    case KEY_DIV:
      rc = OP_DIVIDE;
      break;
    case TOK_MINUS:
    case KEY_MINUS:
      rc = OP_MINUS;
      break;

    case TOK_PLUS:
    case KEY_PLUS:
      rc = OP_PLUS;
      break;

    case TOK_TIMES:
    case KEY_TIMES:
      rc = OP_TIMES;
      break;
    }
  
  return(rc);
}

//--------------------------------------------------------------------------------
// returns numeric value of a number token

int num_value_of(int token)
{
  int retval = 0;
  
  switch(token)
    {
    case TOK_0:
    case KEY_0:
      retval = 0;
      break;
    case TOK_1:
    case KEY_1:
      retval = 1;
      break;
    case TOK_2:
    case KEY_2:
      retval = 2;
      break;
    case TOK_3:
    case KEY_3:
      retval = 3;
      break;
    case TOK_4:
    case KEY_4:
      retval = 4;
      break;
    case TOK_5:
    case KEY_5:
      retval = 5;
      break;
    case TOK_6:
    case KEY_6:
      retval = 6;
      break;
    case TOK_7:
    case KEY_7:
      retval = 7;
      break;
    case TOK_8:
    case KEY_8:
      retval = 8;
      break;
    case TOK_9:
    case KEY_9:
      retval = 9;
      break;
      
    }
  
  return(retval);
}

//--------------------------------------------------------------------------------

// Dump calculator state

void dump_state(CALC_502_STATE *state)
{
  printf("\n");
  printf("\nX:%f",   state->X);
  printf("\nY:%f",   state->Y);
  FOR_EACH_MEMORY
    printf("\n%s:%f", memory_name[i], state->M[i]);
  
  printf("\nNumber of steps used: %d", state->prog_steps_used);
  printf("\nNext token:           %s", token_name(*(state->next_token)));
  printf("\nPending operator:     %s", token_name(state->op));
  printf("\nProgram running:      %d", state->prog_running);
  printf("\nEntering number:      %d", state->entering_number);

  
  printf("\n");  
}


void reset_state(CALC_502_STATE *state, int *prog_space, int prog_steps)
{
  state->X = 0.0;
  state->Y = 0.0;
  FOR_EACH_MEMORY
    {
      state->M[i] = 0.0;
    }

  state->program_space      = prog_space;
  state->prog_running       = false;
  state->prog_steps_used    = prog_steps;
  state->next_token         = prog_space;
  state->entering_number    = 0;
  state->entering_exp       = 0;
  state->entering_frac      = 0;
  state->op                 = TOK_NONE;
  state->substate           = SSTATE_NONE;
  state->inv                = 0;
  state->mem_num            = 0;
  state->mode               = MMODE_RUN;
  state->update_result      = 0;
  state->prog_editing       = PROG_NO_PROG;
}

//--------------------------------------------------------------------------------
//
// Convert memory action token to memory index

int memory_token_to_index(int token)
{
  int retval;

  switch(token)
    {
    case TOK_Min00:
    case TOK_Min01:
    case TOK_Min02:
    case TOK_Min03:
    case TOK_Min04:
    case TOK_Min05:
    case TOK_Min06:
    case TOK_Min07:
    case TOK_Min08:
    case TOK_Min09:
    case TOK_Min10:
    case TOK_Min11:
    case TOK_Min12:
    case TOK_Min13:
    case TOK_Min14:
    case TOK_Min15:
    case TOK_Min16:
    case TOK_Min17:
    case TOK_Min18:
    case TOK_Min19:

      retval = token - TOK_Min00;
      break;

    case TOK_X_TO_M00:
    case TOK_X_TO_M01:
    case TOK_X_TO_M02:
    case TOK_X_TO_M03:
    case TOK_X_TO_M04:
    case TOK_X_TO_M05:
    case TOK_X_TO_M06:
    case TOK_X_TO_M07:
    case TOK_X_TO_M08:
    case TOK_X_TO_M09:
    case TOK_X_TO_M10:
    case TOK_X_TO_M11:
    case TOK_X_TO_M12:
    case TOK_X_TO_M13:
    case TOK_X_TO_M14:
    case TOK_X_TO_M15:
    case TOK_X_TO_M16:
    case TOK_X_TO_M17:
    case TOK_X_TO_M18:
    case TOK_X_TO_M19:
      retval = token - TOK_X_TO_M00;
      break;

    case TOK_MR00:
    case TOK_MR01:
    case TOK_MR02:
    case TOK_MR03:
    case TOK_MR04:
    case TOK_MR05:
    case TOK_MR06:
    case TOK_MR07:
    case TOK_MR08:
    case TOK_MR09:
    case TOK_MR10:
    case TOK_MR11:
    case TOK_MR12:
    case TOK_MR13:
    case TOK_MR14:
    case TOK_MR15:
    case TOK_MR16:
    case TOK_MR17:
    case TOK_MR18:
    case TOK_MR19:
      retval = token - TOK_MR00;
      break;
      
    case TOK_M_MINUS_00:
    case TOK_M_MINUS_01:
    case TOK_M_MINUS_02:
    case TOK_M_MINUS_03:
    case TOK_M_MINUS_04:
    case TOK_M_MINUS_05:
    case TOK_M_MINUS_06:
    case TOK_M_MINUS_07:
    case TOK_M_MINUS_08:
    case TOK_M_MINUS_09:
    case TOK_M_MINUS_10:
    case TOK_M_MINUS_11:
    case TOK_M_MINUS_12:
    case TOK_M_MINUS_13:
    case TOK_M_MINUS_14:
    case TOK_M_MINUS_15:
    case TOK_M_MINUS_16:
    case TOK_M_MINUS_17:
    case TOK_M_MINUS_18:
    case TOK_M_MINUS_19:
      retval = token - TOK_M_MINUS_00;
      break;

    case TOK_M_PLUS_00:
    case TOK_M_PLUS_01:
    case TOK_M_PLUS_02:
    case TOK_M_PLUS_03:
    case TOK_M_PLUS_04:
    case TOK_M_PLUS_05:
    case TOK_M_PLUS_06:
    case TOK_M_PLUS_07:
    case TOK_M_PLUS_08:
    case TOK_M_PLUS_09:

    case TOK_M_PLUS_10:
    case TOK_M_PLUS_11:
    case TOK_M_PLUS_12:
    case TOK_M_PLUS_13:
    case TOK_M_PLUS_14:
    case TOK_M_PLUS_15:
    case TOK_M_PLUS_16:
    case TOK_M_PLUS_17:
    case TOK_M_PLUS_18:
    case TOK_M_PLUS_19:
      retval = token - TOK_M_PLUS_00;
      break;
      
    case TOK_X_TO_MF:
    case TOK_MinF:
    case TOK_MRF:
    case TOK_M_MINUS_F:
    case TOK_M_PLUS_F:
      retval = INDEX_M0F;
      break;
      
    case TOK_Min1F:
    case TOK_MR1F:
    case TOK_M_MINUS_1F:
    case TOK_M_PLUS_1F:
      retval = INDEX_M1F;
      break;
    }

  return(retval);
}

//--------------------------------------------------------------------------------
//
// Finds the token corresponding to the one passed in
//
// e.g. LBL0   <-> GOTO0
//

int find_corresponding_token(int t)
{
  int retval = TOK_NONE;
  
  switch(t)
    {
    case TOK_GOTO0:
    case TOK_GOTO1:
    case TOK_GOTO2:
    case TOK_GOTO3:
    case TOK_GOTO4:
    case TOK_GOTO5:
    case TOK_GOTO6:
    case TOK_GOTO7:
    case TOK_GOTO8:
    case TOK_GOTO9:
      retval = (int)((int)t - (int)TOK_GOTO0) + (int)TOK_LBL0;
    }

  return(retval);
}

//--------------------------------------------------------------------------------

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

////////////////////////////////////////////////////////////////////////////////

void all_clear(CALC_502_STATE *state)
{
  state->entering_number = false;
  state->entering_exp = false;
  state->entering_frac = 0;
  state->X = 0.0;
  strcpy(state->Xstr, "                    ");
  state->update_result = 1;
}

////////////////////////////////////////////////////////////////////////////////
//
// WRT Mode
//
// This mode does not execute any keypresses, it just manages the programs
// in the program space
//
// The tokens in the space are the sme as the 502p tokens, so hopefully we
// should be able to execute programs saved from the 502p.

void mode_wrt(CALC_502_STATE *state, int keypress)
{
  int token = keypress;
  
  // We have to handle INV
#if 0
  if( state->inv )
    {
      if( token != KEY_INV )
	{
	  state->inv = 0;
	}
    }
#endif
  
  switch(token)
    {
    case KEY_INV:
      state->inv = !(state->inv);
      break;

    case KEY_MODE:
      state->substate = SSTATE_MODE_ENTER;;
      break;
      
    }

    switch(state->substate)
    {
    case SSTATE_MODE_ENTER:
      switch(token)
	{
	case KEY_1:
	  state->mode = MMODE_RUN;
	  state->substate = SSTATE_NONE;
	  all_clear(state);
	  break;

	case KEY_2:
	  state->mode = MMODE_WRT;
	  state->substate = SSTATE_WRT_FRONT;
	  sprintf(state->Xstr, program_index(state));
	  break;

	case KEY_3:
	  state->mode = MMODE_PCL;
	  state->substate = SSTATE_PCL_FRONT;
	  break;
	}
      break;
    }

    // We convert some keycodes to tokens
    switch(token)
      {
      case KEY_P0:
	if(state->inv)
	  {
	    token = TOK_P5;
	  }
	else
	  {
	    token = TOK_P0;
	  }
	break;
	
      case KEY_P1:
	if(state->inv)
	  {
	    token = TOK_P6;
	  }
	else
	  {
	    token = TOK_P1;
	  }
	break;

      case KEY_P2:
	if(state->inv)
	  {
	    token = TOK_P7;
	  }
	else
	  {
	    token = TOK_P2;
	  }

	break;

      case KEY_P3:
	if(state->inv)
	  {
	    token = TOK_P8;
	  }
	else
	  {
	    token = TOK_P3;
	  }
	break;

      case KEY_P4:
	if(state->inv)
	  {
	    token = TOK_P9;
	  }
	else
	  {
	    token = TOK_P4;
	  }
	break;
      }
    
    switch(state->substate)
      {
	// When displaying a program the current step is last on the screen
	// We decode instructions, so don't use the 502 codes, because we have
	// a full screen to do it with.
      case SSTATE_WRT_DISP_PROG:
	
	break;
	
      case SSTATE_WRT_FRONT:
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
	    state->prog_editing = token_to_prognum(token);
	    
	    break;
	  }
	
	break;
      }
}



////////////////////////////////////////////////////////////////////////////////
//
// Execute one token
//
// A token can either be a stored program token, or a key press
// These two types of token have different number spaces
//

void exec_token(CALC_502_STATE *state, int key_press)
{
  int token;
  int label_token;
  int *t;
  int i;
  double in, fr;
  double temp;
  
  // Were we supplied with a keypress?
  if( key_press != KEY_NONE )
    {
      token = key_press;
    }
  else
    {
      // Get the next token from the program
      if( (state->next_token - state->program_space) > state->prog_steps_used )
	{
	  state->prog_running = false;
	  return;
	}
      else
	{
	  // We are running a program
	  state->prog_running = true;
	}
      
      // Get next token to execute
      token = *(state->next_token);
    }

  // The WRT and PCL modes have completely different operation so they are processed here
  switch(state->mode)
    {
    case MMODE_WRT:
      mode_wrt(state, token);
      break;

    case MMODE_PCL:
      switch(state->substate)
	{
	case SSTATE_PCL_FRONT:
	  sprintf(state->Xstr, program_index(state));
	  state->update_result = 1;
	  break;
	}
      break;

    }
    
  //  printf("\nToken:%d ", token);
  
  // dump_state(state);

  // Some keypresses can be turned into tokens
  if( state->inv )
    {
      if( token != KEY_INV )
	{
	  state->inv = 0;
	}
      
      switch(token)
	{
	case KEY_OPBRA:
	  token = TOK_INT;
	  break;

	case KEY_CLBRA:
	  token = TOK_FRAC;
	  break;
	}
    }

  switch(state->substate)
    {
    case SSTATE_MODE_ENTER:
      switch(token)
	{
	case KEY_1:
	  state->mode = MMODE_RUN;
	  state->substate = SSTATE_NONE;
	  break;

	case KEY_2:
	  state->mode = MMODE_WRT;
	  state->substate = SSTATE_WRT_FRONT;
	  break;

	case KEY_3:
	  state->mode = MMODE_PCL;
	  state->substate = SSTATE_PCL_FRONT;
	  break;
	}
      break;
      
    case SSTATE_MIN_ENTER:
    case SSTATE_X_TO_M:
    case SSTATE_MR_ENTER:
    case SSTATE_M_PLUS:
    case SSTATE_M_MINUS:
      switch(token)
	{
	case KEY_DOT:
	  state->mem_num = 10;;
	  break;

	case TOK_0:
	case TOK_1:
	case TOK_2:
	case TOK_3:
	case TOK_4:
	case TOK_5:
	case TOK_6:
	case TOK_7:
	case TOK_8:
	case TOK_9:
	  
	case KEY_0:
	case KEY_1:
	case KEY_2:
	case KEY_3:
	case KEY_4:
	case KEY_5:
	case KEY_6:
	case KEY_7:
	case KEY_8:
	case KEY_9:

	  if( token == KEY_EXP )
	    {
	      if( state->mem_num == 10 )
		{
		  state->mem_num = INDEX_M1F;;
		}
	      else
		{
		  state->mem_num = INDEX_M0F;;
		}
	    }
	  else
	    {
	      state->mem_num = state->mem_num * 10 + num_value_of(token);
	    }
	  
	  switch(state->substate)
	    {
	    case SSTATE_MIN_ENTER:
	      state->M[state->mem_num] = state->X;
	      break;

	    case SSTATE_X_TO_M:
	      temp = state->M[state->mem_num];
	      state->M[state->mem_num] = state->X;
	      state->X = temp;
	      state->update_result = 1;
	      break;
	      
	    case SSTATE_MR_ENTER:
	      state->X = state->M[state->mem_num];
	      state->update_result = 1;
	      break;

	    case SSTATE_M_PLUS:
	      state->M[state->mem_num] = state->M[state->mem_num] + state->X;
	      break;

	    case SSTATE_M_MINUS:
	      state->M[state->mem_num] = state->M[state->mem_num] - state->X;
	      break;
	    }

	  Serial.print("Mem access:");
	  Serial.println(state->mem_num);
	  
	  token = KEY_NONE;
	  state->mem_num = 0;
	  state->substate = SSTATE_NONE;
	  break;
	}
      break;

    case SSTATE_NONE:
      Serial.println("SSTATE_NONE");
      switch(token)
	{
	case KEY_MIN:
	  state->substate = SSTATE_MIN_ENTER;
	  break;
	  
	case KEY_MR:
	  state->substate = SSTATE_MR_ENTER;
	  break;

	case KEY_MPLU:
	  state->substate = SSTATE_M_PLUS;
	  break;

	case KEY_MMIN:
	  state->substate = SSTATE_M_MINUS;
	  break;

	case KEY_X_M:
	  state->substate = SSTATE_X_TO_M;
	  break;
	}

    }

  switch(token)
    {

    case KEY_INV:
      state->inv = !(state->inv);
      break;
      
      
    case TOK_FRAC:
      state->X = modf(state->X, &in);
      state->update_result = 1;
      break;

    case TOK_INT:
      modf(state->X, &in);
      state->X = in;
      state->update_result = 1;
      break;
      
    case KEY_MODE:
      state->substate = SSTATE_MODE_ENTER;;
      break;
      
    case KEY_SIN:
    case TOK_SIN:
      state->X = sin(state->X);
      state->update_result = 1;
      break;

    case KEY_COS:
    case TOK_COS:
      state->X = cos(state->X);
      state->update_result = 1;
      break;
      
    case KEY_TAN:
    case TOK_TAN:
      state->X = tan(state->X);
      state->update_result = 1;
      break;
      
    case TOK_GOTO0:
    case TOK_GOTO1:
    case TOK_GOTO2:
    case TOK_GOTO3:
    case TOK_GOTO4:
    case TOK_GOTO5:
    case TOK_GOTO6:
    case TOK_GOTO7:
    case TOK_GOTO8:
    case TOK_GOTO9:
      
      label_token = find_corresponding_token(token);
      
      // Search for the given label
      for(i=0, t=state->program_space; i<state->prog_steps_used; i++, t++)
	{
	  if( *t == label_token )
	    {
	      // Found it
	      state->next_token = t;
	      break;
	    }

	  // Not found, just carry on
	}
      break;

    case TOK_DSZ:
      state->M[0] = state->M[0]-1.0;

      if( state->M[0] == 0.0 )
	{
	  (state->next_token)++;
	}
      
      break;
      
    case TOK_Min00:
    case TOK_Min01:
    case TOK_Min02:
    case TOK_Min03:
    case TOK_Min04:
    case TOK_Min05:
    case TOK_Min06:
    case TOK_Min07:
    case TOK_Min08:
    case TOK_Min09:
    case TOK_MinF:
    case TOK_Min10:
    case TOK_Min11:
    case TOK_Min12:
    case TOK_Min13:
    case TOK_Min14:
    case TOK_Min15:
    case TOK_Min16:
    case TOK_Min17:
    case TOK_Min18:
    case TOK_Min19:
    case TOK_Min1F:
      state->M[memory_token_to_index(token)] = state->X;
      break;

    case TOK_MR00:
    case TOK_MR01:
    case TOK_MR02:
    case TOK_MR03:
    case TOK_MR04:
    case TOK_MR05:
    case TOK_MR06:
    case TOK_MR07:
    case TOK_MR08:
    case TOK_MR09:
    case TOK_MRF:
    case TOK_MR10:
    case TOK_MR11:
    case TOK_MR12:
    case TOK_MR13:
    case TOK_MR14:
    case TOK_MR15:
    case TOK_MR16:
    case TOK_MR17:
    case TOK_MR18:
    case TOK_MR19:
    case TOK_MR1F:
      state->X          = state->M[memory_token_to_index(token)];
      break;

    case TOK_PLUSMINUS:
    case KEY_PLMIN:
      state->X = -state->X;
      state->update_result = 1;
      break;

    case TOK_EQUAL:
    case KEY_EQ:
      // If entering a number we perform operator on X and Y
      if( state->entering_number || (state->op != TOK_NONE) )
	{
	  state->entering_number = false;
	  state->entering_frac = 0;
	  switch(state->op)
	    {
	    case OP_MINUS:
	      state->X = state->Y - state->X;
	      break;

	    case OP_DIVIDE:
	      state->X = state->Y / state->X;
	      break;

	    case OP_TIMES:
	      state->X = state->X * state->Y;
	      break;
	      
	    case OP_PLUS:
	      state->X = state->X + state->Y;
	      break;
	    }
	  
	}
      else
	{
	  //Not entering a number, real calculator normalises display here
	}

      // Equals always stops number entry
      state->update_result = 1;
      state->entering_number = false;
      state->entering_exp = false;
      state->entering_frac = 0;
      break;
      
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


    case TOK_TIMES:
    case KEY_TIMES:
    case TOK_PLUS:
    case KEY_PLUS:
    case TOK_DIVIDE:
    case KEY_DIV:
    case TOK_MINUS:
    case KEY_MINUS:
      // Not entering any more, and we have a pending operator
      state->entering_number = false;
      state->entering_exp = false;
      state->entering_frac = 0;
      state->Y = state->X;
      state->X = 0.0;
      state->op = token_to_op(token);
      break;

    case TOK_AC:
    case KEY_AC:
      all_clear(state);
      break;
      
    case KEY_EXP:
    case TOK_EXP:
      if( state->entering_number )
	{
	  // Now entering exponent
	  state->entering_exp = true;
	  state->entering_frac = 0;
	}
      else
	{
	  // Enter PI
	  state->X = 3.141592653;
	  state->update_result = 1;
	}
      

      break;

    case TOK_DOT:
    case KEY_DOT:
      state->entering_frac = 1;
      state->frac_mul = 0.1;
      strcat(state->Xstr, ".");
      break;
      

    case TOK_0:
    case TOK_1:
    case TOK_2:
    case TOK_3:
    case TOK_4:
    case TOK_5:
    case TOK_6:
    case TOK_7:
    case TOK_8:
    case TOK_9:
<<<<<<< HEAD

    case KEY_0:
    case KEY_1:
    case KEY_2:
    case KEY_3:
    case KEY_4:
    case KEY_5:
    case KEY_6:
    case KEY_7:
    case KEY_8:
    case KEY_9:

      if( state->entering_number )
	{
	}
      else
	{
	  // Not entering a number, clear X then enter number
	  state->X = 0.0;
	  strcpy(state->Xstr, "0");
	}

      strcat(state->Xstr, get_keysym(token));
	     
      if( state->entering_frac )
	{
	  state->X += num_value_of(token) * state->frac_mul;
	  state->frac_mul /= 10.0;
	}
      else  if( state->entering_exp )
	{

	}
      else
	{
	  // Add digit
	  if( state->X < 9999999999 )
	    {
	      state->X *= 10.0;
	      state->X += num_value_of(token);
	    }
	  state->entering_number = true;
=======
      if( state->X <9999999999 )
	{
          int digval = token - TOK_0;
	  state->X *= 10.0;
	  state->X += digval;
>>>>>>> 90d6d19 (Updates)
	}
      break;
    }

  (state->next_token)++;
}
