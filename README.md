# Adapter for FX-502p Calculator Interface

# Adapter that allows calculator to access and SD card and GPIOs on an STM32. Allows I2c and thermal printer printouts.
#


Note:
Although the FX-602P uses a similar command set it doesn't yet work with this adapter. It should be possible to make it work though.
The FX-702p uses the same command set but operates at 5V so it also doesn't work with this adapter without some form of level shifter.
