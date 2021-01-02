//
// Sketch to attach to fx502p and read/write data to.from SD card
//
// We should be able to leave the data line as an open collector
// output, even when we want to use it as an input

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Code configuration
#define DEBUG_SERIAL          0
#define DIRECT_WRITE          0
#define DROP_ZERO_BIT_PACKETS 1
#define TRACE_CLOCKS          0
#define TRACE_TAGS            0

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

int filename_index = 0;

const int chipSelect = 4;

// Pins for fx502p interface
const int D3Pin     = PB3;
const int OPPin      = PB4;

const int SPPin      = PB12;
const int CEPin      = PB13;
const int VCCPin     = PB14;
const int CONTPin    = PB15;

#define ISOLATE_BIT(N,X) ((X & (1<< N)) >> N)

// Debug outputs
const int statPin   = PC13;
const int dataPin   = PC14;


// FSM output flags
boolean cis_flag_502_po = false;
boolean cis_flag_event = false;
char *cis_event = "None";

int loopcnt = 0;
volatile int captured_word = 0;
  
File myFile;

// Capture file
File dumpfile;


enum
  {
    CIS_IDLE = 0,
    CIS_502_PO_1,
    CIS_RX_UNKNOWN_A,
    CIS_RX_WAIT,
    CIS_WAIT_2,
    CIS_WAIT_3,
    CIS_WAIT_TRANS,
    CIS_WAIT_DATA,
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
    IP_UNKA         = 0x19,
    IP_TERMINATE    = 0x1f,
    IP_RDSTAT       = 0x21,
    IP_SELPRT       = 0x29,
    IP_SENDCTRL     = 0x33,
    IP_COUNTER      = 0x34,
    IP_CLOSE        = 0x3C,
    IP_STOP         = 0x3E,

    // Special stimulii
    IP_SEND_DONE    = 0x205D,
  };


const int MAX_BYTES = 20;
const int button1Pin = PA0;
const int button2Pin = PA1;
const int button3Pin = PC15;



volatile int in_byte = 0;
volatile int isr_send_bits = 0;
volatile int isr_send_data = 0;
volatile int isr_send_bits_save = 0;
volatile boolean isr_send_flag = false;
volatile int isr_current_op = 0;
volatile int ce_isr_state = CIS_IDLE;

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

volatile int sp_count=0;
volatile int ce_count=0;
volatile int copied_word = 0;
volatile int word_bits = 0;
volatile int copied_word_bits = 0;

volatile int new_word = 0;

#define BUF_LEN 1500

volatile int buf_in = 0;
volatile int word_buffer[BUF_LEN];
volatile uint8_t blen_buffer[BUF_LEN];
volatile int num_data_words = 0;

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
  
  Serial.println("INDEX");
  arg = cmd.substring(1);
  Serial.println(arg);
  
  indx = arg.toInt();
}

// Modify the buffer
void cmd_modify(String cmd)
{
  String arg;
  
  Serial.println("MOD");
  arg = cmd.substring(1);

  if( indx <= MAX_BYTES )
    {
      stored_bytes[indx] = arg.toInt();
    }
}


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
  Serial.print("  Num data words:");
  Serial.print(num_data_words);

  Serial.println("");
  
  for(i=0; i<buf_in; i++)
    {
      if( (word_buffer[i] & 0xff00) != 0x1000 )
	{
      sprintf(line, " %02X (%d bits)", word_buffer[i], blen_buffer[i]);
      Serial.println(line);
	}
      else
	{
	  sprintf(line, "T%04X %04X", word_buffer[i], blen_buffer[i]);
	  Serial.println(line);
	}
    }
}

// Clear the buffer


