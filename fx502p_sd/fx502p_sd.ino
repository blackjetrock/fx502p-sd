//
// Sketch to attach to fx502p and read/write data to/from SD card
//
// This sketch accepts commands from the 502p and stores the data
// words on the SD card under a filename specified on the 502p. This
// is a three digit number. When loading back the data words are sent
// as they were received.
//
// The files are FILEtnnn.DAT
//
//    where nnn is the 3 digit file number
//    and t is the type of the file:
//         M for memories
//         P for programs
//
// We leave the data line as an open drain
// output, even when we want to use it as an input. This saves the
// cycles needed to call pinMode(). Time is short when processing
// the commands from the 502p so all of the processing is done in
// interrupt routines using nested switch FSMs
//
// The header has been cut down to the minimum that works (50 words)
// and there's no delay when sending data words to or from the 502p.
// This means loading and saving is faster than using the FA-1
//
// 

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Code configuration
#define USE_HINT_LENGTH            0   // Sometimes we know how long the next packet is
#define LATER_OP_RD                1   // Fixes the problem where the OP GPIO state isn't read correctly,
                                       // so adds a delay before we read it.
#define ENABLE_SERIAL              1
#define ENABLE_OLED_SETUP          1
#define DEBUG_SERIAL               0
#define DIRECT_WRITE               0
#define DROP_ZERO_BIT_PACKETS      1
#define TRACE_CLOCKS               1    // If code > 58K-ish and trace clocks off then
                                        // save load doesn't work. No idea why
                                        // If code size is <58K -ish then tracing clocks stops
                                        // save/load working.
#define TRACE_TAGS                 1
#define DISABLE_MONITOR_DURING_RX  1
#define STAT_OP                    0
#define STAT_CE                    1
#define STAT_SP                    1
#define STAT_BITS_0                0
#define SHIFT_TX_DATA              1
#define TX_CHANGE_RISING_EDGE      1   // TX data changes on rising edge of SP

#define HEADER_LENGTH            -50
#define HEADER_WORD              0xffff
#define MEMORY_LENGTH             8    // Number of bytes a memory uses
#define NUM_MEMORIES             22

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
//TwoWire Wire2(PB11,PB10);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// Macro to set up the first data bit (has to be done on previous clock edge
// before sending the data

#if TX_CHANGE_RISING_EDGE
#define SET_DATA_BIT0  if( (isr_send_data & 1) ) digitalWrite(D3Pin, LOW)
#else
#define SET_DATA_BIT0  ;
#endif

// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

int filename_index = 0;

const int chipSelect = PA4;

// Pins for fx502p interface
const int D3Pin      = PB3;
const int OPPin      = PB4;

const int SPPin      = PB12;
const int CEPin      = PB13;
const int VCCPin     = PB14;
const int CONTPin    = PB15;

const int LEDPin     = PC3;

#define ISOLATE_BIT(N,X) ((X & (1<< N)) >> N)

// Debug outputs
const int statPin   = PC0;
const int dataPin   = PC1;


// FSM output flags
boolean cis_flag_event = false;
char *cis_event = "None";

// Event flags
boolean cis_flag_event_read_file = false;  // File data has been read

// File number of data file
char filenum[4] = "...";
char filetype = 'X';

int loopcnt = 0;
volatile int captured_word = 0;
  
File myFile;

// Capture file
File dumpfile;


enum
  {
    CIS_IDLE          = 0,
    CIS_502_PO_1      = 1,
    CIS_RX_UNKNOWN_A  = 2,
    CIS_RX_WAIT       = 3,
    CIS_WAIT_2        = 4,
    CIS_WAIT_3        = 5,
    CIS_WAIT_TRANS    = 6,
    CIS_WAIT_DATA     = 7,
    CIS_RD_1          = 8,
    CIS_RD_STAT       = 9,
    CIS_RD_WAIT_TRANS = 10,
    CIS_RD_SENDING    = 11,
    
  };

char *state_decode_list[] =
  {
    "CIS_IDLE",
    "CIS_502_PO_1",
    "CIS_RX_UNKNOWN_A",
    "CIS_RX_WAIT",
    "CIS_WAIT_2",
    "CIS_WAIT_3",
    "CIS_WAIT_TRANS",
    "CIS_WAIT_DATA",
    "CIS_RD_1",
    "CIS_RD_STAT",
    "CIS_RD_WAIT_TRANS",
    "CIS_RD_SENDING",
  };
  
// Commands
enum
  {
    // Data words
    IP_RESET        = 0x00,
    IP_TRANSFER     = 0x02,
    IP_PRESENCE     = 0x03,
    IP_READ_STATUS  = 0x04,
    IP_WAIT         = 0x0c,
    IP_PLAY         = 0x0e,
    IP_PRTSTR       = 0x10,
    IP_PRTNUM       = 0x11,
    IP_SENDDAT      = 0x13,
    IP_OPEN_RD      = 0x18,
    IP_UNKA         = 0x19,
    IP_TERMINATE    = 0x1f,
    IP_RDSTAT       = 0x21,
    IP_CARRIER_DET  = 0x24,
    IP_OPEN_WR      = 0x28,
    IP_SELPRT       = 0x29,
    IP_SENDCTRL     = 0x33,
    IP_COUNTER      = 0x34,
    IP_CLOSE        = 0x3C,
    IP_STOP         = 0x3E,

    // Special stimulii
    //.    IP_SEND_DONE2   = 0x205D,
    //IP_SEND_DONE    = 0x40BA,
  };


const int MAX_BYTES = 20;
const int button1Pin = PA0;
const int button2Pin = PA1;
const int button3Pin = PC15;

volatile int in_byte = 0;
volatile int isr_send_bits = 0;
volatile unsigned int isr_send_data = 0;
volatile int isr_send_data_save = 0;
volatile int isr_send_bits_save = 0;
volatile boolean isr_send_flag = false;
volatile boolean isr_send_done = false;
volatile int isr_current_op = 0;
volatile int ce_isr_state = CIS_IDLE;
volatile int num_header_words = 0;
volatile int isr_hint_length = 0;

// The serial monitor cannot run while we are capturing data as
// I think it disables interrupts. This causes problems for our
// decoding
volatile boolean monitor_enabled = true;

typedef unsigned char BYTE;

typedef void (*FPTR)();
typedef void (*CMD_FPTR)(String cmd);

// CE ISR states

#define NUM_BUTTONS 3

// Debounce
#define MAX_BUT_COUNT 6

int but_pins[NUM_BUTTONS] = {button1Pin, button2Pin, button3Pin};

typedef struct _BUTTON
{
  int     count;
  boolean pressed;
  boolean last_pressed;   // For edge detection
  FPTR    event_fn;
} BUTTON;

BUTTON buttons[NUM_BUTTONS];

enum ELEMENT_TYPE
  {
    BUTTON_ELEMENT = 10,
    SUB_MENU,
    MENU_END,
  };

struct MENU_ELEMENT
{
  enum ELEMENT_TYPE type;
  char *text;
  void *submenu;
  void (*function)(struct MENU_ELEMENT *e);
};


struct MENU_ELEMENT *current_menu;
struct MENU_ELEMENT *last_menu;
struct MENU_ELEMENT *the_home_menu;
unsigned int menu_selection = 0;
unsigned int menu_size = 0;

#define MAX_LISTFILES 7
#define MAX_NAME 20

MENU_ELEMENT listfiles[MAX_LISTFILES+1];
int num_listfiles;
char names[MAX_LISTFILES][MAX_NAME];
char selected_file[MAX_NAME+1];
char current_file[MAX_NAME+1];

// Where the received data goes
char stored_bytes[MAX_BYTES] = "01234567890";

int stored_bytes_index = 0;

// How many bytes in the buffer. We have a default for testing without a Microtan
int bytecount = 24;

// communication with ISRs

volatile int copied_word = 0;
volatile int word_bits = 0;
volatile int copied_word_bits = 0;

volatile int new_word = 0;

#define BUF_LEN 5000

volatile int buf_in = 0;
volatile uint8_t state_buffer[BUF_LEN];
volatile int word_buffer[BUF_LEN];
volatile uint8_t blen_buffer[BUF_LEN];
volatile int num_data_words = 0;

// This is where data words appear
#define NUM_DATA_WORDS  320

