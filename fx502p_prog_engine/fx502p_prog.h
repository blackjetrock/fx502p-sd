
////////////////////////////////////////////////////////////////////////////////
//
// FX502P Program Execution
//
//
// Token codes


// Token codes
enum
  {
    TOK_P0 = 0,
    TOK_P1,
    TOK_P2,
    TOK_P3,
    TOK_P4,
    TOK_P5,
    TOK_P6,
    TOK_P7,
    TOK_P8,
    TOK_P9,
    TOK_0,
    TOK_1,
    TOK_2,
    TOK_3,
    TOK_DOT,
    TOK_EXP,
    TOK_RND0,
    TOK_RND1,
    TOK_RND2,
    TOK_RND3,
    TOK_RND4,
    TOK_RND5,
    TOK_RND6,
    TOK_RND7,
    TOK_RND8,
    TOK_RND9,
    TOK_4,
    TOK_5,
    TOK_6,
    TOK_7,
    TOK_8,
    TOK_9,
    TOK_LBL0,
    TOK_LBL1,
    TOK_LBL2,
    TOK_LBL3,
    TOK_LBL4,
    TOK_LBL5,
    TOK_LBL6,
    TOK_LBL7,
    TOK_LBL8,
    TOK_LBL9,
    TOK_HLT,
    TOK_QUOTE,
    TOK_20,
    TOK_40,
    TOK_60,
    TOK_2F,
    TOK_GOTO0,
    TOK_GOTO1,
    TOK_GOTO2,
    TOK_GOTO3,
    TOK_GOTO4,
    TOK_GOTO5,
    TOK_GOTO6,
    TOK_GOTO7,
    TOK_GOTO8,
    TOK_GOTO9,
    TOK_xD,
    TOK_3B,
    TOK_ENG,
    TOK_DMS,
    TOK_LOG,
    TOK_LN,
    TOK_GSBP0,
    TOK_GSBP1,
    TOK_GSBP2,
    TOK_GSBP3,
    TOK_GSBP4,
    TOK_GSBP5,
    TOK_GSBP6,
    TOK_GSBP7,
    TOK_GSBP8,
    TOK_GSBP9,
    TOK_PLUSMINUS,
    TOK_OPENBRA,
    TOK_CLOSEBRA,
    TOK_SIN,
    TOK_COS,
    TOK_TAN,
    TOK_X_TO_M00,
    TOK_X_TO_M01,
    TOK_X_TO_M02,
    TOK_X_TO_M03,
    TOK_X_TO_M04,
    TOK_X_TO_M05,
    TOK_X_TO_M06,
    TOK_X_TO_M07,
    TOK_X_TO_M08,
    TOK_X_TO_M09,
    TOK_TIMES,
    TOK_DIVIDE,
    TOK_PLUS,
    TOK_MINUS,
    TOK_EQUAL,
    TOK_EXE,
    TOK_Min00,
    TOK_Min01,
    TOK_Min02,
    TOK_Min03,
    TOK_Min04,
    TOK_Min05,
    TOK_Min06,
    TOK_Min07,
    TOK_Min08,
    TOK_Min09,
    TOK_6A,
    TOK_DSZ,
    TOK_X_EQUAL_ZERO,
    TOK_X_EQUAL_F,
    TOK_RND_NUM,
    TOK_PI,
    TOK_MR00,
    TOK_MR01,
    TOK_MR02,
    TOK_MR03,
    TOK_MR04,
    TOK_MR05,
    TOK_MR06,
    TOK_MR07,
    TOK_MR08,
    TOK_MR09,
    TOK_ISZ,
    TOK_X_GT_EQ_ZERO,
    TOK_X_GT_EQ_F,
    TOK_MEANX,
    TOK_SDX,
    TOK_SDXN,
    TOK_M_MINUS_00,
    TOK_M_MINUS_01,
    TOK_M_MINUS_02,
    TOK_M_MINUS_03,
    TOK_M_MINUS_04,
    TOK_M_MINUS_05,
    TOK_M_MINUS_06,
    TOK_M_MINUS_07,
    TOK_M_MINUS_08,
    TOK_M_MINUS_09,
    TOK_PAUSE,
    TOK_IND,
    TOK_SAVE,
    TOK_LOAD,
    TOK_MAC,
    TOK_SAC,
    TOK_M_PLUS_00,
    TOK_M_PLUS_01,
    TOK_M_PLUS_02,
    TOK_M_PLUS_03,
    TOK_M_PLUS_04,
    TOK_M_PLUS_05,
    TOK_M_PLUS_06,
    TOK_M_PLUS_07,
    TOK_M_PLUS_08,
    TOK_M_PLUS_09,
    TOK_XDEL,
    TOK_9B,
    TOK_SENG,
    TOK_SDMS,
    TOK_10_POW_X,
    TOK_e_POW_X,
    TOK_X_TO_M10,
    TOK_X_TO_M11,
    TOK_X_TO_M12,
    TOK_X_TO_M13,
    TOK_X_TO_M14,
    TOK_X_TO_M15,
    TOK_X_TO_M16,
    TOK_X_TO_M17,
    TOK_X_TO_M18,
    TOK_X_TO_M19,
    TOK_ABS,
    TOK_INT,
    TOK_FRAC,
    TOK_ASN,
    TOK_ACS,
    TOK_ATN,
    TOK_Min10,
    TOK_Min11,
    TOK_Min12,
    TOK_Min13,
    TOK_Min14,
    TOK_Min15,
    TOK_Min16,
    TOK_Min17,
    TOK_Min18,
    TOK_Min19,
    TOK_X_POW_Y,
    TOK_X_POW_RECIP_Y,
    TOK_R_TO_P,
    TOK_P_TO_R,
    TOK_PERCENT,
    TOK_SEXE,
    TOK_MR10,
    TOK_MR11,
    TOK_MR12,
    TOK_MR13,
    TOK_MR14,
    TOK_MR15,
    TOK_MR16,
    TOK_MR17,
    TOK_MR18,
    TOK_MR19,
    TOK_GSB_IND0,
    TOK_X_TO_Y,
    TOK_SQR,
    TOK_X_POW_2,
    TOK_RECIP_X,
    TOK_FACTORIAL,
    TOK_M_MINUS_10,
    TOK_M_MINUS_11,
    TOK_M_MINUS_12,
    TOK_M_MINUS_13,
    TOK_M_MINUS_14,
    TOK_M_MINUS_15,
    TOK_M_MINUS_16,
    TOK_M_MINUS_17,
    TOK_M_MINUS_18,
    TOK_M_MINUS_19,
    TOK_DEG,
    TOK_RAD,
    TOK_GRA,
    TOK_HYPSIN,
    TOK_HYPCOS,
    TOK_HYPTAN,
    TOK_M_PLUS_10,
    TOK_M_PLUS_11,
    TOK_M_PLUS_12,
    TOK_M_PLUS_13,
    TOK_M_PLUS_14,
    TOK_M_PLUS_15,
    TOK_M_PLUS_16,
    TOK_M_PLUS_17,
    TOK_M_PLUS_18,
    TOK_M_PLUS_19,
    TOK_EA,
    TOK_EB,
    TOK_EC,
    TOK_HYPASN,
    TOK_HYPACS,
    TOK_HYPATN,
    TOK_X_TO_MF,
    TOK_MinF,
    TOK_MRF,
    TOK_M_MINUS_F,
    TOK_M_PLUS_F,
    TOK_F5,
    TOK_Min1F,
    TOK_MR1F,
    TOK_M_MINUS_1F,
    TOK_M_PLUS_1F,
    TOK_AC,
    TOK_FB,
    TOK_FC,
    TOK_FD,
    TOK_FE,
    TOK_FF,
    TOK_NONE
  };

