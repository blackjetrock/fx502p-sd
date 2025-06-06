# Adapter for FX-502p Calculator Interface

Adapter that allows calculator to access and SD card and GPIOs on an STM32. Allows I2c and thermal printer printouts.

![IMG_20250401_211537476](https://github.com/user-attachments/assets/a8959951-17f1-4ca3-8cac-b0b70dedff60)

 The sketch accepts commands from the 502p and stores the data
 words on the SD card under a filename specified on the 502p. This
 is a three digit number. When loading back the data words are sent
 as they were received.

 The files are FILEtnnn.DAT

    where nnn is the 3 digit file number
    and t is the type of the file:
         M for memories
         P for programs

 We leave the data line as an open drain
 output, even when we want to use it as an input. This saves the
 cycles needed to call pinMode(). Time is short when processing
 the commands from the 502p so all of the processing is done in
 interrupt routines using nested switch FSMs

 The header has been cut down to the minimum that works (50 words)
 and there's no delay when sending data words to or from the 502p.
 This means loading and saving is faster than using the FA-1

 There is code in this sketch to set and read the time and date. This
 uses a DS3231 RTC attached to the PC7 and PC6 GPIO lines on the gpio
 connector J7. On the module I used, GND and VCC lined up with GND and 3V3 on J7 
 so the code uses the GPIO lines that line up with SDA and SCL and create 
 an I2C bus on those pins.

Commands
========

The FX502P communicates with the gadget using the INV SAVE INV EXE keystroke. This saves the 
current display value to the tape interface. The commands are coded in numbers, so to issue a command 
enter the number on the calculator and then press INV SAVE INV EXE
So, for example, to display the help text page onm the OLED display you need to enter 1.0E40 and then
INV SAVE INV EXE. The help text should then be shown on the OLED display.

1.0 E40

This command displays help text on the OLED screen. Press the decimal point key to move
to the next page of help text.

1.1 E40

Display status page

1.2 E40
Display the graphics page.
Pixels can be set on this page using the graphics commands

1.3 E40
Display memory page.
This page shows memories that have been sent using an INV SAVE EXE in MODE 1

1.4 E40
Display text page. text can be placed on this page with the text commands.


1.5 E40
Display token page
This page display program tokens sent using INV SAVE EXE in MODE 3
Page using the decimal point key.

1.6 E40
This page displays the current date and time. An RTC module must be attached using I2C.


1.70 E40
Turns printing off

1.71 E40
Turns printing on
	  


A.BC E47

This sets the current filename for programs to PABC.DAT. This is needed as even though the file number
is entered on the calculator when savng and loading that number does not go over the interface when loading.

A.BC E48

This set sthe current filename to MABC for memory saving and loading.

A.BCD E49

This sets the filename bank to ABCD. The filename banks are a way to have more than 1000 programs or memories stored on an SD card. 

Real Time Clock Commands
------------------------
This requires a DS3231 I2C real time clock module to hold the time and date. It needs to be attached to the I2C

1.0 E42 : Read date

After this is received, the date can be read using an
 
	 inv LOAD inv EXE
	  or
	 inv LOAD EXE

The date is in either the X register or the F memory
respectively.
	 
2.0 E42 : Read time

After this is received, the time can be read using an
 
	 inv LOAD inv EXE
	  or
	 inv LOAD EXE
	
respectively.

2.yymmdd E42 : Set date

3.hhmmss E42 : Set time


Text Display Commands
---------------------

Put text on the display

1.xxyy E41     
  
  Set cursor to (x,y)
  
2.aabbccdd E41   
  
3.aabbccdd E41   
  
  Print text on printer, aa etc are ascii codes

Graphics Display Commands
-------------------------

Sample Programs
---------------

The directory 

Sample_FX502P_Programs

holds some example programs.

- P998  Draws random dots on the OLED display
- ![IMAG2680](https://user-images.githubusercontent.com/31587992/186107269-a8835f86-1f78-45a7-9d78-4ada5e2dd4f6.jpg)

- P999  Draws a sine wave on the OLED display
![IMAG2677](https://user-images.githubusercontent.com/31587992/186105780-468d5783-0f16-4c4b-8286-751db65d038a.jpg)


Printer
-------

The gadget can drive a simple thermal printer of the type used for receipt printing. An external PSU is required for printing due to the current requirements of the printer. Check the printer details for the curren tit uses, if it doesn't say, assume a 2A or higher PSU is needed, these printers take a lot of current. 
The attachment is on J3. there's an (unmarked) GND connection which should be attached to the PSU for the printer. The TX line sends data to the printer when enabled in the gadget.
When conneted and enabled, saving a program or memories results in the data being printed out, in ASCII.

This is the printer attached to the gadget. The black lead is GND:
![IMAG2673](https://user-images.githubusercontent.com/31587992/186103871-0126356a-db8c-4ae6-b160-0595b8cada4a.jpg)

This is the rear of the printer showing the connections:
![IMAG2676](https://user-images.githubusercontent.com/31587992/186103966-8dca466f-541c-466b-a4a6-35d6ce19fc37.jpg)

The details of the printer PSU I used. This was just one I had lying about, I made a socket connection for it.
![IMAG2674](https://user-images.githubusercontent.com/31587992/186103937-f3e9ff34-7684-4ce9-a8c4-ec7d56ae96f9.jpg)

This is th eprinter I used, with some sample output.
![IMAG2675](https://user-images.githubusercontent.com/31587992/186103979-77ccb95e-cc5d-4b36-b70f-66bfaab75b2f.jpg)

This is the output when printing programs (ignore the memory line at the top, that is what is printed if INV SAVE INV EXE is used in MODE1):
![IMAG2679](https://user-images.githubusercontent.com/31587992/186105376-8986fa3f-f110-412f-b77a-5a2a27c24139.jpg)

And this is the printout of memories:
![IMAG2678](https://user-images.githubusercontent.com/31587992/186105384-00c22a10-865b-4468-b48d-e43195b9bbd6.jpg)

#
# Note:
# Although the FX-602P uses a similar command set it doesn't yet work with this adapter. It should be possible to make it work though.
# The FX-702p uses the same command set but operates at 5V so it also doesn't work with this adapter without some form of level shifter.


