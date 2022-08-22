EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 2
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Charleslabs_Parts:SD_Card_Module_catalex A1
U 1 1 5FFAAEE7
P 9850 5550
F 0 "A1" H 10180 5596 50  0000 L CNN
F 1 "SD_Card_Module_catalex" H 10180 5505 50  0000 L CNN
F 2 "Charleslabs_Parts:SD_Card_Module" H 10800 5600 50  0001 C CNN
F 3 "" H 9550 5900 50  0001 C CNN
	1    9850 5550
	1    0    0    -1  
$EndComp
$Sheet
S 10250 1650 500  400 
U 5FFAC35B
F0 "STM Support" 50
F1 "stm_support.sch" 50
$EndSheet
$Comp
L power:+5V #PWR025
U 1 1 5FFB0150
P 9850 5000
F 0 "#PWR025" H 9850 4850 50  0001 C CNN
F 1 "+5V" H 9865 5173 50  0000 C CNN
F 2 "" H 9850 5000 50  0001 C CNN
F 3 "" H 9850 5000 50  0001 C CNN
	1    9850 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9850 5000 9850 5150
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR026
U 1 1 5FFB06E6
P 9850 6250
F 0 "#PWR026" H 9850 6250 30  0001 C CNN
F 1 "GND" H 9850 6180 30  0001 C CNN
F 2 "" H 9850 6250 60  0000 C CNN
F 3 "" H 9850 6250 60  0000 C CNN
	1    9850 6250
	1    0    0    -1  
$EndComp
$Comp
L MCU_ST_STM32F1:STM32F103RGTx U?
U 1 1 5FFC10B6
P 5150 5300
AR Path="/5FFB81CD/5FFC10B6" Ref="U?"  Part="1" 
AR Path="/5FFC10B6" Ref="U2"  Part="1" 
F 0 "U2" H 5150 3411 50  0000 C CNN
F 1 "STM32F103RGTx" H 5900 7300 50  0000 C CNN
F 2 "Package_QFP:LQFP-64_10x10mm_P0.5mm" H 4550 3600 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00253742.pdf" H 5150 5300 50  0001 C CNN
	1    5150 5300
	1    0    0    -1  
$EndComp
Text GLabel 5850 5000 2    50   Input ~ 0
SWDIO
Text GLabel 5850 5100 2    50   Input ~ 0
SWDCLK
Text GLabel 5850 6400 2    50   Input ~ 0
SCL
Text GLabel 5850 6500 2    50   Input ~ 0
SDA
$Comp
L Device:R_Small R?
U 1 1 5FFC10D6
P 4150 5100
AR Path="/5FFB81CD/5FFC10D6" Ref="R?"  Part="1" 
AR Path="/5FFC10D6" Ref="R7"  Part="1" 
F 0 "R7" V 4100 5200 50  0000 L CNN
F 1 "390R" V 4000 5100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 4150 5100 50  0001 C CNN
F 3 "~" H 4150 5100 50  0001 C CNN
	1    4150 5100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4250 5100 4450 5100
Text GLabel 3850 5100 0    50   Input ~ 0
OSCO
Text GLabel 3850 5000 0    50   Input ~ 0
OSCI
Wire Wire Line
	3850 5000 4450 5000
Wire Wire Line
	3850 5100 4050 5100
Text GLabel 4450 3900 0    50   Input ~ 0
BOOT0
Text GLabel 4450 3700 0    50   Input ~ 0
NRST
Wire Wire Line
	4950 3500 4950 3300
Wire Wire Line
	5350 3500 5350 3300
Wire Wire Line
	5350 3300 5250 3300
Connection ~ 4950 3300
Wire Wire Line
	4950 3300 4950 3100
Wire Wire Line
	5250 3500 5250 3300
Connection ~ 5250 3300
Wire Wire Line
	5250 3300 5150 3300
Wire Wire Line
	5150 3500 5150 3300
Connection ~ 5150 3300
Wire Wire Line
	5150 3300 5050 3300
Wire Wire Line
	5050 3500 5050 3300
Connection ~ 5050 3300
Wire Wire Line
	5050 3300 4950 3300
$Comp
L power:+3V3 #PWR?
U 1 1 5FFC10F1
P 4950 3100
AR Path="/5FFB81CD/5FFC10F1" Ref="#PWR?"  Part="1" 
AR Path="/5FFC10F1" Ref="#PWR013"  Part="1" 
F 0 "#PWR013" H 4950 2950 50  0001 C CNN
F 1 "+3V3" H 4965 3273 50  0000 C CNN
F 2 "" H 4950 3100 50  0001 C CNN
F 3 "" H 4950 3100 50  0001 C CNN
	1    4950 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 3500 5450 3300
