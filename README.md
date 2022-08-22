# Adapter for FX-502p Calculator Interface

Adapter that allows calculator to access and SD card and GPIOs on an STM32. Allows I2c and thermal printer printouts.

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
 connector J7. 

Commands
========

The FX502P communicates with the gadget using the INV SAVE INV EXE keystroke. This saves the 
current display value to the tape interface. The commands are coded in numbers, so to issue a command 
enter the number on the calculator and hen press INV SAVE INV EXE

1.0 E40
This command displays help text on the OLED screen. Press the decimal point key to move
to the next page of help text.

A.BC E47
This sets the current filename for programs to PABC.DAT. This is needed as even though the file number
is entered on the calculator when savng and loading that number does not go over the interface when loading.

A.BC E48
This set sthe current filename to MABC for memory saving and loading.

A.BCD E49
This sets the filename bank to ABCD

Real Time Clock Commands
------------------------

1.0 E 42 : Read time
2.yymmdd E42 Set date
3.hhmmss E42 Set time



# Note:
# Although the FX-602P uses a similar command set it doesn't yet work with this adapter. It should be possible to make it work though.
# The FX-702p uses the same command set but operates at 5V so it also doesn't work with this adapter without some form of level shifter.