//volatile int data_word_in_index = 0;
volatile int data_word_tx_index = 0;
volatile int data_word_out_index = 0;

volatile int data_words[NUM_DATA_WORDS];

// We build the byte packet in this int, it can be longer than
// 8 bits as it has the start bit, stop bit and parity if we have it on

volatile unsigned int capture_bits_len = 0;
volatile unsigned int capture_bits = 0xffff;

// Flag that indicates we are looking for a start bit
volatile int waiting_for_start = 1;

#define START_BIT 2

// Flag that indicates we have a bit or bits
volatile int got_bit = 0;

// How many bits we have received
volatile int number_of_bits = 0;

// Bit value of the N bits
volatile int bit_value = 0;

// Bit period in us
// default to 9600
//volatile int bit_period = 833;
volatile int bit_period = 102;

////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Prototypes
//

void but_ev_null();
void but_ev_up();
void but_ev_down();
void but_ev_select();


////////////////////////////////////////////////////////////////////////////////
// reverses a byte or nibble
int reverse(int x, int n)
{
  int i;
  int r = 0;
  
  for(i=0; i<n; i++)
    {
      r<<=1;
      r+= (x & 1);
      x>>=1;
    }
  
  return(r);
}

////////////////////////////////////////////////////////////////////////////////
// returns the correct parity bit for the word

int correct_parity_of(int byte)
{
  int i;
  int p = 0;

  for(i=0; i< 8; i++)
    {
      p += ((byte & (1 << i)) >> i);
    }

  return( p % 2);
}

////////////////////////////////////////////////////////////////////////////////
//
// get data byte from a data_words entry

int get_data_words_byte(int i)
{
  return( reverse((data_words[i] & 0x7F80) >> 7, 8));
}

////////////////////////////////////////////////////////////////////////////////
//
// Allow interaction with serial monitor
//

// Commands
int indx = 0;

void cmd_next(String cmd)
{
  indx++;
  
}

void cmd_prev(String cmd)
{
  indx--;
}
		     
void cmd_index(String cmd)
{
  String arg;
  int i;
  char line[40];
  
  Serial.println("INDEX");
  arg = cmd.substring(1);
  
  Serial.println(arg);
  
  indx = arg.toInt();
  
  int data = 0;
  data    = (data_words[i] & 0x7F80) >> 7;
  sprintf(line, "DATA: %02X: %02X", indx, data_words[i]);
  Serial.println(line);
}

// Modify the buffer
void cmd_modify(String cmd)
{
  String arg;
  char line[40];
  
  Serial.println("MOD");
  arg = cmd.substring(1);

  if( indx <= MAX_BYTES )
    {
      // Get new value
      int data = arg.toInt();
      int word = data_words[indx];

      Serial.println(data);
      // Clear data bits
      word &= ~0x7F80;
      word |= reverse(data,8) << 7;
      data_words[indx] = word;

      // New data byte inserted.
      // We fix parity
      data_words[indx] |= (correct_parity_of(data) << 6);

      sprintf(line, "%04d:%02X", indx, data_words[indx]);
      Serial.println(line);
    }
  
}

////////////////////////////////////////////////////////////////////////////////
//
// Displays the captured data buffer
//
//
////////////////////////////////////////////////////////////////////////////////

#define DISPLAY_COLS 16

