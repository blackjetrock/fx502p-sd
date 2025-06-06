EESchema Schematic File Version 5
EELAYER 46 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
Comment5 ""
Comment6 ""
Comment7 ""
Comment8 ""
Comment9 ""
$EndDescr
Connection ~ 2450 2700
Connection ~ 4950 3000
Connection ~ 4950 7000
Connection ~ 5050 3000
Connection ~ 5050 7000
Connection ~ 5150 3000
Connection ~ 5150 7000
Connection ~ 5250 3000
Connection ~ 5250 7000
Connection ~ 5350 3000
Connection ~ 7500 2800
Connection ~ 7500 3350
Connection ~ 7650 2100
Connection ~ 7650 2700
Connection ~ 7650 3450
Connection ~ 8150 2100
Wire Wire Line
	850  2500 850  2650
Wire Wire Line
	850  2850 850  3250
Wire Wire Line
	950  3500 950  4000
Wire Wire Line
	1050 2650 1050 2500
Wire Wire Line
	1050 3250 1050 2850
Wire Wire Line
	1150 3750 1150 3500
Wire Wire Line
	1150 4100 1150 3950
Wire Wire Line
	1250 2650 1250 2500
Wire Wire Line
	1250 2850 1250 3250
Wire Wire Line
	1350 3950 1350 3500
Wire Wire Line
	1450 2650 1450 2500
Wire Wire Line
	1450 2850 1450 3250
Wire Wire Line
	1850 4350 1900 4350
Wire Wire Line
	1900 4350 1900 4650
Wire Wire Line
	2050 2700 2050 3950
Wire Wire Line
	2050 3950 1350 3950
Wire Wire Line
	2250 2700 2450 2700
Wire Wire Line
	2450 2100 2450 2700
Wire Wire Line
	2450 2100 2750 2100
Wire Wire Line
	2450 2700 3100 2700
Wire Wire Line
	2750 850  2750 1200
Wire Wire Line
	2750 1300 2750 1700
Wire Wire Line
	2750 2000 2750 2100
Wire Wire Line
	3050 5800 3050 6500
Wire Wire Line
	3050 6500 4100 6500
Wire Wire Line
	3100 2550 3100 2700
Wire Wire Line
	3200 2700 3200 2550
Wire Wire Line
	3400 2700 3200 2700
Wire Wire Line
	3800 5100 4450 5100
Wire Wire Line
	3800 5300 4450 5300
Wire Wire Line
	3800 5500 4450 5500
Wire Wire Line
	3800 5700 4450 5700
Wire Wire Line
	3850 4700 4450 4700
Wire Wire Line
	3850 4800 4050 4800
Wire Wire Line
	3850 6000 3800 6000
Wire Wire Line
	3850 6000 3850 6350
Wire Wire Line
	4100 5900 3800 5900
Wire Wire Line
	4100 6500 4100 5900
Wire Wire Line
	4250 4800 4450 4800
Wire Wire Line
	4450 5200 3800 5200
Wire Wire Line
	4450 5400 3800 5400
Wire Wire Line
	4450 5600 3800 5600
Wire Wire Line
	4450 5800 3800 5800
Wire Wire Line
	4950 3000 4950 2800
Wire Wire Line
	4950 3200 4950 3000
Wire Wire Line
	4950 6800 4950 7000
Wire Wire Line
	4950 7000 4950 7250
Wire Wire Line
	5050 3000 4950 3000
Wire Wire Line
	5050 3200 5050 3000
Wire Wire Line
	5050 6800 5050 7000
Wire Wire Line
	5050 7000 4950 7000
Wire Wire Line
	5150 3000 5050 3000
Wire Wire Line
	5150 3200 5150 3000
Wire Wire Line
	5150 6800 5150 7000
Wire Wire Line
	5150 7000 5050 7000
Wire Wire Line
	5250 3000 5150 3000
Wire Wire Line
	5250 3200 5250 3000
Wire Wire Line
	5250 6800 5250 7000
Wire Wire Line
	5250 7000 5150 7000
Wire Wire Line
	5250 7000 5350 7000
Wire Wire Line
	5350 3000 5250 3000
Wire Wire Line
	5350 3200 5350 3000
Wire Wire Line
	5350 7000 5350 6800