Wire Wire Line
	5450 3300 5350 3300
Connection ~ 5350 3300
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 5FFC10FA
P 4950 7550
AR Path="/5FFB81CD/5FFC10FA" Ref="#PWR?"  Part="1" 
AR Path="/5FFC10FA" Ref="#PWR014"  Part="1" 
F 0 "#PWR014" H 4950 7550 30  0001 C CNN
F 1 "GND" H 4950 7480 30  0001 C CNN
F 2 "" H 4950 7550 60  0000 C CNN
F 3 "" H 4950 7550 60  0000 C CNN
	1    4950 7550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 7100 4950 7300
Wire Wire Line
	5050 7100 5050 7300
Wire Wire Line
	5050 7300 4950 7300
Connection ~ 4950 7300
Wire Wire Line
	4950 7300 4950 7550
Wire Wire Line
	5150 7100 5150 7300
Wire Wire Line
	5150 7300 5050 7300
Connection ~ 5050 7300
Wire Wire Line
	5250 7100 5250 7300
Wire Wire Line
	5250 7300 5150 7300
Connection ~ 5150 7300
Wire Wire Line
	5250 7300 5350 7300
Wire Wire Line
	5350 7300 5350 7100
Connection ~ 5250 7300
Text GLabel 5850 5600 2    50   Input ~ 0
BOOT1
$Comp
L Timer:MCP7940N-xSN U?
U 1 1 60007C55
P 4000 1950
AR Path="/5FFB81CD/60007C55" Ref="U?"  Part="1" 
AR Path="/60007C55" Ref="U1"  Part="1" 
F 0 "U1" H 4400 1650 50  0000 C CNN
F 1 "MCP7940N-xSN" H 4400 1550 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 4000 1950 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/20005010F.pdf" H 4000 1950 50  0001 C CNN
	1    4000 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4100 1400 4100 1550
$Comp
L power:+3V3 #PWR?
U 1 1 60007C5C
P 4000 1000
AR Path="/5FFB81CD/60007C5C" Ref="#PWR?"  Part="1" 
AR Path="/60007C5C" Ref="#PWR010"  Part="1" 
F 0 "#PWR010" H 4000 850 50  0001 C CNN
F 1 "+3V3" H 4015 1173 50  0000 C CNN
F 2 "" H 4000 1000 50  0001 C CNN
F 3 "" H 4000 1000 50  0001 C CNN
	1    4000 1000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 1000 4000 1150
$Comp
L power:GND #PWR?
U 1 1 60007C63
P 4000 2750
AR Path="/5FFB81CD/60007C63" Ref="#PWR?"  Part="1" 
AR Path="/60007C63" Ref="#PWR011"  Part="1" 
F 0 "#PWR011" H 4000 2500 50  0001 C CNN
F 1 "GND" H 4005 2577 50  0000 C CNN
F 2 "" H 4000 2750 50  0001 C CNN
F 3 "" H 4000 2750 50  0001 C CNN
	1    4000 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 2750 4000 2350
$Comp
L fx502p-sd-pcb-1-rescue:XTAL-Microtan_exp X?
U 1 1 60007C71
P 5050 1950
AR Path="/5FFB81CD/60007C71" Ref="X?"  Part="1" 
AR Path="/60007C71" Ref="X1"  Part="1" 
F 0 "X1" V 4997 2073 60  0000 L CNN
F 1 "32.768kHz" V 5103 2073 60  0000 L CNN
F 2 "Crystal:Crystal_SMD_3215-2Pin_3.2x1.5mm" H 5050 1950 60  0001 C CNN
F 3 "" H 5050 1950 60  0000 C CNN
	1    5050 1950
	0    1    1    0   
$EndComp
Wire Wire Line
	5050 2150 5050 2250
Wire Wire Line
	5050 2250 4650 2250
Wire Wire Line
	4650 2250 4650 2050
Wire Wire Line
	4650 2050 4400 2050
Wire Wire Line
	4400 1850 4650 1850
Wire Wire Line
	4650 1850 4650 1650
Wire Wire Line
	4650 1650 5050 1650
Wire Wire Line
	5050 1650 5050 1750