void cmd_display(String cmd)
{
  int i;
  int address = 0;
  
  char ascii[DISPLAY_COLS+2];
  char c[2];
  char line[50];
  
  int ascii_i = 0;
  ascii[0] ='\0';
  
  Serial.print("Buffer Count:");
  Serial.print(buf_in);
  //  Serial.print("  Word in:");
  //Serial.print(data_word_in_index);
  Serial.print("  Word out:");
  Serial.print(data_word_out_index);
  Serial.print("  TX out:");
  Serial.println(data_word_tx_index);
  Serial.print(" State:");
  Serial.print(ce_isr_state);
  Serial.print(" NumHdr:");
  Serial.print(num_header_words);
  Serial.print("  Num data words:");
  Serial.print(num_data_words);

  Serial.println("");

  char tag_decode[40];
  char state_decode[40];

  for(i=0; i<buf_in; i++)
    {
      sprintf(state_decode, "%12s", state_decode_list[state_buffer[i]]);
      if( (word_buffer[i] & 0xff00) != 0x1000 )
	{
	  sprintf(line, " %02X (%d bits) S%d(%s)", word_buffer[i], blen_buffer[i], state_buffer[i], state_decode);
	  Serial.println(line);
	}
      else
	{
	  switch(word_buffer[i])
	    {
	      
	    case 0x10CC:
	      sprintf(tag_decode, "%19s%01X", "OP ISR::", blen_buffer[i]);
	      break;

	    case 0x10CE:
	      sprintf(tag_decode, "%19s%01X", "CE ISR::", blen_buffer[i]);
	      break;

	    case 0x10BB:
	      sprintf(tag_decode, "%19s%01X", "OP change:", blen_buffer[i]);
	      break;

	    case 0x105E:
	      sprintf(tag_decode, "%16s%04X", "Send data:", blen_buffer[i]);
	      break;
	      
	    case 0x10C1:
	      sprintf(tag_decode, "%20s", "clk");
	      break;

	    case 0x10E0:
	      sprintf(tag_decode, "%20s", "End of Packet");
	      break;

	    case 0x10E1:
	      switch(blen_buffer[i])
		{
		case 0x1919:
		  sprintf(tag_decode, "%20s", "Zero bit packet");
		  break;
		  
		case 0:
		  sprintf(tag_decode, "%20s", "End of packet");
		  break;
		}

	      break;

	      
	    case 0x1050:
	      switch(blen_buffer[i])
		{
		case 0x0:
		  sprintf(tag_decode, "%20s", "Set Data Up");
		  break;
		}

	      break;

	    case 0x1051:
	      switch(blen_buffer[i])
		{
		case 0x111:
		  sprintf(tag_decode, "%20s", "Send All Done");
		  break;
		default:
		  sprintf(tag_decode, "%20s", "Send All Done");
		  
		break;
		}

	      break;

	    case 0x1055:
	      sprintf(tag_decode, "%20s", "Start of Packet");
	      break;

	    default:
	      sprintf(tag_decode, "%20s", "???");
	      break;
	    }
	  
	  sprintf(line, "T%04X (%s) %04X S%d(%s)", word_buffer[i], tag_decode, blen_buffer[i], state_buffer[i], state_decode);
	  Serial.println(line);
	}
    }


#if 1
  // These are the captured data words. We decode these to make the dump easier to read
  int start = 0;
  int stop = 0;
  int parity = 0;
  int xxx = 0;
  int data = 0;
  int word = 0;

  Serial.println("     00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
  
  for(i=0; i<NUM_DATA_WORDS; i++)
    {
      //sprintf(line, " %d %04X ", i, data_words[i]);
      //Serial.print(line);

      // Decode to get the data bits
      word    = data_words[i];
      start   = (word & 0x8000) >> 16;
      data    = (word & 0x7F80) >> 7;
      parity  = (word & 0x0040) >> 6;
      stop    = (word & 0x0030) >> 4;
      xxx     = (word & 0x000F) >> 0;

      if( (i%16) == 0 )
	{
	  Serial.println("");
	  sprintf(line, "%04X:", i);
	  Serial.print(line);
	}
      
      sprintf(line, "%02X ", reverse(data,8));
      Serial.print(line);

    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
// Fix the parity bits
//
//

void cmd_fix_parity(String cmd)
{
  int i;
  
  int start = 0;
  int stop = 0;
  int parity = 0;
  int xxx = 0;
  int data = 0;
  int word = 0;
  char line[40];

  for(i=0; i<NUM_DATA_WORDS; i++)
    {
      sprintf(line, " %d %04X ", i, data_words[i]);
      Serial.print(line);

      // Decode to get the data bits
      word    = data_words[i];
      start   = (word & 0x8000) >> 16;
      data    = (word & 0x7F80) >> 7;
      parity  = (word & 0x0040) >> 6;
      stop    = (word & 0x0030) >> 4;
      xxx     = (word & 0x000F) >> 0;

      sprintf(line, " %d %02X %d=%d %01X %01X ", start, reverse(data,8), parity, correct_parity_of(data), stop, xxx);
      Serial.println(line);

    }
}

// Clear the buffer


void cmd_clear(String cmd)
{
  int i;
  
  buf_in = 0;
  num_data_words = 0;
  num_header_words = 0;
  
  for(i=0; i<NUM_DATA_WORDS; i++)
    {
      data_words[i] = HEADER_WORD;
    }
  
  //  data_word_in_index = 0;
}

void cmd_reset_trace(String cmd)
{
  buf_in = 0;
}


// Close the capture file
void cmd_close(String cmd)
{
  dumpfile.close();
}


// Deletes a file
void cmd_deletefile(String cmd)
{
  String arg;
  
  arg = cmd.substring(strlen("delete "));

  Serial.print("Deleting file '");
  Serial.print(arg);
  Serial.println("'");
  
  SD.remove(arg);
}

// read the file with the given name into the buffer

void core_read(String arg, boolean oled_nserial)
{
  if( oled_nserial )
    {
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("Reading file ");
      display.println(arg.c_str());
      display.display();
      delay(1000);
    }
  else
    {
      Serial.print("Reading file '");
      Serial.print(arg);
      Serial.println("'");
    }
  
  myFile = SD.open(arg);

  if (myFile)
    {
#define MLI 10      
      char line[MLI];
      int li = 0;
      char ch;
      
      // Read from the file and store it in the buffer
      num_data_words = 0;
      
      while (myFile.available())
	{
	  // Read characters until newline
	  ch = myFile.read();

	  if( ch == '\n' )
	    {
	      line[li++] = '\0';
	      Serial.println(line);
	      sscanf(line, "%X", &(data_words[num_data_words++]));
	      li = 0;
	    }
	  else
	    {
	      line[li++] = ch;
	      if( li > MLI )
		{
		  li = MLI;
		}
	    }
	  

	  if( num_data_words >= NUM_DATA_WORDS )
	    {
	      num_data_words = NUM_DATA_WORDS;
	    }
	}
      
      // close the file:
      myFile.close();

      if ( oled_nserial )
	{
	  display.print(num_data_words);
	  display.println(" bytes read");
	  display.display();
	  delay(3000);
	}
      else
	{
	  Serial.print(num_data_words);
	  Serial.println(" bytes read.");
	}
    }
  else
    {
      // if the file didn't open, print an error:
      if( oled_nserial )
	{
	  display.println("Error opening");
	  display.println(arg.c_str());
	  display.display();
	  delay(2000);
	}
      else
	{
	  Serial.print("Error opening ");
	  Serial.println(arg);
	}
    }
}

void cmd_readfile(String cmd)
{
  String arg;
  
  arg = cmd.substring(strlen("read "));

  core_read(arg, false);
}

void cmd_listfiles(String cmd)
{
  File dir;
  
  dir = SD.open("/");

  // return to the first file in the directory
  dir.rewindDirectory();
  
  while (true) {
    
    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }

    Serial.print(entry.name());

    if (entry.isDirectory())
      {
	Serial.println("/");
      }
    else
      {
	// files have sizes, directories do not
	Serial.print("\t\t");
	Serial.println(entry.size(), DEC);
      }
    entry.close();
  }

  dir.close();
}

void cmd_initsd(String cmd)
{
  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialisation failed!");
  }
  else
    {
      Serial.println("SD card initialised.");
    }

}


// Writes the buffer to a file.
// Deletes any file that exists with the same name so that the resulting
// file is the same size as the buffer

boolean led_state = true;
void core_writefile(boolean oled_nserial)
{
  char filename[20] = "nofile";
  int i;

  if( led_state )
    {
      digitalWrite(LEDPin, HIGH);
    }
  else
    {
      digitalWrite(LEDPin, LOW);
    }
  
  led_state = !led_state;
  
  sprintf(filename, "%c%s.DAT", filetype, filenum);
  
  if( oled_nserial )
    {
      display.clearDisplay();
      display.setCursor(0,0);
      display.println("");
      display.print("Writing ");
      display.print(" ");
      display.println();
      display.print("'");
      display.print(filename);
      display.print("'");
      display.display();
    }
  else
    {
      Serial.println("");
      Serial.print("Writing ");
      Serial.print(num_data_words);
      Serial.print(" bytes to '");
      Serial.print(filename);
      Serial.print("'");
      Serial.println("");
    }
  
  // Delete so we have no extra data if the file is currently larger than the buffer
  SD.remove(filename);
  
  // Open file for writing
  myFile = SD.open(filename, FILE_WRITE);

  if( myFile )
    {
      // Write data
      for(i=0; i<num_data_words; i++)
	{
	  myFile.println(data_words[i], HEX);
	}
      
      myFile.close();

      if( oled_nserial )
	{
	  display.setCursor(0,3*8);
	  display.print(num_data_words);
	  display.println(" bytes written");
	  display.display();
	}
      else
	{
	  Serial.print(num_data_words);
	  Serial.println(" bytes written");
	}
    }
  else
    {
      if(oled_nserial)
	{
	  display.println("Could not open file");
	  display.display();

	}
      else
	{
	  Serial.println("Could not open file");
	}
    }

  if( oled_nserial )
    {
      delay(2000);
    }
}

void cmd_port(String cmd)
{
  int pb;

  while(1)
    {
      pb = GPIOB->IDR;
      Serial.println(pb, HEX);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// Decode and display the data words as memories
//

// returns a decoded memory of the form:
// -1.23456789E-12
//
// as  string

char decoded_memory[40];
boolean upper_digit = true;
int digit_i;

// Initialises digit retrieval
void start_next_digit(int data_words_i)
{
  digit_i = data_words_i;
  upper_digit = false;
}

// get the next digit from a memory as  character
char next_digit()
{
  int dv;
  char dc;
  
  if( upper_digit )
    {
      dv = ((get_data_words_byte(digit_i) & 0xF0) >> 4);      
      upper_digit = false;

    }
  else
    {
      dv = ((get_data_words_byte(digit_i) & 0x0F) >> 0);
      upper_digit = true;
      digit_i--;
    }

  switch(dv)
    {
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
      dc = dv + '0';
      break;

    case 10:
      dc = 'o';
      break;
      
    case 11:
      dc = 'P';
      break;
      
    case 12:
      dc = 'C';
      break;
      
    case 13:
      dc = 'E';
      break;
      
    case 14:
      dc = '-';
      break;
      
    case 15:
      dc = ' ';
      break;
      
    default:
      dc = '?';
      break;
    }

  return (dc);
}

char *decode_memory(int data_word_i)
{
  char memory_str[40];
  int i;
  int j;
  int exponent;
  char exp[5];
  
  memory_str[0] = ' ';
  
  start_next_digit(data_word_i);
  for(j=1, i=data_word_i+13; i>=data_word_i; i--, j++)
    {
      memory_str[j] = next_digit();
    }
  
  exponent  = ((get_data_words_byte(digit_i) & 0xF0) >> 4) * 10;
  exponent += ((get_data_words_byte(digit_i) & 0x0F) >> 0) * 1;     

  sprintf(exp, "E%02d", exponent);

  memory_str[j] = '\0';

  strcat(memory_str, exp);
  
  strcpy(decoded_memory, memory_str);
  return(decoded_memory);  
}

// returns the name of memory N
char m_name[5];

char *memory_name(int i)
{
  if( i == 0 )
    {
      return("0F");
    }

  if( (i >= 1) && (i <=10) )
    {
      sprintf(m_name, "%02d", 9-(i-1));
      return(m_name);
    }

  if( i == 11 )
    {
      return("1F");
    }

  if( (i >= 12) && (i <=21) )
    {
      sprintf(m_name, "%02d", 29-(i-2));
      return(m_name);
    }
  
  return("??");
}


// Decode the data words
void cmd_disp_mem(String cmd)
{
  char line[40];
  int a = ((get_data_words_byte(0) & 0x0F) >> 0);
  int b = ((get_data_words_byte(0) & 0xF0) >> 4);
  int c = ((get_data_words_byte(1) & 0x0F) >> 0);
  int d = ((get_data_words_byte(1) & 0xF0) >> 4);
  
  int filenum = a + b*10 + c*100;
  int filetype = d;
  char *filetype_s;
  
  switch(filetype)
    {
    case 15:
      filetype_s = "Memory";
      break;
    case 11:
      filetype_s = "Program";
      break;
    default:
      filetype_s = "Unknown";
      break;
    }
  sprintf(line, "\nType:%s (%d) Number:%03d", filetype_s, filetype, filenum);
  Serial.println(line);

  int mem_num = 0;
  
  for(int i=2; i<2+22*8;i+=MEMORY_LENGTH)
    {
      sprintf(line, "%s: %s", memory_name((i-2)/MEMORY_LENGTH), decode_memory(i+7));
      Serial.println(line);
    }

}

void cmd_writefile(String cmd)
{
  core_writefile(false);
}

const int NUM_CMDS = 16;

String cmd;
struct
{
  String cmdname;
  CMD_FPTR   handler;
} cmdlist [] =
  {
    {"mem",         cmd_disp_mem},
    {"m",           cmd_modify},
    {"c",           cmd_clear},
    {"rt",          cmd_reset_trace},
    {"d",           cmd_display},
    {"parity",      cmd_fix_parity},
    {"next",        cmd_next},
    {"prev",        cmd_prev},
    {"i",           cmd_index},
    {"close",       cmd_close},
    {"write",       cmd_writefile},
    {"list",        cmd_listfiles},
    {"initsd",      cmd_initsd},
    {"help",        cmd_help},
    {"read",        cmd_readfile},
    {"delete",      cmd_deletefile},
    {"port",        cmd_port},
    {"-",           cmd_null},
  };


void cmd_null(String cmd)
{
  Serial.println("Null cmd");
}

void cmd_help(String cmd)
{
  int i;

#if 1
  for(i=0; cmdlist[i].handler != cmd_null; i++)
#else
    for(i=0; i<NUM_CMDS; i++)
#endif
    {
      Serial.println(cmdlist[i].cmdname);
    }
}

void run_monitor()
{
  char c;
  int i;
  String test;
  
  if( Serial.available() )
    {
      //      Serial.println("Monitor process started");
      c = Serial.read();

      switch(c)
	{
	case '\r':
	case '\n':
	  // We have a command, process it
	  for(i=0; i<NUM_CMDS; i++)
	    {
	      test = cmd.substring(0, (cmdlist[i].cmdname).length());
	      if( cmdlist[i].cmdname == "-" )
		{
		  break;
		}
	      
	      if( test == cmdlist[i].cmdname )
		{
		  (*(cmdlist[i].handler))(cmd);
		  break;
		}
	    }

	  cmd = "";
	  break;

	default:
	  cmd += c;
	  break;
	}
      //Serial.println("Monitor process completed");
    }
}

// The switch menu/OLED display system
void to_back_menu(struct MENU_ELEMENT *e)
{
  menu_selection = 0;
  current_menu = last_menu;
  draw_menu(current_menu, true);
}

void to_home_menu(struct MENU_ELEMENT *e)
{
  menu_selection = 0;
  current_menu = the_home_menu;
  draw_menu(current_menu, true);
}

// Sets PIO to all inputs 
void button_all_inputs(MENU_ELEMENT *e)
{

  Serial.print("Interface now all inputs");

  display.setTextSize(1);      
  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Interface all inputs");
  display.display();
  delay(2000);

  draw_menu(current_menu, true);
}


void button_clear(MENU_ELEMENT *e)
{
  bytecount = -1;

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Buffer Cleared");
  display.display();
  
  delay(3000);
  draw_menu(current_menu, true);
}

void button_write(MENU_ELEMENT *e)
{
  core_writefile(true);

  delay(3000);
  draw_menu(current_menu, true);
}


// The button function puts up to the first 7 files on screen then set sup a button handler
// which will display subsequent pages.
// We use the menu structures to display the names and allow selection

// File selected
void button_select_file(MENU_ELEMENT *e)
{
  strcpy(selected_file, e->text);

  // Back a menu
  to_back_menu(e);
  
}


// Allow a file to be selected. The file name will be stored for a later 'read' command.

int file_offset = 0;

#define FILE_PAGE 7

void but_ev_file_up()
{
#if DEBUG
  Serial.print("Before-menu_selection: ");
  Serial.print(menu_selection);
  Serial.print("file_offset: ");
  Serial.println(file_offset);
#endif
  
  if( menu_selection == 0 )
    {
      if( file_offset == 0 )
	{
	  // Don't move
	}
      else
	{
	  // Move files back one
	  file_offset--;
	}
    }
  else
    {
      // Move cursor up
      menu_selection--;
    }

#if DEBUG
  Serial.print("Before-menu_selection: ");
  Serial.print(menu_selection);
  Serial.print("file_offset: ");
  Serial.println(file_offset);
#endif
  
  button_list(NULL);

  if( menu_selection >= menu_size )
    {
      menu_selection = menu_size - 1;
    }
}

void but_ev_file_down()
{
#if DEBUG  
  Serial.print("Before-menu_selection: ");
  Serial.print(menu_selection);
  Serial.print("file_offset: ");
  Serial.println(file_offset);
#endif
  
  // Move cursor down one entry
  menu_selection++;
  
  // Are we off the end of the menu?
  if( menu_selection == menu_size )
    {
      // 
      if( menu_selection >= MAX_LISTFILES,1 )
	{
	  menu_selection--;

	  // If the screen is full then we haven't reached the end of the file list
	  // so move the list up one
	  if( menu_size == MAX_LISTFILES )
	    {
	      file_offset++;
	    }
	}
    }

  // We need to make sure cursor is on menu
  if( menu_selection >= menu_size )
    {
      menu_selection = menu_size - 1;
    }

#if DEBUG  
  Serial.print("Before-menu_selection: ");
  Serial.print(menu_selection);
  Serial.print("file_offset: ");
  Serial.println(file_offset);
  Serial.print("menu_size: ");
  Serial.println(menu_size);
#endif
  
  button_list(NULL);
}

// Store file name and exit menu
// File can be read later

void but_ev_file_select()
{
  strcpy(current_file, listfiles[menu_selection].text);
  file_offset = 0;

  display.clearDisplay();
  display.setCursor(0,0);
  display.println("Selected file");
  display.print(current_file);
  display.display();
  delay(3000);

  menu_selection = 0;
  to_home_menu(NULL);
  
  buttons[0].event_fn = but_ev_up;
  buttons[1].event_fn = but_ev_down;
  buttons[2].event_fn = but_ev_select;
}

void button_to_home(MENU_ELEMENT *e)
{
  to_home_menu(NULL);
}

void button_list(MENU_ELEMENT *e)
{
  File dir;
  int file_n = 0;
  num_listfiles = 0;
  int i;

  Serial.println("button_list");
  dir = SD.open("/");

  // return to the first file in the directory
  dir.rewindDirectory();
  
  while (num_listfiles < MAX_LISTFILES) {

    File entry =  dir.openNextFile();

    if (! entry) {
      // no more files
      // terminate menu
      listfiles[num_listfiles].text = "";
      listfiles[num_listfiles].type = MENU_END;
      listfiles[num_listfiles].submenu = NULL;
      listfiles[num_listfiles].function = button_select_file;
      entry.close();
      break;
    }

    
    // We don't allow directories and don't ount them
    if (entry.isDirectory())
      {
      }
    else
      {
#if DEBUG	
	Serial.print("BList-file_n:");
	Serial.print(file_n);
	Serial.print(entry.name());
	Serial.print("  num_listfiles:");
	Serial.println(num_listfiles);
#endif
	// Create a new menu element
	// we also don't want to display anything before the offset
	if( file_n >= file_offset )
	  {
	    strncpy(&(names[num_listfiles][0]), entry.name(), MAX_NAME);
	    //	display.println(&(names[nu);
	    listfiles[num_listfiles].text = &(names[num_listfiles][0]);
	    listfiles[num_listfiles].type = BUTTON_ELEMENT;
	    listfiles[num_listfiles].submenu = NULL;
	    listfiles[num_listfiles].function = button_select_file;
	    
	    num_listfiles++;
	  }
	// Next file
	file_n++;

      }
    entry.close();
    
  }

  dir.close();

  // terminate menu
  listfiles[num_listfiles].text = "";
  listfiles[num_listfiles].type = MENU_END;
  listfiles[num_listfiles].submenu = NULL;
  listfiles[num_listfiles].function = button_select_file;

  // We know how big the menu is now
  if( num_listfiles != 0 )
    {
      menu_size = num_listfiles;
    }

  // Button actions modified
  buttons[0].event_fn = but_ev_file_up;
  buttons[1].event_fn = but_ev_file_down;
  buttons[2].event_fn = but_ev_file_select;

  // Set up menu of file names
  current_menu = &(listfiles[0]);
  draw_menu(current_menu, false);

}


#define COLUMNS 5
#define PAGE_LENGTH 30

// Display the buffer

int display_offset = 0;

void but_page_up()
{
  if( display_offset > PAGE_LENGTH )
    {
      display_offset -= PAGE_LENGTH;
    }
  else
    {
      display_offset = 0;
    }
  button_display(NULL);
}

void but_page_down()
{
  display_offset += PAGE_LENGTH;
  
  if( display_offset >= bytecount )
    {
      display_offset = bytecount-PAGE_LENGTH;
    }

  if( display_offset < 0 )
    {
      display_offset = 0;
    }
  
  button_display(NULL);
}

void but_page_exit()
{
  display_offset = 0;
  draw_menu(current_menu, true);

  buttons[0].event_fn = but_ev_up;
  buttons[1].event_fn = but_ev_down;
  buttons[2].event_fn = but_ev_select;

}

void button_display(MENU_ELEMENT *e)
{
  int i;
  char ascii[17];
  char c[5];
  
  int ascii_i = 0;

  display.clearDisplay();
  
  for(i=0; (i<bytecount) && (i<PAGE_LENGTH); i++)
    {
      if( isprint(stored_bytes[i]) )
	{
	  sprintf(ascii, "%c", stored_bytes[i+display_offset]);
	}
      else
	{
	  sprintf(ascii, ".");
	}
      
      sprintf(c,     "%02X",  stored_bytes[i+display_offset]);

      display.setCursor(6*15+(i%COLUMNS)*1*6, 8*(i/COLUMNS+1));
      display.println(ascii);
      display.setCursor(10*0+(i%COLUMNS)*2*8, 8*(i/COLUMNS+1));
      display.print(c);

    }

  // Drop into page up and down and exit buttoin handlers
  buttons[0].event_fn = but_page_up;
  buttons[1].event_fn = but_page_down;
  buttons[2].event_fn = but_page_exit;

  display.display();
}


void button_send(MENU_ELEMENT *e)
{
  //  send_databytes(true);
  draw_menu(current_menu, true);
}

/* read the current file from SD card */

void button_read(MENU_ELEMENT *e)
{
  core_read(current_file, true);

  draw_menu(current_menu, true);
}


struct MENU_ELEMENT home_menu[] =
  {
    {BUTTON_ELEMENT, "List",                       NULL,     button_list},
    {BUTTON_ELEMENT, "Clear",                      NULL,     button_clear},
    {BUTTON_ELEMENT, "Send",                       NULL,     button_send},
    {BUTTON_ELEMENT, "Write",                      NULL,     button_write},
    {BUTTON_ELEMENT, "Display",                    NULL,     button_display},
    {BUTTON_ELEMENT, "Read",                       NULL,     button_read},
    {MENU_END,       "",                           NULL,     NULL},
  };

// Clear flag indicates whether we redraw the menu text and clear the screen. Or not.

void draw_menu(struct MENU_ELEMENT *e, boolean clear)
{
  int i = 0;
  char *curs = " ";
  char etext[20];

  Serial.println("draw_menu");
  // Clear screen
  if(clear,1)
    {
      display.clearDisplay();
    }
  
  while( e->type != MENU_END )
    {
      sprintf(etext, " %-19s", e->text);
      
      switch(e->type)
	{
	case BUTTON_ELEMENT:
	  display.setCursor(0, i*8);
	  //display.printChar(curs);
	  if( clear,1 )
	    {
	      display.println(etext);
	    }
	  break;

	case SUB_MENU:
	  display.setCursor(0, i*8);
	  //display.printChar(curs);
	  if ( clear,1 )
	    {
	      display.println(etext);
	    }
	  break;
	}
      e++;
      i++;
    }
  
  menu_size = i;

#if DEBUG
  Serial.print("menu_size:");
  Serial.println(menu_size);
#endif
  
  // Blank the other entries
  //make sure menu_selection isn't outside the menu
  if( menu_selection >= menu_size )
    {
      menu_selection = menu_size-1;
    }

  for(; i<MAX_LISTFILES; i++)
    {
      display.setCursor(0, i*8);
      display.println("               ");
    }

  for(i=0;i<menu_size;i++)
    {
      if( i == menu_selection )
	{
	  curs = ">";	  
	}
      else
	{
	  curs = " ";
	}

      display.setCursor(0, i*8);
      display.print(curs);
    }
  display.display();
  Serial.println("Draw_menu exit");
}

// Null button event function
void but_ev_null()
{ 
}

void but_ev_up()
{
  if( menu_selection == 0 )
    {
      menu_selection = menu_size - 1;
    }
  else
    {
      menu_selection = (menu_selection - 1) % menu_size;
    }
  
  draw_menu(current_menu, false);
}

void but_ev_down()
{

  menu_selection = (menu_selection + 1) % menu_size;

  draw_menu(current_menu, false);
}

void but_ev_select()
{
  struct MENU_ELEMENT *e;
  int i = 0;
  
  // Do what the current selection says to do
  for(e=current_menu, i=0; (e->type != MENU_END); i++, e++)
    {
      if( i == menu_selection )
	{
	  switch(e->type)
	    {
	    case SUB_MENU:
	      current_menu = (MENU_ELEMENT *)e->submenu;
	      draw_menu(current_menu, true);
	      break;
	      
	    default:
	      // Do action
	      (e->function)(e);
	      break;
	    }
	}
    }
}

#if 0
void init_buttons()
{
  Serial.println("Init buttons");
  for(int i=0; i<NUM_BUTTONS; i++)
    {
      buttons[i].count = 0;
      buttons[i].pressed = false;
      buttons[i].last_pressed = false;
      buttons[i].event_fn = but_ev_null;
    }

  buttons[0].event_fn = but_ev_up;
  buttons[1].event_fn = but_ev_down;
  buttons[2].event_fn = but_ev_select;
}

void update_buttons()
{
  for(int i=0; i<NUM_BUTTONS; i++)
    {
      if( digitalRead(but_pins[i]) == LOW )
	{
	  if( buttons[i].count < MAX_BUT_COUNT )
	    {
	      buttons[i].count++;
	      if( buttons[i].count == MAX_BUT_COUNT )
		{
		  // Just got to MAX_COUNT
		  buttons[i].pressed = true;
		  Serial.println("Press");
		}
	    }
	}
      else
	{
	  if( buttons[i].count > 0 )
	    {
	      buttons[i].count--;
	      
	      if( buttons[i].count == 0 )
		{
		  // Just got to zero
		  buttons[i].pressed = false;
		}
	    }
	}
      
      // If button has gone from pressed to not pressed then we treat that as a key event
      if( (buttons[i].last_pressed == true) && (buttons[i].pressed == false) )
	{
	  Serial.println("Call ev");
	  (buttons[i].event_fn)();
	}

      buttons[i].last_pressed = buttons[i].pressed;
    }
}
#endif
  
//HardwareSerial Serial1(PA10, PA9);
//HardwareSerial Serial2(PB11, PB10);


void setup() {


  //  Wire2.begin();

#if ENABLE_OLED_SETUP
  Wire.setSDA(PB11);
  Wire.setSCL(PB10);

  
  Wire.begin();
#endif
  pinMode(SPPin, INPUT);

  // Turn LED on
  pinMode(LEDPin, OUTPUT);
  digitalWrite(LEDPin, LOW);
  
  // Make data line open drain output. We can read from it when set to
  // high as it is just a pull-up. Not having to call
  // pinMode saves us cycles

  digitalWrite(D3Pin, HIGH);
  pinMode(D3Pin, OUTPUT_OPEN_DRAIN);
  pinMode(PA0, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PA2, INPUT);
  
  pinMode(statPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //  digitalWrite(dataPin, LOW);
  

  // put your setup code here, to run once:
#if ENABLE_SERIAL
  Serial.begin(2000000);
#endif
  //  Serial2.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Serial.println("");
  Serial.println("");
  Serial.println("fx502p Gadget");
  Serial.println("");
  Serial.println("OLED OK.");
  
  // Clear the buffer
  display.clearDisplay();
  Serial.print("\nInitializing SD card...");
  display.setTextSize(1);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(F("fx502p Gadget"));
  display.display();
  
  Serial.print("\nInitializing SD card...");

#if 0  
  // we'll use the initialization code from the utility libraries
  // since we're just testing if the card is working!
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    Serial.println("* is your wiring correct?");
    Serial.println("* did you change the chipSelect pin to match your shield or module?");

    display.println("SD Fail");
    display.display();
  } else {
    Serial.println("Wiring is correct and a card is present.");
    display.println("SD OK");
    display.display();
    delay(2000);

  }

  // print the type of card
  Serial.println();
  Serial.print("Card type:         ");
  switch (card.type()) {
  case SD_CARD_TYPE_SD1:
    Serial.println("SD1");
    break;
  case SD_CARD_TYPE_SD2:
    Serial.println("SD2");
    break;
  case SD_CARD_TYPE_SDHC:
    Serial.println("SDHC");
    break;
  default:
    Serial.println("Unknown");
  }
  // Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
  if (!volume.init(card)) {
    Serial.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    while (1);
  }

  Serial.print("Clusters:          ");
  Serial.println(volume.clusterCount());
  Serial.print("Blocks x Cluster:  ");
  Serial.println(volume.blocksPerCluster());

  Serial.print("Total Blocks:      ");
  Serial.println(volume.blocksPerCluster() * volume.clusterCount());
  Serial.println();

  // print the type and size of the first FAT-type volume
  uint32_t volumesize;
  Serial.print("Volume type is:    FAT");
  Serial.println(volume.fatType(), DEC);

  volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
  volumesize *= volume.clusterCount();       // we'll have a lot of clusters
  volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB)
  Serial.print("Volume size (Kb):  ");
  Serial.println(volumesize);
  Serial.print("Volume size (Mb):  ");
  volumesize /= 1024;
  Serial.println(volumesize);
  Serial.print("Volume size (Gb):  ");
  Serial.println((float)volumesize / 1024.0);
#else
    
  if (!SD.begin(chipSelect)) {
    //if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    Serial.println("SD Card initialisation failed!");
    display.println("SD Fail");
    display.display();
    //    delay(2000);
  }
  else
    {
      Serial.println("SD card initialised.");
      display.println("SD OK");
      display.display();
      //delay(2000);
    }

#endif
  
  bytecount = strlen(&(stored_bytes[0]));
  current_menu = &(home_menu[0]);
  last_menu = &(home_menu[0]);
  the_home_menu = last_menu;

#if 0
  to_home_menu(NULL);
#endif
  //  init_buttons();

  // We want an interrupt on rising edge of clock
  attachInterrupt(digitalPinToInterrupt(SPPin), spISR,  CHANGE);
  attachInterrupt(digitalPinToInterrupt(CEPin), ceISR,  CHANGE);
  //  attachInterrupt(digitalPinToInterrupt(OPPin), opISR,  CHANGE);
    
  //  attachInterrupt(digitalPinToInterrupt(SIOTXDPin), highISR, RISING);

  // Read a file in for testing
  core_read("P123.DAT", true);
}


void buffer_point(int captured_word, int word_bits)
{
  if( buf_in < BUF_LEN )
    {
      word_buffer[buf_in]  = captured_word;
      blen_buffer[buf_in]  = word_bits;
      state_buffer[buf_in] = ce_isr_state;
      buf_in++;
    }
}

// Check the file we are about to write for meta commands
//
// If exponent is 47 then use first 3 digits as the current file
// to load for memory LOAD commands
// If exponent is 48 then use first 3 digits for the file number
// of the file to load for program LOAD commands
//
// To allow more than 1000 file numbers we can have a 'bank' number
// that is set up with a meta command
//
// We can transform numbers into special characters

void meta_check()
{
  char fn[4] = "...";
  char filename[20];
  
  // Is the exponent a special one?
  if( (data_words[0] == 0x0030) &&
      (data_words[1] == 0x07b0) &&
      (data_words[2] == 0x7130) )
    {
      // Read file into memory read for a LOAD
      fn[1] = (unsigned char)(((data_words[8] >> 7) & 0x0F)>>0);
      fn[2] = (unsigned char)(((data_words[8] >> 7) & 0xF0)>>4);
      fn[0] = (unsigned char)(((data_words[9] >> 7) & 0xF0)>>4);
      fn[0] = reverse(fn[0], 4);
      fn[1] = reverse(fn[1], 4);
      fn[2] = reverse(fn[2], 4);
      fn[0] += '0';
      fn[1] += '0';
      fn[2] += '0';
      fn[3] = '\0';

      sprintf(filename, "P%s.DAT", fn);
      core_read(filename, true);
    }

  if( (data_words[0] == 0x0030) &&
      (data_words[1] == 0x07b0) &&
      (data_words[2] == 0x0930) )
    {
      // Read file into memory read for a LOAD
      fn[1] = (unsigned char)(((data_words[8] >> 7) & 0x0F)>>0);
      fn[2] = (unsigned char)(((data_words[8] >> 7) & 0xF0)>>4);
      fn[0] = (unsigned char)(((data_words[9] >> 7) & 0xF0)>>4);
      fn[0] = reverse(fn[0], 4);
      fn[1] = reverse(fn[1], 4);
      fn[2] = reverse(fn[2], 4);
      fn[0] += '0';
      fn[1] += '0';
      fn[2] += '0';
      fn[3] = '\0';

      sprintf(filename, "M%s.DAT", fn);
      core_read(filename, true);
    }
}

////////////////////////////////////////////////////////////////////////////////
//
// Check for meta information
//
// We need a way to specify which file should be sent on a LOAD
// This is done using the inv SAVE inv EXE file. This saves the X register
// We use the 
int y = 32;

void loop() {
  int i;
  char c;

#if 0
  loopcnt++;
  
  if( (loopcnt % 500000) == 0 )
    {
      Serial.println("Loop");
    }
#endif
  
#if DISABLE_MONITOR_DURING_RX  
  if( monitor_enabled )
    {
      run_monitor();
    }
#else
  run_monitor();
#endif
  
#if 1
  if( cis_flag_event )
    {
      cis_flag_event = false;

      // Get file number from first two word
      filenum[1] = (unsigned char)(((data_words[0] >> 7) & 0x0F)>>0);
      filenum[2] = (unsigned char)(((data_words[0] >> 7) & 0xF0)>>4);
      filenum[0] = (unsigned char)(((data_words[1] >> 7) & 0xF0)>>4);
      filetype   = (unsigned char)(((data_words[1] >> 7) & 0x0F)>>0);
      filenum[0] = reverse(filenum[0], 4);
      filenum[1] = reverse(filenum[1], 4);
      filenum[2] = reverse(filenum[2], 4);
      filetype   = reverse(filetype, 4);
      filenum[0] += '0';
      filenum[1] += '0';
      filenum[2] += '0';
      filenum[3] = '\0';
      switch(filetype)
	{
	case 11:
	  filetype = 'P';
	  break;
	  
	case 15:
	  filetype = 'M';
	  break;
	}

      if( cis_flag_event_read_file )
	{
	  cis_flag_event_read_file = false;
	  
	  // Write data to a file
	  core_writefile(true);

	  // Check for meta information
	  meta_check();
	}
      
      display.fillRect(0, y, 128, 8, BLACK);
      display.setCursor(0,y);
      y += 8;
      if( y > 56 )
	{
	  y = 0;
	}
      display.print(cis_event);
      display.print (" '");
      display.print((char *) &(filenum[0]));
      display.print("'");
      display.display();
    }

  if( new_word )
    {
#if 0
      new_word = 0;
      
      Serial.print(copied_word, HEX);
      Serial.print(" ");
      Serial.print(copied_word_bits, HEX);
      Serial.print(" S");
      Serial.println(ce_isr_state);
#endif
#if 0      
      //      display.clearDisplay();
      display.clearDisplay();
      display.setCursor(0,16);
      display.print(captured_word, HEX);
      display.setCursor(0,24);
      display.print(copied_word, HEX);
      display.display();
#endif
    }
#endif
  
#if 0  
  if( Serial2.available(),0 )
    {
      c = Serial2.read();
      Serial.print(" S");
      Serial.println(c,HEX);
    }
#endif
  
}

void start_of_packet()
{
  int pb = GPIOB->IDR;
  int op = ISOLATE_BIT(4, pb);

  captured_word = 0;

#if STAT_BITS_0
  digitalWrite(statPin, HIGH);
  digitalWrite(statPin, LOW);
  digitalWrite(statPin, HIGH);
  digitalWrite(statPin, LOW);
#endif
  
  word_bits = 0;
  
  // Record current OP state so we can detect changes
  isr_current_op = op;

  // Not sending data
  //  isr_send_flag = false;
  
#if TRACE_TAGS
  buffer_point(0x1055, 0);
#endif
}

////////////////////////////////////////////////////////////////////////////////
//
//
// Processes the end of a packet. uses an FSM to decide what to do next
//
// This needs to be fast so we don't miss any subsequent interrupts
//
////////////////////////////////////////////////////////////////////////////////

void end_of_packet()
{
#if TRACE_TAGS
  buffer_point(0x10E0, captured_word);
#endif

  // End of packet means data input, so set output HIGH
  // Unless we are sending data
  if( !isr_send_flag )
    {
      digitalWrite(D3Pin, HIGH);
    }
  
#if DROP_ZERO_BIT_PACKETS
  // Ignore zero bit packets
  if( word_bits == 0 )
    {
#if TRACE_TAGS
      buffer_point(0x10E1, 0x1919);
#endif
      return;
    }
#endif
  
  copied_word = captured_word;
  copied_word_bits = word_bits;

  new_word = 1;

  if( isr_send_done )
    {
      buffer_point(isr_send_data_save, word_bits);
    }
  else
    {
      buffer_point(captured_word, word_bits);
    }
  
  // We don't have a lot of time so use a simple
  // nested switch FSM

  switch(ce_isr_state)
    {
    case CIS_IDLE:
      // We aren't transferring a file in either direction
      // so enable the monitor
      monitor_enabled = true;
      
      switch(captured_word)
	{
#if 0
	case IP_RESET:
	  ce_isr_state = CIS_502_PO_1;
	  break;
#endif	      
	case IP_UNKA:
	  ce_isr_state = CIS_RX_UNKNOWN_A;
	  break;

	  // Start of a file being sent from the 502p
	case IP_OPEN_WR:
	  ce_isr_state = CIS_WAIT_2;

	  // Provide the number of bits we are waiting for, as we know what the next
	  // packet will be
	  isr_hint_length = 6;
	  break;

	  // Start of a file being sent to the 502p
	  
	case IP_OPEN_RD:
	  // We start the tx index negative as that indicates header words.
	  // only once the index goes positive (or 0) does the code send
	  // data words form the data words array
	  
	  data_word_tx_index = HEADER_LENGTH;

	  // Provide the number of bits we are waiting for, as we know what the next
	  // packet will be
	  isr_hint_length = 6;
	  
	  ce_isr_state = CIS_RD_1;
	  break;
	  
	case IP_WAIT:
	  // Disable monitor
	  // This is the write path start
	  monitor_enabled = false;
	  
	  ce_isr_state = CIS_RX_WAIT;
	  //	  buf_in = 0;
	  num_data_words = 0;
	  //	  data_word_in_index = 0;
	  
	  // We want to send a 0 bit on the next clock cycle,
	  // set it up
	  isr_send_data = 0;
	  isr_send_data_save = isr_send_data;
	  isr_send_bits = 1;
	  isr_send_bits_save = 1;
	  isr_send_flag = true;
	  SET_DATA_BIT0;
	  break;
	}
      break;

      // We've sent the bit for the WAIT command, wait for it
      // to go and then back to idle
    case CIS_RX_WAIT:
      if( isr_send_done )
	{
	  isr_send_done = false;

	  // We have sent data, now continue
	  captured_word = 0;
	  ce_isr_state = CIS_IDLE;
	  //ce_isr_state = CIS_WAIT_2;
	}
      
      switch(captured_word)
	{

	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	  // This is due to a bad word at start of load path
	case IP_OPEN_RD:
	  // We start the tx index negative as that indicates header words.
	  // only once the index goes positive (or 0) does the code send
	  // data words form the data words array
	  
	  data_word_tx_index = HEADER_LENGTH;
	  
	  ce_isr_state = CIS_RD_1;
	  break;

	}
      break;

      // We've had an open for write, so we go down the write
      // path
    case CIS_WAIT_2:
      switch(captured_word)
	{
	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_data_save = isr_send_data;
	  isr_send_bits_save = isr_send_bits;
	  isr_send_flag = true;
	  SET_DATA_BIT0;
	  ce_isr_state = CIS_WAIT_3;
	  break;
#if 1
	case IP_RESET:
	  // End of data, signal event and back to idle
	  if( word_bits == 6 )
	    {
	      cis_flag_event = true;
	      cis_event = "File:";
	      cis_flag_event_read_file = true;
	      
	      ce_isr_state = CIS_IDLE;
	      monitor_enabled = true;
	    }
	  break;
#endif
	}
      
      break;

      // We've had an open for read, so we go down the read
      // path
      
    case CIS_RD_1:
      
      // We disable the monitor here for the read path as it's the first
      // packet received
      monitor_enabled = false;

      switch(captured_word)
	{
	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_data_save = isr_send_data;
	  isr_send_bits_save = isr_send_bits;
	  isr_send_flag = true;
	  SET_DATA_BIT0;
	  ce_isr_state = CIS_RD_STAT;
	  break;
#if 1
	case IP_RESET:
	  // End of data, signal event and back to idle
	  if( word_bits == 6 )
	    {
	      cis_flag_event = true;
	      cis_event = "Sent:";
	      
	      ce_isr_state = CIS_IDLE;
	      monitor_enabled = true;
	    }
	  break;
#endif
	}
      
      break;

    case CIS_WAIT_3:
      if( isr_send_done )
	{
	  isr_send_done = false;

	  // Status sent so now we wait for the transfer command
	  captured_word = 0;
#if 0
	  cis_flag_event = true;
	  cis_event = "inv EXE";
#endif
	  ce_isr_state = CIS_WAIT_TRANS;

	}

      switch(captured_word)
	{
	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;
	}
      break;

      // We have had a request for status so we return a good status
      // if we have no need to pause the transmission.
      // We can't send the file number that the 502p has been sked
      // to receive as we have no way to know what that is. That means we
      // have to enter the file number on the SD card board
      // We could have a coded form of file number selection using a specific
      // number in a specific memory or something, but we'll do that later
    case CIS_RD_STAT:
      if( isr_send_done )
	{
	  // Status sent so now we wait for the transfer command
	  captured_word = 0;
#if 0
	  cis_flag_event = true;
	  cis_event = "inv EXE";
#endif
	  //	  ce_isr_state = CIS_WAIT_TRANS;
	  ce_isr_state = CIS_RD_WAIT_TRANS;
	}

      switch(captured_word)
	{
	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	}
      break;
      
    case CIS_WAIT_TRANS:
      switch(captured_word)
	{
	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_data_save = isr_send_data;
	  isr_send_bits_save = isr_send_bits;
	  isr_send_flag = true;
	  SET_DATA_BIT0;
	  ce_isr_state = CIS_WAIT_3;
	  break;
#if 1
	case IP_TRANSFER:
	  // We have the transfer command so now wait for
	  // data
	  ce_isr_state = CIS_WAIT_DATA;
#endif
	  break;
	}
      break;

    case CIS_RD_WAIT_TRANS:
      switch(captured_word)
	{
	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_data_save = isr_send_data;
	  isr_send_bits_save = isr_send_bits;
	  isr_send_flag = true;
	  SET_DATA_BIT0;
	  //ce_isr_state = CIS_WAIT_3;
	  ce_isr_state = CIS_RD_1;
	  break;

	  // header has been received, we can stop sending header
	  // words
	case IP_CARRIER_DET:
	  data_word_tx_index = 0;
	  break;
#if 1
	case IP_TRANSFER:
	  // We need to send 16 bits of data, send the next data word from
	  // the data word buffer.
	  isr_send_bits = 16;
	  if( data_word_tx_index < 0 )
	    {
	      // Send header data
	      isr_send_data = HEADER_WORD;
	      data_word_tx_index++;
	    }
	  else
	    {
	      isr_send_data = reverse(data_words[data_word_tx_index++], 16);
	      //isr_send_data = data_words[data_word_tx_index++];

#if SHIFT_TX_DATA
	      // Data is shifted 4 bits
	      isr_send_data <<= 4;
	      isr_send_data |= 0x7;
#else
	      //isr_send_data |= 0xf000;
#endif
	      if( data_word_tx_index > (NUM_DATA_WORDS - 1) )
		{
		  data_word_tx_index = (NUM_DATA_WORDS -1);
		}
	    }
	  isr_send_data_save = isr_send_data;
	  isr_send_bits_save = isr_send_bits;
	  isr_send_flag = true;

	  // We need to drive the GPIO line, pull up is not enough
	  pinMode(D3Pin, OUTPUT);
	  SET_DATA_BIT0;
	  ce_isr_state = CIS_RD_SENDING;
#endif
	  break;
	}
      break;

    case CIS_RD_SENDING:
      if( isr_send_done )
	{
	  // We have sent data, now go back and see if more should be sent
	  captured_word = 0;

	  // We know the length of the next packet
	  isr_hint_length = 6;
	  
	  ce_isr_state = CIS_RD_1;
	  //ce_isr_state = CIS_WAIT_2;
	}

      switch(captured_word)
	{

	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;
	}
      break;
      
    case CIS_WAIT_DATA:

      if(word_bits == 16)
	{
	  // 16 bits of data
	  
	  // If data is all 1s then it is header data

	  
	  if( (captured_word & 0xFFF0) == 0xFFF0 )
	    {
	      // Header word, ignore it
	      // Back for more data
	      num_header_words++;

	      // We know the length of the next packet
	      isr_hint_length = 6;
	      ce_isr_state = CIS_WAIT_2;
	    }
	  else
	    {
	      // Store this data
	      data_words[num_data_words++] = captured_word;

	      if( num_data_words >= (NUM_DATA_WORDS-10) )
		{
		  num_data_words = NUM_DATA_WORDS - 10;
		}

	      // We know the length of the next packet
	      isr_hint_length = 6;
	      ce_isr_state = CIS_WAIT_2;
	    }
	}

      switch(captured_word)
	{
      	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_data_save = isr_send_data;
	  isr_send_bits_save = isr_send_bits;
	  isr_send_flag = true;
	  SET_DATA_BIT0;
	  ce_isr_state = CIS_WAIT_TRANS;
	  break;
	}
      break;
      
    case CIS_RX_UNKNOWN_A:
      switch(captured_word)
	{
      	case IP_STOP:
	  ce_isr_state = CIS_IDLE;
	  break;

	case IP_PRESENCE:
	  // We need to send a bit after this command
	  isr_send_bits = 1;
	  isr_send_data = 0;
	  isr_send_data_save = isr_send_data;
	  isr_send_bits_save = isr_send_bits;
	  isr_send_flag = true;
	  SET_DATA_BIT0;
	  break;
	}
      break;
	  
    case CIS_502_PO_1:
      switch(captured_word)
	{
	case IP_STOP:
	  cis_flag_event = true;
	  cis_event = "Reset";
	  ce_isr_state = CIS_IDLE;
	  break;
	}
      break;
	  
    }

#if TRACE_TAGS
  buffer_point(0x10E1, 0);
#endif
}


// SP has had an edge

void spISR()
{
  volatile int pb = GPIOB->IDR;
  int sp = ISOLATE_BIT(12, pb);
  int d =  ISOLATE_BIT(3, pb);
  int ce = ISOLATE_BIT(13, pb);

#if !LATER_OP_RD
      pb = GPIOB->IDR;
      int op = ISOLATE_BIT(4, pb);
#endif


  boolean end_packet_now = false;
  

#if STAT_SP  
  digitalWrite(statPin, HIGH);
#endif
  
#if TRACE_CLOCKS  
  buffer_point(0x10C1, sp);
#endif
  
  // If ce is not asserted then we just exit, we ignore
  // anything not for us
  if( !ce )
    {
#if STAT_SP      
      digitalWrite(statPin, LOW);
#endif
      return;
    }

  // Do we have to send data for this clock?
  if( isr_send_flag )
    {
      
#if TRACE_TAGS
      buffer_point(0x105E, isr_send_data);
#endif
      
      // We are required to send bits
      // Data seems to change on a different edge when sending the 16 bit
      // data to the 502p
      
#if TX_CHANGE_RISING_EDGE      
      if( !sp )
#else
	if(sp)
#endif	
	  {
	    // One more bit sent
	    isr_send_bits--;
	    isr_send_data >>= 1;
	  
	    if( isr_send_bits == 0 )
	      {
		// All done

#if TRACE_TAGS
		buffer_point(0x1051, 0x111);
#endif
	      
		// Turn send flag off
		isr_send_flag = false;

		// Send stimulus to FSM
		isr_send_done = true;
		word_bits = isr_send_bits_save;

		// Set as open drain again
		pinMode(D3Pin, OUTPUT_OPEN_DRAIN);	      
		digitalWrite(D3Pin, HIGH);
	      }
	  }
	else
	  {
	    // falling edge
	    // Set data up
	    // Invert it
	    if( (isr_send_data & 1) )
	      {
		// Send a 1 (inverted logic) by writing a 0 and
		// driving open collector output
		digitalWrite(D3Pin, LOW);
	      }
	    else
	      {
		// Take line high
		digitalWrite(D3Pin, HIGH);
	      }
	  
#if TRACE_TAGS
	    buffer_point(0x1050, 0x0);
#endif
	  }
    }
  else
    {
      
      // We are reading data
      if( sp )
	{
	  // One more rising SP, capture data
	  captured_word <<= 1;
	  captured_word += (1-d);
	  word_bits++;
#if STAT_BITS_0
	  digitalWrite(statPin, HIGH);
	  digitalWrite(statPin, LOW);
#endif
	}
      else
	{
	  // If we are in send mode then we need to 
	}

      // Has OP changed?
      // We read OP here to give us a delay from the SPISR to reading the GPIO
      // If we do it too fast the GPIO state is wrong, when we use fast code,
      // or larger code sizes. No idea why.
#if LATER_OP_RD
      pb = GPIOB->IDR;
      int op = ISOLATE_BIT(4, pb);
#endif

#if USE_HINT_LENGTH      
      // Do we have a hint as to the length of the packet
      // we are waiting for?
      end_packet_now = false;
      if( isr_hint_length != 0 )
	{
	  // yes, end the packet if the length matches
	  if( word_bits == isr_hint_length )
	    {
	      end_packet_now = true;
	      isr_hint_length = 0;
	    }
	}
#endif
      
      // Has OP changed?

      // If so we end this packet, but only if ce is active
      
      if( (op != isr_current_op) || end_packet_now )
	{
#if TRACE_TAGS
	  buffer_point(0x10BB, op);
#endif
	  
	  // End of this packet
	  end_of_packet();

	  // Start of next one
	  start_of_packet();
	}

      // New current value for OP
      isr_current_op = op;


    }

#if STAT_SP  
  digitalWrite(statPin, LOW);
#endif
}


// A packet has just started, or, more accurately we have just had
// an asserted CE
// We end the packet when CE de-asserts.
// OP has to be monitored as we use that to determine when the
// current command has ended and we need to process the next
// command or data bit

void ceISR()
{
  int pb = GPIOB->IDR;
  int ce = ISOLATE_BIT(13, pb);

#if STAT_CE
  digitalWrite(statPin, HIGH);
#endif
  
#if TRACE_TAGS
  buffer_point(0x10CE, ce);
#endif
  
  // One more rising CE
  if( ce )
    {
      start_of_packet();
    }
  else
    {
      end_of_packet();
      //      start_of_packet();   //????
    }
  
#if STAT_CE
  digitalWrite(statPin, LOW);
#endif
}


// If OP changes state then it's the end of a packet
// and the start of a new one.
#if 1

void opISR()
{
  int pb = GPIOB->IDR;
  int op = ISOLATE_BIT(4, pb);

#if STAT_OP    
  digitalWrite(statPin, HIGH);
#endif
  
#if TRACE_TAGS
  buffer_point(0x10CC, op);
#endif
  
  end_of_packet();
  start_of_packet();

#if STAT_OP  
  digitalWrite(statPin, LOW);
#endif  
}
#endif