Wire Wire Line
	5450 3000 5350 3000
Wire Wire Line
	5450 3200 5450 3000
Wire Wire Line
	6150 1050 6750 1050
Wire Wire Line
	6750 1050 6750 1350
Wire Wire Line
	7200 3350 7500 3350
Wire Wire Line
	7200 3450 7650 3450
Wire Wire Line
	7300 4600 7650 4600
Wire Wire Line
	7300 5000 7300 4600
Wire Wire Line
	7500 2100 7500 2250
Wire Wire Line
	7500 2450 7500 2800
Wire Wire Line
	7500 2800 8500 2800
Wire Wire Line
	7500 3350 7500 2800
Wire Wire Line
	7500 3650 7500 3350
Wire Wire Line
	7650 2100 7500 2100
Wire Wire Line
	7650 2250 7650 2100
Wire Wire Line
	7650 2450 7650 2700
Wire Wire Line
	7650 2700 7650 3450
Wire Wire Line
	7650 3450 7650 3550
Wire Wire Line
	7650 3550 8500 3550
Wire Wire Line
	8000 2500 8500 2500
Wire Wire Line
	8000 2900 8000 2500
Wire Wire Line
	8000 3350 8000 3250
Wire Wire Line
	8000 3450 8500 3450
Wire Wire Line
	8000 3850 8000 3450
Wire Wire Line
	8150 2000 8150 2100
Wire Wire Line
	8150 2100 7650 2100
Wire Wire Line
	8150 2100 8150 2600
Wire Wire Line
	8150 2600 8500 2600
Wire Wire Line
	8500 2700 7650 2700
Wire Wire Line
	8500 3350 8000 3350
Wire Wire Line
	8500 3650 7500 3650
Wire Wire Line
	9700 4650 9700 4800
Wire Wire Line
	9700 5600 9700 5900