// Operators
enum
  {
    OP_NONE = 0,
    OP_PLUS = 10,
    OP_MINUS,
    OP_DIVIDE,
    OP_TIMES,
  };

// State of the calculator
// programs are applied to this structure when they execute

typedef unsigned char uint8_t;

#ifndef ARDUINO
typedef int boolean;
#endif

#define false 0
#define true (!false);

#define NUM_MEMORIES 22

#define INDEX_M0F 20
#define INDEX_M1F 21

#define FOR_EACH_MEMORY for(int i=0;i<NUM_MEMORIES;i++)

typedef struct 
{
  double X;
  double Y;
  double M[NUM_MEMORIES];
  int         mode;              // The major mode the calculator is in
  int         *program_space;    // The program area
  int         *next_token;       // Next token to execute
  boolean     prog_running;      // true if program running
  int         prog_steps_used;   // Number of steps used
  int         entering_number;   // In progess of number entry in X if true
  int         entering_exp;      // In progress of entering exponent
  int         entering_frac;     // Entering fractional part
  double      frac_mul;          // Used when entering frac
  int         op;                // Pending operator
  int         substate;          // Sub state
  int         inv;               // Non zero if INV pending
  int         mem_num;           // Memory number when entering
} CALC_502_STATE;

typedef void (*PROG_FN)(CALC_502_STATE *state, int token);

typedef struct
{
  char *name;
  int flags;
  PROG_FN function;  
} TOKEN;

// Major modes
enum
  {
    MMODE_RUN,
    MMODE_WRT,
    MMODE_PCL,
  };

// Sub states
enum
  {
    SSTATE_NONE,
    SSTATE_MIN_ENTER,
    SSTATE_MR_ENTER,
    SSTATE_X_TO_M,
    SSTATE_M_PLUS,
    SSTATE_M_MINUS,
    SSTATE_MODE_ENTER,
    
  };

void dump_state(CALC_502_STATE *state);
void reset_state(CALC_502_STATE *state, int *prog_space, int prog_steps);
void exec_token(CALC_502_STATE *state, int key_press);