$Comp
L Device:C_Small C?
U 1 1 60007C7F
P 5050 2500
AR Path="/5FFB81CD/60007C7F" Ref="C?"  Part="1" 
AR Path="/60007C7F" Ref="C3"  Part="1" 
F 0 "C3" H 5142 2546 50  0000 L CNN
F 1 "10pF" H 5142 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5050 2500 50  0001 C CNN
F 3 "~" H 5050 2500 50  0001 C CNN
	1    5050 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60007C85
P 5700 2500
AR Path="/5FFB81CD/60007C85" Ref="C?"  Part="1" 
AR Path="/60007C85" Ref="C4"  Part="1" 
F 0 "C4" H 5792 2546 50  0000 L CNN
F 1 "10pF" H 5792 2455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5700 2500 50  0001 C CNN
F 3 "~" H 5700 2500 50  0001 C CNN
	1    5700 2500
	1    0    0    -1  
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 60007C91
P 5050 2750
AR Path="/5FFB81CD/60007C91" Ref="#PWR?"  Part="1" 
AR Path="/60007C91" Ref="#PWR015"  Part="1" 
F 0 "#PWR015" H 5050 2750 30  0001 C CNN
F 1 "GND" H 5050 2680 30  0001 C CNN
F 2 "" H 5050 2750 60  0000 C CNN
F 3 "" H 5050 2750 60  0000 C CNN
	1    5050 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2750 5050 2600
Wire Wire Line
	5700 2750 5700 2600
Wire Wire Line
	5050 2400 5050 2250
Connection ~ 5050 2250
Wire Wire Line
	5700 2400 5700 1650
Wire Wire Line
	5700 1650 5050 1650
Connection ~ 5050 1650
$Comp
L Device:C_Small C?
U 1 1 60007C9E
P 3000 1650
AR Path="/5FFB81CD/60007C9E" Ref="C?"  Part="1" 
AR Path="/60007C9E" Ref="C1"  Part="1" 
F 0 "C1" H 3092 1696 50  0000 L CNN
F 1 "100nF" H 3092 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3000 1650 50  0001 C CNN
F 3 "~" H 3000 1650 50  0001 C CNN
	1    3000 1650
	1    0    0    -1  
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 60007CA4
P 3000 1900
AR Path="/5FFB81CD/60007CA4" Ref="#PWR?"  Part="1" 
AR Path="/60007CA4" Ref="#PWR07"  Part="1" 
F 0 "#PWR07" H 3000 1900 30  0001 C CNN
F 1 "GND" H 3000 1830 30  0001 C CNN
F 2 "" H 3000 1900 60  0000 C CNN
F 3 "" H 3000 1900 60  0000 C CNN
	1    3000 1900
	1    0    0    -1  
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 60007CAA
P 4500 1450
AR Path="/5FFB81CD/60007CAA" Ref="#PWR?"  Part="1" 
AR Path="/60007CAA" Ref="#PWR012"  Part="1" 
F 0 "#PWR012" H 4500 1450 30  0001 C CNN
F 1 "GND" H 4500 1380 30  0001 C CNN
F 2 "" H 4500 1450 60  0000 C CNN
F 3 "" H 4500 1450 60  0000 C CNN
	1    4500 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C?
U 1 1 60007CB0
P 4500 1250
AR Path="/5FFB81CD/60007CB0" Ref="C?"  Part="1" 
AR Path="/60007CB0" Ref="C2"  Part="1" 
F 0 "C2" H 4592 1296 50  0000 L CNN
F 1 "100nF" H 4592 1205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4500 1250 50  0001 C CNN
F 3 "~" H 4500 1250 50  0001 C CNN
	1    4500 1250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 1150 4000 1150
Connection ~ 4000 1150
Wire Wire Line
	4000 1150 4000 1300
Wire Wire Line
	4500 1350 4500 1450
Wire Wire Line
	3000 1550 3000 1400
Wire Wire Line
	3000 1750 3000 1900
Text GLabel 3450 1850 0    50   Input ~ 0
SDA
Text GLabel 3450 1750 0    50   Input ~ 0
SCL
Wire Wire Line
	3600 1750 3450 1750
Wire Wire Line
	3600 1850 3450 1850
Text GLabel 3600 2050 0    50   Input ~ 0
RTC_MFP
Text GLabel 5850 4800 2    50   Input ~ 0
PA11
Text GLabel 5850 4900 2    50   Input ~ 0
PA12
Text GLabel 9450 5400 0    50   Input ~ 0
SD_CS
Text GLabel 9450 5500 0    50   Input ~ 0
SD_MOSI
Text GLabel 9450 5600 0    50   Input ~ 0
SD_CLK
Text GLabel 9450 5700 0    50   Input ~ 0
SD_MISO
Wire Wire Line
	9850 5950 9850 6250