Text Notes 2750 4200 0    50   ~ 0
const int D3Pin      = PB3;\nconst int OPPin      = PB4;\n\nconst int SPPin      = PB12;\nconst int CEPin      = PB13;\nconst int VCCPin     = PB14;\nconst int CONTPin    = PB15;\n
Text Notes 3050 1300 0    50   ~ 0
Option to power \ncalculator from \nUSB (FX502P only).\nRemove batteries.
Text Notes 3100 3100 0    50   ~ 0
Option to power calculator\nfrom GPIO line. FX502P only.\nRemove batteries.
Text GLabel 850  2500 1    50   Input ~ 0
CALC_SP
Text GLabel 1050 2500 1    50   Input ~ 0
CALC_OP
Text GLabel 1150 4100 3    50   Input ~ 0
CALC_CONT
Text GLabel 1250 2500 1    50   Input ~ 0
CALC_D3
Text GLabel 1450 2500 1    50   Input ~ 0
CALC_CE
Text GLabel 1850 4350 0    50   Input ~ 0
CALC_GND
Text GLabel 3400 2700 2    50   Input ~ 0
CALC_VCC_GPIO
Text GLabel 3850 4700 0    50   Input ~ 0
OSCI
Text GLabel 3850 4800 0    50   Input ~ 0
OSCO
Text GLabel 4450 3400 0    50   Input ~ 0
NRST
Text GLabel 4450 3600 0    50   Input ~ 0
BOOT0
Text GLabel 5850 3800 2    50   Input ~ 0
SD_CS
Text GLabel 5850 3900 2    50   Input ~ 0
SD_CLK
Text GLabel 5850 4000 2    50   Input ~ 0
SD_MISO
Text GLabel 5850 4100 2    50   Input ~ 0
SD_MOSI
Text GLabel 5850 4300 2    50   Input ~ 0
TX
Text GLabel 5850 4400 2    50   Input ~ 0
RX
Text GLabel 5850 4500 2    50   Input ~ 0
PA11
Text GLabel 5850 4600 2    50   Input ~ 0
PA12
Text GLabel 5850 4700 2    50   Input ~ 0
SWDIO
Text GLabel 5850 4800 2    50   Input ~ 0
SWDCLK
Text GLabel 5850 5300 2    50   Input ~ 0
BOOT1
Text GLabel 5850 5400 2    50   Input ~ 0
CALC_D3
Text GLabel 5850 5500 2    50   Input ~ 0
CALC_OP
Text GLabel 5850 6100 2    50   Input ~ 0
SCL
Text GLabel 5850 6200 2    50   Input ~ 0
SDA
Text GLabel 5850 6300 2    50   Input ~ 0
CALC_SP
Text GLabel 5850 6400 2    50   Input ~ 0
CALC_CE
Text GLabel 5850 6500 2    50   Input ~ 0
CALC_VCC_GPIO
Text GLabel 5850 6600 2    50   Input ~ 0
CALC_CONT
Text GLabel 6150 850  2    50   Input ~ 0
TX
Text GLabel 6150 950  2    50   Input ~ 0
RX
Text GLabel 7200 3350 0    50   Input ~ 0
SDA
Text GLabel 7200 3450 0    50   Input ~ 0
SCL
Text GLabel 7650 4700 0    50   Input ~ 0
SDA
Text GLabel 7650 4800 0    50   Input ~ 0
SCL
Text GLabel 9300 5050 0    50   Input ~ 0
SD_CS
Text GLabel 9300 5150 0    50   Input ~ 0
SD_MOSI
Text GLabel 9300 5250 0    50   Input ~ 0
SD_CLK
Text GLabel 9300 5350 0    50   Input ~ 0
SD_MISO
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6001C4EB
P 950 4000
AR Path="/5FFD1EE0/6001C4EB" Ref="#PWR?"  Part="1" 
AR Path="/6001C4EB" Ref="#PWR0108"  Part="1" 
F 0 "#PWR0108" H 950 4000 30  0001 C CNN
F 1 "GND" H 950 3930 30  0001 C CNN
F 2 "" H 950 4000 60  0000 C CNN
F 3 "" H 950 4000 60  0000 C CNN
F 4 "" H 950 4000 50  0001 C CNN
	1    950  4000
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6001C4B8
P 1900 4650
AR Path="/5FFD1EE0/6001C4B8" Ref="#PWR?"  Part="1" 
AR Path="/6001C4B8" Ref="#PWR0105"  Part="1" 
F 0 "#PWR0105" H 1900 4650 30  0001 C CNN
F 1 "GND" H 1900 4580 30  0001 C CNN
F 2 "" H 1900 4650 60  0000 C CNN
F 3 "" H 1900 4650 60  0000 C CNN
F 4 "" H 1900 4650 50  0001 C CNN
	1    1900 4650
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 600814BC
P 3850 6350
AR Path="/5FFD1EE0/600814BC" Ref="#PWR?"  Part="1" 
AR Path="/600814BC" Ref="#PWR0117"  Part="1" 
F 0 "#PWR0117" H 3850 6350 30  0001 C CNN
F 1 "GND" H 3850 6280 30  0001 C CNN
F 2 "" H 3850 6350 60  0000 C CNN
F 3 "" H 3850 6350 60  0000 C CNN
F 4 "" H 3850 6350 50  0001 C CNN
	1    3850 6350
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6001C48E
P 4950 7250
AR Path="/5FFB81CD/6001C48E" Ref="#PWR?"  Part="1" 
AR Path="/5FFD1EE0/6001C48E" Ref="#PWR?"  Part="1" 
AR Path="/6001C48E" Ref="#PWR0104"  Part="1" 
F 0 "#PWR0104" H 4950 7250 30  0001 C CNN
F 1 "GND" H 4950 7180 30  0001 C CNN
F 2 "" H 4950 7250 60  0000 C CNN
F 3 "" H 4950 7250 60  0000 C CNN
F 4 "" H 4950 7250 50  0001 C CNN
	1    4950 7250
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6001C4DD
P 6750 1350
AR Path="/5FFD1EE0/6001C4DD" Ref="#PWR?"  Part="1" 
AR Path="/6001C4DD" Ref="#PWR0107"  Part="1" 
F 0 "#PWR0107" H 6750 1350 30  0001 C CNN
F 1 "GND" H 6750 1280 30  0001 C CNN
F 2 "" H 6750 1350 60  0000 C CNN
F 3 "" H 6750 1350 60  0000 C CNN
F 4 "" H 6750 1350 50  0001 C CNN
	1    6750 1350
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6004AC4F
P 7300 5000
AR Path="/5FFD1EE0/6004AC4F" Ref="#PWR?"  Part="1" 
AR Path="/6004AC4F" Ref="#PWR0113"  Part="1" 
F 0 "#PWR0113" H 7300 5000 30  0001 C CNN
F 1 "GND" H 7300 4930 30  0001 C CNN
F 2 "" H 7300 5000 60  0000 C CNN
F 3 "" H 7300 5000 60  0000 C CNN
F 4 "" H 7300 5000 50  0001 C CNN
	1    7300 5000
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6001C4FF
P 8000 2900
AR Path="/5FFD1EE0/6001C4FF" Ref="#PWR?"  Part="1" 
AR Path="/6001C4FF" Ref="#PWR0109"  Part="1" 
F 0 "#PWR0109" H 8000 2900 30  0001 C CNN
F 1 "GND" H 8000 2830 30  0001 C CNN
F 2 "" H 8000 2900 60  0000 C CNN
F 3 "" H 8000 2900 60  0000 C CNN
F 4 "" H 8000 2900 50  0001 C CNN
	1    8000 2900
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6001C507
P 8000 3850
AR Path="/5FFD1EE0/6001C507" Ref="#PWR?"  Part="1" 
AR Path="/6001C507" Ref="#PWR0110"  Part="1" 
F 0 "#PWR0110" H 8000 3850 30  0001 C CNN
F 1 "GND" H 8000 3780 30  0001 C CNN
F 2 "" H 8000 3850 60  0000 C CNN
F 3 "" H 8000 3850 60  0000 C CNN
F 4 "" H 8000 3850 50  0001 C CNN
	1    8000 3850
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 6001C45A
P 9700 5900
AR Path="/5FFD1EE0/6001C45A" Ref="#PWR?"  Part="1" 
AR Path="/6001C45A" Ref="#PWR0102"  Part="1" 
F 0 "#PWR0102" H 9700 5900 30  0001 C CNN
F 1 "GND" H 9700 5830 30  0001 C CNN
F 2 "" H 9700 5900 60  0000 C CNN
F 3 "" H 9700 5900 60  0000 C CNN
F 4 "" H 9700 5900 50  0001 C CNN
	1    9700 5900
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:+3V3-power #PWR?
U 1 1 6001C4C7
P 2750 850
AR Path="/5FFD1EE0/6001C4C7" Ref="#PWR?"  Part="1" 
AR Path="/6001C4C7" Ref="#PWR0106"  Part="1" 
F 0 "#PWR0106" H 2750 700 50  0001 C CNN
F 1 "+3V3" H 2765 1023 50  0000 C CNN
F 2 "" H 2750 850 50  0001 C CNN
F 3 "" H 2750 850 50  0001 C CNN
F 4 "" H 2750 850 50  0001 C CNN
	1    2750 850 
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:+3V3-power #PWR?
U 1 1 6007B847
P 3050 5800
AR Path="/5FFD1EE0/6007B847" Ref="#PWR?"  Part="1" 
AR Path="/6007B847" Ref="#PWR0116"  Part="1" 
F 0 "#PWR0116" H 3050 5650 50  0001 C CNN
F 1 "+3V3" H 3065 5973 50  0000 C CNN
F 2 "" H 3050 5800 50  0001 C CNN
F 3 "" H 3050 5800 50  0001 C CNN
F 4 "" H 3050 5800 50  0001 C CNN
	1    3050 5800
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:+3V3-power #PWR?
U 1 1 6001C485
P 4950 2800
AR Path="/5FFB81CD/6001C485" Ref="#PWR?"  Part="1" 
AR Path="/5FFD1EE0/6001C485" Ref="#PWR?"  Part="1" 
AR Path="/6001C485" Ref="#PWR0103"  Part="1" 
F 0 "#PWR0103" H 4950 2650 50  0001 C CNN
F 1 "+3V3" H 4965 2973 50  0000 C CNN
F 2 "" H 4950 2800 50  0001 C CNN
F 3 "" H 4950 2800 50  0001 C CNN
F 4 "" H 4950 2800 50  0001 C CNN
	1    4950 2800
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:+3V3-power #PWR?
U 1 1 6001C515
P 8000 3250
AR Path="/5FFD1EE0/6001C515" Ref="#PWR?"  Part="1" 
AR Path="/6001C515" Ref="#PWR0112"  Part="1" 
F 0 "#PWR0112" H 8000 3100 50  0001 C CNN
F 1 "+3V3" H 8015 3423 50  0000 C CNN
F 2 "" H 8000 3250 50  0001 C CNN
F 3 "" H 8000 3250 50  0001 C CNN
F 4 "" H 8000 3250 50  0001 C CNN
	1    8000 3250
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:+3V3-power #PWR?
U 1 1 6001C50F
P 8150 2000
AR Path="/5FFD1EE0/6001C50F" Ref="#PWR?"  Part="1" 
AR Path="/6001C50F" Ref="#PWR0111"  Part="1" 
F 0 "#PWR0111" H 8150 1850 50  0001 C CNN
F 1 "+3V3" H 8150 2150 50  0000 C CNN
F 2 "" H 8150 2000 50  0001 C CNN
F 3 "" H 8150 2000 50  0001 C CNN
F 4 "" H 8150 2000 50  0001 C CNN
	1    8150 2000
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:+5V-power #PWR?
U 1 1 6001C453
P 9700 4650
AR Path="/5FFD1EE0/6001C453" Ref="#PWR?"  Part="1" 
AR Path="/6001C453" Ref="#PWR0101"  Part="1" 
F 0 "#PWR0101" H 9700 4500 50  0001 C CNN
F 1 "+5V" H 9715 4823 50  0000 C CNN
F 2 "" H 9700 4650 50  0001 C CNN
F 3 "" H 9700 4650 50  0001 C CNN
F 4 "" H 9700 4650 50  0001 C CNN
	1    9700 4650
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C542
P 850 2750
AR Path="/5FFD1EE0/6001C542" Ref="R?"  Part="1" 
AR Path="/6001C542" Ref="R1"  Part="1" 
F 0 "R1" V 850 3450 50  0000 C CNN
F 1 "1k" V 850 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 850 2750 50  0001 C CNN
F 3 "~" H 850 2750 50  0001 C CNN
F 4 "" H 850 2750 50  0001 C CNN
	1    850  2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C53C