void cmd_clear(String cmd)
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
      // Read from the file and store it in the buffer
      bytecount = 0;
      
      while (myFile.available())
	{
	  stored_bytes[bytecount++] = myFile.read();
	  if( bytecount >= MAX_BYTES )
	    {
	      bytecount = MAX_BYTES;
	    }
	  
	}
      
      // close the file:
      myFile.close();

      if ( oled_nserial )
	{
	  display.print(bytecount);
	  display.println(" bytes read");
	  display.display();
	  delay(3000);
	}
      else
	{
	  Serial.print(bytecount);
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


void core_writefile(boolean oled_nserial)
{
  char filename[20] = "U___.txt";
  int i;

  do
    {
      sprintf(filename, "PCG%04d.DAT", filename_index++);
    }

  while( SD.exists(filename) );
  
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
      Serial.print(bytecount);
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
      for(i=0; i<bytecount; i++)
	{
	  myFile.write(stored_bytes[i]);
	}
      
      myFile.close();

      if( oled_nserial )
	{
	  display.setCursor(0,3*8);
	  display.print(bytecount);
	  display.println(" bytes written");
	  display.display();
	}
      else
	{
	  Serial.print(bytecount);
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

void cmd_writefile(String cmd)
{
  core_writefile(false);
}

const int NUM_CMDS = 15;

String cmd;
struct
{
  String cmdname;
  CMD_FPTR   handler;
} cmdlist [NUM_CMDS] =
  {
    {"m",           cmd_modify},
    {"c",           cmd_clear},
    {"d",           cmd_display},
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
  
  for(i=0; i<NUM_CMDS; i++)
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

  
//HardwareSerial Serial1(PA10, PA9);
HardwareSerial Serial2(PB11, PB10);

void setup() {

  Wire.begin();
  pinMode(SPPin, INPUT);

  // Make data line open drain output. We can read from it when set to
  // high as it is just a pull-up. Not having to call
  // pinMode saves us cycles
  
  pinMode(D3Pin, OUTPUT_OPEN_DRAIN);
  pinMode(PA0, INPUT);
  pinMode(PA1, INPUT);
  pinMode(PA2, INPUT);
  
  pinMode(statPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  //  digitalWrite(dataPin, LOW);
  
  // put your setup code here, to run once:
  Serial.begin(2000000);
  Serial2.begin(9600);

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
    Serial.println("SD Card initialisation failed!");
    display.println("SD Fail");
    display.display();
    delay(2000);
  }
  else
    {
      Serial.println("SD card initialised.");
      display.println("SD OK");
      display.display();
      delay(2000);
    }

#endif
  
  bytecount = strlen(&(stored_bytes[0]));
  current_menu = &(home_menu[0]);
  last_menu = &(home_menu[0]);
  the_home_menu = last_menu;

#if 0
  to_home_menu(NULL);
#endif
  init_buttons();

  // We want an interrupt on rising edge of clock
  attachInterrupt(digitalPinToInterrupt(SPPin), spISR,  CHANGE);
  attachInterrupt(digitalPinToInterrupt(CEPin), ceISR,  CHANGE);
  attachInterrupt(digitalPinToInterrupt(OPPin), opISR,  CHANGE);
    
  //  attachInterrupt(digitalPinToInterrupt(SIOTXDPin), highISR, RISING);
}


void buffer_point(int captured_word, int word_bits)
{
  if( buf_in < BUF_LEN )
    {
      word_buffer[buf_in]  = captured_word;
      blen_buffer[buf_in]  = word_bits;
      buf_in++;
    }
}

void loop() {
  int i;
  char c;

  loopcnt++;
  
  if( (loopcnt % 50000000) == 0 )
    {
      Serial.println("Loop");
    }
  
  update_buttons();
  run_monitor();

  if( cis_flag_event )
    {
      cis_flag_event = false;
      display.fillRect(0, 32, 128, 8, BLACK);
      display.setCursor(0,32);
      display.print(cis_event);
      display.display();
    }

  if( cis_flag_502_po )
    {
      cis_flag_502_po = false;
      display.fillRect(0, 24, 128, 8, BLACK);
      display.setCursor(0,24);
      display.print("fx502p PO");
      display.display();
    }
  
  if( new_word )
    {
      new_word = 0;
      
      Serial.print(sp_count);
      Serial.print(" ");
      Serial.print(ce_count);
      Serial.print(" ");
      Serial.print(copied_word, HEX);
      Serial.print(" ");
      Serial.println(copied_word_bits, HEX);

#if 0      
      //      display.clearDisplay();
      display.clearDisplay();
      display.setCursor(0,0);
      display.print(sp_count);
      display.setCursor(0,8);
      display.print(ce_count);
      display.setCursor(0,16);
      display.print(captured_word, HEX);
      display.setCursor(0,24);
      display.print(copied_word, HEX);
      display.display();
#endif
    }
    
  if( Serial2.available(),0 )
    {
      c = Serial2.read();
      Serial.print(" S");
      Serial.println(c,HEX);
    }
}

void start_of_packet()
{
  int pb = GPIOB->IDR;
  int op = ISOLATE_BIT(4, pb);

  captured_word = 0;
  word_bits = 0;

  // Record current OP state so we can detect changes
  isr_current_op = op;

#if TRACE_TAGS
  buffer_point(0x1055, 0, 0);
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
  buffer_point(0x10E0, ce_isr_state, captured_word);
#endif

  // End of packet means data input, so set output HIGH
  digitalWrite(D3Pin, HIGH);

#if DROP_ZERO_BIT_PACKETS
  // Ignore zero bit packets
  if( word_bits == 0 )
    {
#if TRACE_TAGS
      buffer_point(0x10E1, 0x1919, 0x1919);
#endif
      return;
    }
#endif
  
  copied_word = captured_word;
  copied_word_bits = word_bits;

  new_word = 1;

  buffer_point(captured_word, word_bits);
  
  // We don't have a lot of time so use a simple
  // nested switch FSM

  switch(ce_isr_state)
    {
    case CIS_IDLE:
      switch(captured_word)
	{
	case IP_RESET:
	  ce_isr_state = CIS_502_PO_1;
	  break;
	      
	case IP_UNKA:
	  ce_isr_state = CIS_RX_UNKNOWN_A;
	  break;

	case IP_WAIT:
	  ce_isr_state = CIS_RX_WAIT;
	  num_data_words = 0;
	  
	  // We want to send a 0 bit on the next clock cycle,
	  // set it up
	  isr_send_data = 0;
	  isr_send_bits = 1;
	  isr_send_bits_save = 1;
	  isr_send_flag = true;
	  break;
	}
      break;
	  
    case CIS_RX_WAIT:
      switch(captured_word)
	{
	case IP_SEND_DONE:
	  // We have sent data, now continue
	  ce_isr_state = CIS_WAIT_2;
	  break;
	}
      break;

    case CIS_WAIT_2:
      switch(captured_word)
	{
	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_bits_save = 1;
	  isr_send_flag = true;

	  ce_isr_state = CIS_WAIT_3;
	  break;
#if 0
	case IP_RESET:
	  // End of data, signal event and back to idle
	  if(  == 6 )
	    {
	      cis_flag_event = true;
	      cis_event = "Data received";
	      
	      ce_isr_state = CIS_IDLE;
	    }
	  break;
#endif
	}
      
      break;

    case CIS_WAIT_3:
      switch(captured_word)
	{
	case IP_SEND_DONE:
	  // Status sent so now we wait for the transfer command
#if 0
	  cis_flag_event = true;
	  cis_event = "inv EXE";
#endif
	  ce_isr_state = CIS_WAIT_TRANS;

	  break;
	}
      break;
      
    case CIS_WAIT_TRANS:
      switch(captured_word)
	{
	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_bits_save = 1;
	  isr_send_flag = true;

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

    case CIS_WAIT_DATA:
      if(word_bits == 16)
	{
	  // 16 bits of data
	  
	  // If data is all 1s then it is header data
	  num_data_words++;
	  
	  if( captured_word == 0xFFFF )
	    {
	      // Back for more data
	      ce_isr_state = CIS_WAIT_2;
	    }
	  else
	    {
	      // Store this data
	      ce_isr_state = CIS_WAIT_2;
	    }
	}

      switch(captured_word)
	{
	case IP_READ_STATUS:
	  // We have the next packet, we need to send a data bit
	  // for this one too
	  isr_send_bits = 1;
	  isr_send_data = 1;
	  isr_send_bits_save = 1;
	  isr_send_flag = true;


	  ce_isr_state = CIS_WAIT_TRANS;
	  break;
	}
      break;
      
    case CIS_RX_UNKNOWN_A:
      switch(captured_word)
	{
	case IP_PRESENCE:
	  // We need to send a bit after this command
	  isr_send_bits = 1;
	  isr_send_data = 0;
	  isr_send_bits_save = 1;
	  isr_send_flag = true;

	  break;
	}
      break;
	  
    case CIS_502_PO_1:
      switch(captured_word)
	{
	case IP_STOP:
	  cis_flag_event = true;
	  cis_event = "fx502p po";
	  ce_isr_state = CIS_IDLE;
	  break;
	}
      break;
	  
    }

#if TRACE_TAGS
  buffer_point(0x10E1, 0, 0);
#endif
}


// SP has had an edge

void spISR()
{
  int pb = GPIOB->IDR;
  int sp = ISOLATE_BIT(12, pb);
  int d =  ISOLATE_BIT(3, pb);
  int op = ISOLATE_BIT(4, pb);
  int ce = ISOLATE_BIT(13, pb);
  
  digitalWrite(statPin, HIGH);

#if TRACE_CLOCKS  
  buffer_point(0x10C1, sp, sp);
#endif
  
  // If ce is not asserted then we just exit, we ignore
  // anything not for us
  if( !ce )
    {
      return;
    }
  
  if( isr_send_flag )
    {
      
#if TRACE_TAGS
      buffer_point(0x105E, isr_send_bits, isr_send_data);
#endif
      
      // We are required to send bits
      if( sp )
	{
	  // One more bit sent
	  isr_send_bits--;
	  isr_send_data >>= 1;
	  
	  if( isr_send_bits == 0 )
	    {
	      // All done
	      // Set as input again
	      digitalWrite(D3Pin, HIGH);

#if TRACE_TAGS
	      buffer_point(0x1051, 0x111, 0x111);
#endif
	      
	      // Turn send flag off
	      isr_send_flag = false;

	      // Send stimulus to FSM
	      captured_word = IP_SEND_DONE;
	      word_bits = isr_send_bits_save;
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
	      // Send a 0 (inverted to a 1) by doing nothing
	    }
	  
#if TRACE_TAGS
	  buffer_point(0x1050, 0x0, 0x0);
#endif
	}
    }
  else
    {
      // Has OP changed?
      // If so we end this packet, but only if ce is active
      
      if( op != isr_current_op,0 )
	{
#if TRACE_TAGS
	  buffer_point(0x10BB, op, op);
#endif
	  
	  // End of this packet
	  end_of_packet();

	  // Start of next one
	  start_of_packet();
	}

      // New current value for OP
      isr_current_op = op;
      
      // We are reading data
      if( sp )
	{
	  // One more rising SP, capture data
	  sp_count++;
	  
	  captured_word <<= 1;
	  captured_word += (1-d);
	  word_bits++;
	}
      else
	{
	  // If we are in send mode then we need to 
	}
    }
  
  digitalWrite(statPin, LOW);
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

  digitalWrite(statPin, HIGH);

#if TRACE_TAGS
  buffer_point(0x10CE, ce, ce);
#endif
  
  // One more rising CE
  ce_count++;

  if( ce )
    {
      start_of_packet();
    }
  else
    {
      end_of_packet();
    }
  
  
  digitalWrite(statPin, LOW);
}


// If OP changes state then it's the end of a packet
// and the start of a new one.
#if 1

void opISR()
{
  int pb = GPIOB->IDR;
  int op = ISOLATE_BIT(4, pb);
 
  digitalWrite(statPin, HIGH);

#if TRACE_TAGS
  buffer_point(0x10CC, op, op);
#endif
  
  end_of_packet();
  start_of_packet();
 
  digitalWrite(statPin, LOW);
  
}
#endif