Text GLabel 5850 4100 2    50   Input ~ 0
SD_CS
Text GLabel 5850 4400 2    50   Input ~ 0
SD_MOSI
Text GLabel 5850 4200 2    50   Input ~ 0
SD_CLK
Text GLabel 5850 4300 2    50   Input ~ 0
SD_MISO
Text GLabel 5850 4700 2    50   Input ~ 0
RX
Text GLabel 5850 4600 2    50   Input ~ 0
TX
Text Notes 2750 4500 0    50   ~ 0
const int D3Pin      = PB3;\nconst int OPPin      = PB4;\n\nconst int SPPin      = PB12;\nconst int CEPin      = PB13;\nconst int VCCPin     = PB14;\nconst int CONTPin    = PB15;\n
Text GLabel 5850 5700 2    50   Input ~ 0
CALC_D3
Text GLabel 5850 5800 2    50   Input ~ 0
CALC_OP
Text GLabel 5850 6600 2    50   Input ~ 0
CALC_SP
Text GLabel 5850 6700 2    50   Input ~ 0
CALC_CE
Text GLabel 5850 6800 2    50   Input ~ 0
CALC_VCC
Text GLabel 5850 6900 2    50   Input ~ 0
CALC_CONT
Text GLabel 1300 6900 0    50   Input ~ 0
CALC_GND
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR02
U 1 1 6003805B
P 1350 7200
F 0 "#PWR02" H 1350 7200 30  0001 C CNN
F 1 "GND" H 1350 7130 30  0001 C CNN
F 2 "" H 1350 7200 60  0000 C CNN
F 3 "" H 1350 7200 60  0000 C CNN
	1    1350 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 6900 1350 6900
Wire Wire Line
	1350 6900 1350 7200
Text GLabel 1300 6500 0    50   Input ~ 0
CALC_VCC
$Comp
L Device:D D1
U 1 1 6003BF58
P 1350 6250
F 0 "D1" V 1396 6170 50  0000 R CNN
F 1 "D" V 1305 6170 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-323" H 1350 6250 50  0001 C CNN
F 3 "~" H 1350 6250 50  0001 C CNN
	1    1350 6250
	0    -1   -1   0   
$EndComp
$Comp
L power:+3V3 #PWR01
U 1 1 6003CF7F
P 1350 5250
F 0 "#PWR01" H 1350 5100 50  0001 C CNN
F 1 "+3V3" H 1365 5423 50  0000 C CNN
F 2 "" H 1350 5250 50  0001 C CNN
F 3 "" H 1350 5250 50  0001 C CNN
	1    1350 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 6400 1350 6500
Wire Wire Line
	1350 6500 1300 6500
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 60042212
P 1150 5600
F 0 "J1" H 1258 5781 50  0000 C CNN
F 1 "Conn_01x02_Male" H 1258 5690 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 1150 5600 50  0001 C CNN
F 3 "~" H 1150 5600 50  0001 C CNN
	1    1150 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1350 5250 1350 5600
Wire Wire Line
	1350 5700 1350 6100
$Comp
L Connector:Conn_01x03_Female J3
U 1 1 60046DDF
P 7250 2550
F 0 "J3" H 7278 2576 50  0000 L CNN
F 1 "Conn_01x03_Female" H 7278 2485 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7250 2550 50  0001 C CNN
F 3 "~" H 7250 2550 50  0001 C CNN
	1    7250 2550
	-1   0    0    1   
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR03
U 1 1 60048E05
P 8050 2950
F 0 "#PWR03" H 8050 2950 30  0001 C CNN
F 1 "GND" H 8050 2880 30  0001 C CNN
F 2 "" H 8050 2950 60  0000 C CNN
F 3 "" H 8050 2950 60  0000 C CNN
	1    8050 2950
	1    0    0    -1  
$EndComp
Text GLabel 7450 2550 2    50   Input ~ 0
RX
Text GLabel 7450 2450 2    50   Input ~ 0
TX
$Comp
L Device:Battery_Cell BT1
U 1 1 6004D705
P 2350 2250
F 0 "BT1" H 2468 2346 50  0000 L CNN
F 1 "Battery_Cell" H 2468 2255 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_1060_1x2032" V 2350 2310 50  0001 C CNN
F 3 "~" V 2350 2310 50  0001 C CNN
	1    2350 2250
	1    0    0    -1  
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR04
U 1 1 6004E771
P 2350 2400
F 0 "#PWR04" H 2350 2400 30  0001 C CNN
F 1 "GND" H 2350 2330 30  0001 C CNN
F 2 "" H 2350 2400 60  0000 C CNN
F 3 "" H 2350 2400 60  0000 C CNN
	1    2350 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 2400 2350 2350