P 1050 2750
AR Path="/5FFD1EE0/6001C53C" Ref="R?"  Part="1" 
AR Path="/6001C53C" Ref="R2"  Part="1" 
F 0 "R2" V 1050 3450 50  0000 C CNN
F 1 "1k" V 1050 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1050 2750 50  0001 C CNN
F 3 "~" H 1050 2750 50  0001 C CNN
F 4 "" H 1050 2750 50  0001 C CNN
	1    1050 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C536
P 1150 3850
AR Path="/5FFD1EE0/6001C536" Ref="R?"  Part="1" 
AR Path="/6001C536" Ref="R3"  Part="1" 
F 0 "R3" V 1350 4500 50  0000 C CNN
F 1 "1k" V 1250 4400 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1150 3850 50  0001 C CNN
F 3 "~" H 1150 3850 50  0001 C CNN
F 4 "" H 1150 3850 50  0001 C CNN
	1    1150 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C530
P 1250 2750
AR Path="/5FFD1EE0/6001C530" Ref="R?"  Part="1" 
AR Path="/6001C530" Ref="R4"  Part="1" 
F 0 "R4" V 1250 3450 50  0000 C CNN
F 1 "1k" V 1250 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1250 2750 50  0001 C CNN
F 3 "~" H 1250 2750 50  0001 C CNN
F 4 "" H 1250 2750 50  0001 C CNN
	1    1250 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C524