$Comp
L Connector:Conn_01x03_Male J4
U 1 1 60051DFB
P 1750 1400
F 0 "J4" H 1500 1650 50  0000 L CNN
F 1 "Conn_01x03_Male" H 1500 1750 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 1750 1400 50  0001 C CNN
F 3 "~" H 1750 1400 50  0001 C CNN
	1    1750 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3000 1400 4100 1400
Wire Wire Line
	2350 1500 1950 1500
Wire Wire Line
	2350 1500 2350 2050
Wire Wire Line
	1950 1400 3000 1400
Connection ~ 3000 1400
Wire Wire Line
	1950 1300 4000 1300
Connection ~ 4000 1300
Wire Wire Line
	4000 1300 4000 1550
Text GLabel 850  2800 1    50   Input ~ 0
CALC_SP
Text GLabel 1450 2800 1    50   Input ~ 0
CALC_CE
Text GLabel 3400 3000 2    50   Input ~ 0
CALC_VCC
Text GLabel 1150 4400 3    50   Input ~ 0
CALC_CONT
Text GLabel 1250 2800 1    50   Input ~ 0
CALC_D3
Text GLabel 1050 2800 1    50   Input ~ 0
CALC_OP
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR06
U 1 1 6006A9F7
P 950 4300
F 0 "#PWR06" H 950 4300 30  0001 C CNN
F 1 "GND" H 950 4230 30  0001 C CNN
F 2 "" H 950 4300 60  0000 C CNN
F 3 "" H 950 4300 60  0000 C CNN
	1    950  4300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8050 2650 8050 2950
Wire Wire Line
	7450 2650 8050 2650
$Comp
L Connector:Conn_01x10_Male J6
U 1 1 60070A05
P 2850 6600
F 0 "J6" H 2600 5800 50  0000 C CNN
F 1 "Conn_01x10_Male" H 2900 5900 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 2850 6600 50  0001 C CNN
F 3 "~" H 2850 6600 50  0001 C CNN
	1    2850 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	3050 6200 4450 6200
Wire Wire Line
	4450 6300 3050 6300
Wire Wire Line
	3050 6400 4450 6400
Wire Wire Line
	4450 6500 3050 6500
Wire Wire Line
	3050 6600 4450 6600
Wire Wire Line
	4450 6700 3050 6700
Wire Wire Line
	3050 6800 4450 6800
Wire Wire Line
	4450 6900 3050 6900
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR08
U 1 1 60085A8E
P 3200 7150
F 0 "#PWR08" H 3200 7150 30  0001 C CNN
F 1 "GND" H 3200 7080 30  0001 C CNN
F 2 "" H 3200 7150 60  0000 C CNN
F 3 "" H 3200 7150 60  0000 C CNN
	1    3200 7150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 7150 3200 7100
Wire Wire Line
	3200 7100 3050 7100
$Comp
L power:+3V3 #PWR09
U 1 1 6008D098
P 3350 5000
F 0 "#PWR09" H 3350 4850 50  0001 C CNN
F 1 "+3V3" H 3365 5173 50  0000 C CNN
F 2 "" H 3350 5000 50  0001 C CNN
F 3 "" H 3350 5000 50  0001 C CNN
	1    3350 5000
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x10_Male J5
U 1 1 600A5844
P 2350 5800
F 0 "J5" H 1950 6400 50  0000 C CNN
F 1 "Conn_01x10_Male" H 2200 6500 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x10_P2.54mm_Vertical" H 2350 5800 50  0001 C CNN
F 3 "~" H 2350 5800 50  0001 C CNN
	1    2350 5800
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 5400 4450 5400
Wire Wire Line
	4450 5500 2550 5500
Wire Wire Line
	2550 5600 4450 5600
Wire Wire Line
	4450 5700 2550 5700
Wire Wire Line
	2550 5800 4450 5800
Wire Wire Line
	4450 5900 2550 5900
Wire Wire Line
	2550 6000 4450 6000
Wire Wire Line
	4450 6100 2550 6100
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR05
U 1 1 600A841C
P 2700 6350
F 0 "#PWR05" H 2700 6350 30  0001 C CNN
F 1 "GND" H 2700 6280 30  0001 C CNN
F 2 "" H 2700 6350 60  0000 C CNN
F 3 "" H 2700 6350 60  0000 C CNN
	1    2700 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 6350 2700 6300
Wire Wire Line
	2700 6300 2550 6300
Wire Wire Line
	3350 7000 3050 7000
Wire Wire Line
	3350 5300 2700 5300
Wire Wire Line
	2700 5300 2700 6200
Wire Wire Line
	2700 6200 2550 6200
Wire Wire Line
	3350 5000 3350 5300
Connection ~ 3350 5300
Wire Wire Line
	3350 5300 3350 7000
$Comp
L Connector:Conn_01x04_Male J10
U 1 1 600D77C1
P 9250 1450
F 0 "J10" H 9358 1731 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9100 1050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9250 1450 50  0001 C CNN
F 3 "~" H 9250 1450 50  0001 C CNN
	1    9250 1450
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x04_Male J11
U 1 1 600E5924
P 9250 2300
F 0 "J11" H 9358 2581 50  0000 C CNN
F 1 "Conn_01x04_Male" H 9400 1900 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 9250 2300 50  0001 C CNN
F 3 "~" H 9250 2300 50  0001 C CNN
	1    9250 2300
	-1   0    0    1   
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR021
U 1 1 600EAC67
P 8550 1650
F 0 "#PWR021" H 8550 1650 30  0001 C CNN
F 1 "GND" H 8550 1580 30  0001 C CNN
F 2 "" H 8550 1650 60  0000 C CNN
F 3 "" H 8550 1650 60  0000 C CNN
	1    8550 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 1650 8550 1250
Wire Wire Line
	8550 1250 9050 1250
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR023
U 1 1 600EE7BA
P 8550 2600
F 0 "#PWR023" H 8550 2600 30  0001 C CNN
F 1 "GND" H 8550 2530 30  0001 C CNN
F 2 "" H 8550 2600 60  0000 C CNN
F 3 "" H 8550 2600 60  0000 C CNN
	1    8550 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 2600 8550 2200
Wire Wire Line
	8550 2200 9050 2200
$Comp
L power:+3V3 #PWR024
U 1 1 600F2A27
P 8700 750
F 0 "#PWR024" H 8700 600 50  0001 C CNN
F 1 "+3V3" H 8700 900 50  0000 C CNN
F 2 "" H 8700 750 50  0001 C CNN
F 3 "" H 8700 750 50  0001 C CNN
	1    8700 750 
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR022
U 1 1 600F39D9
P 8550 2000
F 0 "#PWR022" H 8550 1850 50  0001 C CNN
F 1 "+3V3" H 8565 2173 50  0000 C CNN
F 2 "" H 8550 2000 50  0001 C CNN
F 3 "" H 8550 2000 50  0001 C CNN
	1    8550 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	9050 2100 8550 2100
Wire Wire Line
	8550 2100 8550 2000
Wire Wire Line
	8700 1350 9050 1350
Wire Wire Line
	9050 1450 8200 1450
Wire Wire Line
	8200 1450 8200 2200
Wire Wire Line
	8200 2300 9050 2300
Wire Wire Line
	9050 2400 8050 2400
Wire Wire Line
	8050 2400 8050 2100
Wire Wire Line
	8050 1550 9050 1550
$Comp
L Device:R_Small R1
U 1 1 6010C2BE
P 1450 3050
F 0 "R1" V 1450 3750 50  0000 C CNN
F 1 "R_Small" V 1450 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1450 3050 50  0001 C CNN
F 3 "~" H 1450 3050 50  0001 C CNN
	1    1450 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 6010C900
P 2150 3000
F 0 "R2" V 1954 3000 50  0000 C CNN
F 1 "R_Small" V 2045 3000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 2150 3000 50  0001 C CNN
F 3 "~" H 2150 3000 50  0001 C CNN
	1    2150 3000
	0    1    1    0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 6010D245
P 1250 3050
F 0 "R3" V 1250 3750 50  0000 C CNN
F 1 "R_Small" V 1250 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1250 3050 50  0001 C CNN
F 3 "~" H 1250 3050 50  0001 C CNN
	1    1250 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R4