P 1450 2750
AR Path="/5FFD1EE0/6001C524" Ref="R?"  Part="1" 
AR Path="/6001C524" Ref="R5"  Part="1" 
F 0 "R5" V 1450 3450 50  0000 C CNN
F 1 "1k" V 1450 3700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1450 2750 50  0001 C CNN
F 3 "~" H 1450 2750 50  0001 C CNN
F 4 "" H 1450 2750 50  0001 C CNN
	1    1450 2750
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C52A
P 2150 2700
AR Path="/5FFD1EE0/6001C52A" Ref="R?"  Part="1" 
AR Path="/6001C52A" Ref="R6"  Part="1" 
F 0 "R6" V 1954 2700 50  0000 C CNN
F 1 "0R" V 2045 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 2150 2700 50  0001 C CNN
F 3 "~" H 2150 2700 50  0001 C CNN
F 4 "" H 2150 2700 50  0001 C CNN
	1    2150 2700
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C46A
P 4150 4800
AR Path="/5FFB81CD/6001C46A" Ref="R?"  Part="1" 
AR Path="/5FFD1EE0/6001C46A" Ref="R?"  Part="1" 
AR Path="/6001C46A" Ref="R7"  Part="1" 
F 0 "R7" V 4100 4900 50  0000 L CNN
F 1 "390R" V 4000 4800 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4150 4800 50  0001 C CNN
F 3 "~" H 4150 4800 50  0001 C CNN
F 4 "" H 4150 4800 50  0001 C CNN
	1    4150 4800
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C555
P 7500 2350
AR Path="/5FFD1EE0/6001C555" Ref="R?"  Part="1" 
AR Path="/6001C555" Ref="R8"  Part="1" 
F 0 "R8" H 7100 2400 50  0000 L CNN
F 1 "4k7" H 7050 2300 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7500 2350 50  0001 C CNN
F 3 "~" H 7500 2350 50  0001 C CNN
F 4 "" H 7500 2350 50  0001 C CNN
	1    7500 2350
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R?
U 1 1 6001C55B
P 7650 2350
AR Path="/5FFD1EE0/6001C55B" Ref="R?"  Part="1" 
AR Path="/6001C55B" Ref="R9"  Part="1" 
F 0 "R9" H 7750 2450 50  0000 L CNN
F 1 "4k7" H 7750 2350 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 7650 2350 50  0001 C CNN
F 3 "~" H 7650 2350 50  0001 C CNN
F 4 "" H 7650 2350 50  0001 C CNN
	1    7650 2350
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Conn_01x02_Male-Connector J?
U 1 1 6001C4CF
P 2550 1200
AR Path="/5FFD1EE0/6001C4CF" Ref="J?"  Part="1" 
AR Path="/6001C4CF" Ref="J1"  Part="1" 
F 0 "J1" H 2658 1381 50  0000 C CNN
F 1 "Conn_01x02_Male" H 2658 1290 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2550 1200 50  0001 C CNN
F 3 "~" H 2550 1200 50  0001 C CNN
F 4 "" H 2550 1200 50  0001 C CNN
	1    2550 1200
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Conn_01x02_Male-Connector J?
U 1 1 6001C56D
P 3200 2350
AR Path="/5FFD1EE0/6001C56D" Ref="J?"  Part="1" 
AR Path="/6001C56D" Ref="J2"  Part="1" 
F 0 "J2" V 3262 2394 50  0000 L CNN
F 1 "Conn_01x02_Male" V 3353 2394 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3200 2350 50  0001 C CNN
F 3 "~" H 3200 2350 50  0001 C CNN
F 4 "" H 3200 2350 50  0001 C CNN
	1    3200 2350
	0    1    1    0   
$EndComp
$Comp
L Device:D D?
U 1 1 6001C4C1
P 2750 1850
AR Path="/5FFD1EE0/6001C4C1" Ref="D?"  Part="1" 
AR Path="/6001C4C1" Ref="D1"  Part="1" 
F 0 "D1" V 2796 1770 50  0000 R CNN
F 1 "1N4148" V 2705 1770 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323_HandSoldering" H 2750 1850 50  0001 C CNN
F 3 "~" H 2750 1850 50  0001 C CNN
F 4 "" H 2750 1850 50  0001 C CNN
	1    2750 1850
	0    -1   -1   0   
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Conn_01x03_Female-Connector J?
U 1 1 6001C4D7
P 5950 950
AR Path="/5FFD1EE0/6001C4D7" Ref="J?"  Part="1" 
AR Path="/6001C4D7" Ref="J3"  Part="1" 
F 0 "J3" H 5978 976 50  0000 L CNN
F 1 "Conn_01x03_Female" H 5978 885 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 5950 950 50  0001 C CNN
F 3 "~" H 5950 950 50  0001 C CNN
F 4 "" H 5950 950 50  0001 C CNN
	1    5950 950 
	-1   0    0    1   
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Conn_01x03_Female-Connector J6
U 1 1 600482FB
P 7850 4700
F 0 "J6" H 7878 4726 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7878 4635 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7850 4700 50  0001 C CNN
F 3 "~" H 7850 4700 50  0001 C CNN
F 4 "" H 7850 4700 50  0001 C CNN
	1    7850 4700
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Conn_01x04_Male-Connector J?
U 1 1 6001C4F3
P 8700 2700
AR Path="/5FFD1EE0/6001C4F3" Ref="J?"  Part="1" 
AR Path="/6001C4F3" Ref="J4"  Part="1" 
F 0 "J4" H 8808 2981 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8550 2300 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8700 2700 50  0001 C CNN
F 3 "~" H 8700 2700 50  0001 C CNN
F 4 "" H 8700 2700 50  0001 C CNN
	1    8700 2700
	-1   0    0    1   
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Conn_01x04_Male-Connector J?
U 1 1 6001C4F9
P 8700 3550
AR Path="/5FFD1EE0/6001C4F9" Ref="J?"  Part="1" 
AR Path="/6001C4F9" Ref="J5"  Part="1" 
F 0 "J5" H 8808 3831 50  0000 C CNN
F 1 "Conn_01x04_Male" H 8850 3150 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8700 3550 50  0001 C CNN
F 3 "~" H 8700 3550 50  0001 C CNN
F 4 "" H 8700 3550 50  0001 C CNN
	1    8700 3550
	-1   0    0    1   
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Conn_01x10_Female-Connector J7
U 1 1 600643D2
P 3600 5600
F 0 "J7" H 3492 4875 50  0000 C CNN
F 1 "Conn_01x10_Female" H 3492 4966 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 3600 5600 50  0001 C CNN
F 3 "~" H 3600 5600 50  0001 C CNN
F 4 "" H 3600 5600 50  0001 C CNN
	1    3600 5600
	-1   0    0    1   