U 1 1 6010D46A
P 1150 4150
F 0 "R4" V 1350 4800 50  0000 C CNN
F 1 "R_Small" V 1250 4700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1150 4150 50  0001 C CNN
F 3 "~" H 1150 4150 50  0001 C CNN
	1    1150 4150
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R5
U 1 1 6010D502
P 1050 3050
F 0 "R5" V 1050 3750 50  0000 C CNN
F 1 "R_Small" V 1050 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 1050 3050 50  0001 C CNN
F 3 "~" H 1050 3050 50  0001 C CNN
	1    1050 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R6
U 1 1 6010D5B5
P 850 3050
F 0 "R6" V 850 3750 50  0000 C CNN
F 1 "R_Small" V 850 4000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 850 3050 50  0001 C CNN
F 3 "~" H 850 3050 50  0001 C CNN
	1    850  3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 2950 1450 2800
Wire Wire Line
	1250 2950 1250 2800
Wire Wire Line
	1150 4400 1150 4250
Wire Wire Line
	1050 2950 1050 2800
Wire Wire Line
	850  2800 850  2950
Text GLabel 7750 2200 0    50   Input ~ 0
SCL
Text GLabel 7750 2100 0    50   Input ~ 0
SDA
Wire Wire Line
	7750 2100 8050 2100
Connection ~ 8050 2100
Wire Wire Line
	8050 2100 8050 1550
Wire Wire Line
	7750 2200 8200 2200
Connection ~ 8200 2200
Wire Wire Line
	8200 2200 8200 2300
$Comp
L Device:R_Small R8
U 1 1 601596DF
P 8050 1100
F 0 "R8" H 7650 1150 50  0000 L CNN
F 1 "R_Small" H 7600 1050 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 8050 1100 50  0001 C CNN
F 3 "~" H 8050 1100 50  0001 C CNN
	1    8050 1100
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R9
U 1 1 6015A5CD
P 8200 1100
F 0 "R9" H 8300 1200 50  0000 L CNN
F 1 "R_Small" H 8300 1100 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" H 8200 1100 50  0001 C CNN
F 3 "~" H 8200 1100 50  0001 C CNN
	1    8200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 1200 8200 1450
Connection ~ 8200 1450
Wire Wire Line
	8050 1200 8050 1550
Connection ~ 8050 1550
Wire Wire Line
	8700 750  8700 850 
Wire Wire Line
	8700 850  8200 850 
Wire Wire Line
	8050 850  8050 1000
Connection ~ 8700 850 
Wire Wire Line
	8700 850  8700 1350
Wire Wire Line
	8200 1000 8200 850 
Connection ~ 8200 850 
Wire Wire Line
	8200 850  8050 850 
$Comp
L Connector:Conn_01x02_Male J7
U 1 1 6017BB07
P 3200 2650
F 0 "J7" V 3262 2694 50  0000 L CNN
F 1 "Conn_01x02_Male" V 3353 2694 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3200 2650 50  0001 C CNN
F 3 "~" H 3200 2650 50  0001 C CNN
	1    3200 2650
	0    1    1    0   
$EndComp
Wire Wire Line
	3400 3000 3200 3000
Wire Wire Line
	3200 3000 3200 2850
Wire Wire Line
	3100 2850 3100 3000
Wire Wire Line
	2250 3000 3100 3000
Text Notes 3100 3400 0    50   ~ 0
Option to power calculator\nfrom GPIO line. FX502P only.\nRemove batteries.
Text Notes 1500 6800 0    50   ~ 0
Option to power \ncalculator from \nUSB (FX502P only).\nRemove batteries.
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR?
U 1 1 601CED60
P 5700 2750
AR Path="/5FFB81CD/601CED60" Ref="#PWR?"  Part="1" 
AR Path="/601CED60" Ref="#PWR016"  Part="1" 
F 0 "#PWR016" H 5700 2750 30  0001 C CNN
F 1 "GND" H 5700 2680 30  0001 C CNN
F 2 "" H 5700 2750 60  0000 C CNN
F 3 "" H 5700 2750 60  0000 C CNN
	1    5700 2750
	1    0    0    -1  
$EndComp
$Comp
L mirotan-due-cassette-shield-cache:Switch_SW_SPST SW?
U 1 1 6026BE31
P 7600 4650
AR Path="/5F5533DA/6026BE31" Ref="SW?"  Part="1" 
AR Path="/6026BE31" Ref="SW4"  Part="1" 
AR Path="/5FFB81CD/6026BE31" Ref="SW?"  Part="1" 
AR Path="/5FFAC35B/6026BE31" Ref="SW?"  Part="1" 
F 0 "SW4" V 7554 4562 50  0000 R CNN
F 1 "Switch_SW_SPST" V 7645 4562 50  0000 R CNN
F 2 "BP:SMD_BUTTON" H 7600 4650 50  0001 C CNN
F 3 "" H 7600 4650 50  0001 C CNN
	1    7600 4650
	0    -1   1    0   