$EndComp
$Comp
L fx502p-minimal-sd-rescue:Expansion-fx502p P?
U 1 1 6001C579
P 1250 3400
AR Path="/5FFD1EE0/6001C579" Ref="P?"  Part="1" 
AR Path="/6001C579" Ref="P1"  Part="1" 
F 0 "P1" H 1578 3767 50  0000 L CNN
F 1 "Expansion" H 1578 3676 50  0000 L CNN
F 2 "ajm_kicad:expansion_fx502p" H 1250 3400 50  0001 C CNN
F 3 "" H 1250 3400 50  0001 C CNN
F 4 "" H 1250 3400 50  0001 C CNN
	1    1250 3400
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:SD_Card_Module_catalex-Charleslabs_Parts A?
U 1 1 6001C44B
P 9700 5200
AR Path="/5FFD1EE0/6001C44B" Ref="A?"  Part="1" 
AR Path="/6001C44B" Ref="A1"  Part="1" 
F 0 "A1" H 10030 5246 50  0000 L CNN
F 1 "SD_Card_Module_catalex" H 10030 5155 50  0000 L CNN
F 2 "Charleslabs_Parts:SD_Card_Module" H 10650 5250 50  0001 C CNN
F 3 "" H 9400 5550 50  0001 C CNN
F 4 "" H 9700 5200 50  0001 C CNN
	1    9700 5200
	1    0    0    -1  
$EndComp
$Comp
L fx502p-minimal-sd-rescue:STM32F103RGTx-MCU_ST_STM32F1 U?
U 1 1 6001C460
P 5150 5000
AR Path="/5FFB81CD/6001C460" Ref="U?"  Part="1" 
AR Path="/5FFD1EE0/6001C460" Ref="U?"  Part="1" 
AR Path="/6001C460" Ref="U1"  Part="1" 
F 0 "U1" H 5150 3111 50  0000 C CNN
F 1 "STM32F103RGTx" H 5900 7000 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 4550 3300 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00253742.pdf" H 5150 5000 50  0001 C CNN
F 4 "" H 5150 5000 50  0001 C CNN
	1    5150 5000
	1    0    0    -1  
$EndComp
$Sheet
S 9850 900  1000 500 
U 5FFD1EE0
F0 "large sd" 50
F1 "fx502p-sd-pcb-1.sch" 50
$EndSheet
$Sheet
S 9850 1750 1000 500 
U 5FFD222D
F0 "stm support2" 50
F1 "stm_support.sch" 50
$EndSheet
$EndSCHEMATC