$EndComp
$Comp
L mirotan-due-cassette-shield-cache:Switch_SW_SPST SW?
U 1 1 60273084
P 7200 4650
AR Path="/5F5533DA/60273084" Ref="SW?"  Part="1" 
AR Path="/60273084" Ref="SW2"  Part="1" 
AR Path="/5FFB81CD/60273084" Ref="SW?"  Part="1" 
AR Path="/5FFAC35B/60273084" Ref="SW?"  Part="1" 
F 0 "SW2" V 7154 4562 50  0000 R CNN
F 1 "Switch_SW_SPST" V 7245 4562 50  0000 R CNN
F 2 "BP:SMD_BUTTON" H 7200 4650 50  0001 C CNN
F 3 "" H 7200 4650 50  0001 C CNN
	1    7200 4650
	0    -1   1    0   
$EndComp
$Comp
L mirotan-due-cassette-shield-cache:Switch_SW_SPST SW?
U 1 1 6027A331
P 7400 4650
AR Path="/5F5533DA/6027A331" Ref="SW?"  Part="1" 
AR Path="/6027A331" Ref="SW3"  Part="1" 
AR Path="/5FFB81CD/6027A331" Ref="SW?"  Part="1" 
AR Path="/5FFAC35B/6027A331" Ref="SW?"  Part="1" 
F 0 "SW3" V 7354 4562 50  0000 R CNN
F 1 "Switch_SW_SPST" V 7445 4562 50  0000 R CNN
F 2 "BP:SMD_BUTTON" H 7400 4650 50  0001 C CNN
F 3 "" H 7400 4650 50  0001 C CNN
	1    7400 4650
	0    -1   1    0   
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR0101
U 1 1 602953AC
P 7200 5000
F 0 "#PWR0101" H 7200 5000 30  0001 C CNN
F 1 "GND" H 7200 4930 30  0001 C CNN
F 2 "" H 7200 5000 60  0000 C CNN
F 3 "" H 7200 5000 60  0000 C CNN
	1    7200 5000
	1    0    0    -1  
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR0102
U 1 1 6029CA74
P 7400 5000
F 0 "#PWR0102" H 7400 5000 30  0001 C CNN
F 1 "GND" H 7400 4930 30  0001 C CNN
F 2 "" H 7400 5000 60  0000 C CNN
F 3 "" H 7400 5000 60  0000 C CNN
	1    7400 5000
	1    0    0    -1  
$EndComp
$Comp
L fx502p-sd-pcb-1-rescue:GND-Microtan_65_CPU-cache #PWR0103
U 1 1 602A3D07
P 7600 5000
F 0 "#PWR0103" H 7600 5000 30  0001 C CNN
F 1 "GND" H 7600 4930 30  0001 C CNN
F 2 "" H 7600 5000 60  0000 C CNN
F 3 "" H 7600 5000 60  0000 C CNN
	1    7600 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	7200 4850 7200 5000
Wire Wire Line
	7400 5000 7400 4850
Wire Wire Line
	7600 4850 7600 5000
Wire Wire Line
	5850 3700 7200 3700
Wire Wire Line
	5850 3800 7400 3800
Wire Wire Line
	5850 3900 7600 3900
Wire Wire Line
	7200 4450 7200 3700
Wire Wire Line
	7400 4450 7400 3800
Wire Wire Line
	7600 4450 7600 3900
$Comp
L fx502p:Expansion P1
U 1 1 603507C7
P 1250 3700
F 0 "P1" H 1578 4067 50  0000 L CNN
F 1 "Expansion" H 1578 3976 50  0000 L CNN
F 2 "ajm_kicad:expansion_fx502p" H 1250 3700 50  0001 C CNN
F 3 "" H 1250 3700 50  0001 C CNN
	1    1250 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1150 4050 1150 3800
Wire Wire Line
	950  3800 950  4300
Wire Wire Line
	850  3150 850  3550
Wire Wire Line
	1450 3150 1450 3550
Wire Wire Line
	1050 3550 1050 3150
Wire Wire Line
	1250 3150 1250 3550
Wire Wire Line
	2050 3000 2050 4250
Wire Wire Line
	2050 4250 1350 4250
Wire Wire Line
	1350 4250 1350 3800
$EndSCHEMATC
