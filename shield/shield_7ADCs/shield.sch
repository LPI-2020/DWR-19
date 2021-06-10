EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "mar. 31 mars 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_02x08_Odd_Even CN8
U 1 1 60C5E63A
P 3050 3750
F 0 "CN8" H 3050 4700 50  0000 C CNN
F 1 "Digital" V 3050 3750 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x08_P2.54mm_Vertical" H 3050 2700 50  0001 C CNN
F 3 "" H 3050 2700 50  0000 C CNN
	1    3050 3750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x15_Odd_Even CN9
U 1 1 60C69719
P 3050 5000
F 0 "CN9" H 3050 5950 50  0000 C CNN
F 1 "Digital" V 3050 5000 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x15_P2.54mm_Vertical" H 3050 3950 50  0001 C CNN
F 3 "" H 3050 3950 50  0000 C CNN
	1    3050 5000
	1    0    0    -1  
$EndComp
Text Label 3800 3450 2    60   ~ 0
NC
Text Label 3800 3550 2    60   ~ 0
IOREF
Text Label 3800 3650 2    60   ~ 0
RSET
Text Label 3800 3750 2    60   ~ 0
3,3V
Text Label 3800 3850 2    60   ~ 0
5V
Text Label 3800 3950 2    60   ~ 0
GND
Text Label 3800 4050 2    60   ~ 0
GND
Text Label 3800 4150 2    60   ~ 0
VIN
Wire Wire Line
	3350 3450 3800 3450
Wire Wire Line
	3800 3550 3350 3550
Wire Wire Line
	3350 3650 3800 3650
Wire Wire Line
	3800 3750 3350 3750
Wire Wire Line
	3350 3850 3800 3850
Wire Wire Line
	3800 3950 3350 3950
Wire Wire Line
	3350 4050 3800 4050
Wire Wire Line
	3800 4150 3350 4150
Wire Wire Line
	5850 4000 5400 4000
Wire Wire Line
	5400 3900 5850 3900
Text Label 5850 4000 2    60   ~ 0
PB4
Text Label 5850 3900 2    60   ~ 0
PA4
Wire Wire Line
	5850 3800 5400 3800
Wire Wire Line
	5400 3700 5850 3700
Wire Wire Line
	5850 3600 5400 3600
Wire Wire Line
	5400 3500 5850 3500
Wire Wire Line
	5850 3400 5400 3400
Wire Wire Line
	5400 3300 5850 3300
Text Label 5850 3800 2    60   ~ 0
PB3
Text Label 5850 3700 2    60   ~ 0
PB5
Text Label 5850 3600 2    60   ~ 0
PC7
Text Label 5850 3500 2    60   ~ 0
PA15
Text Label 5850 3400 2    60   ~ 0
PB12
Text Label 5850 3300 2    60   ~ 0
PB13
$Comp
L Connector_Generic:Conn_02x17_Odd_Even CN10
U 1 1 60C7F25B
P 5100 4950
F 0 "CN10" H 5100 5900 50  0000 C CNN
F 1 "Digital" V 5100 4950 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x17_P2.54mm_Vertical" H 5100 3900 50  0001 C CNN
F 3 "" H 5100 3900 50  0000 C CNN
	1    5100 4950
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Odd_Even CN7
U 1 1 60C712AD
P 5100 3500
F 0 "CN7" H 5100 4450 50  0000 C CNN
F 1 "Digital" V 5100 3500 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 5100 2450 50  0001 C CNN
F 3 "" H 5100 2450 50  0000 C CNN
	1    5100 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 5050 5400 5050
Wire Wire Line
	5400 4950 5850 4950
Text Label 5850 5050 2    60   ~ 0
PD13
Text Label 5850 4950 2    60   ~ 0
GND
Wire Wire Line
	5850 4850 5400 4850
Wire Wire Line
	5400 4750 5850 4750
Wire Wire Line
	5850 4650 5400 4650
Wire Wire Line
	5400 4550 5850 4550
Wire Wire Line
	5850 4450 5400 4450
Wire Wire Line
	5400 4350 5850 4350
Wire Wire Line
	5850 4250 5400 4250
Wire Wire Line
	5400 4150 5850 4150
Text Label 5850 4850 2    60   ~ 0
PB2
Text Label 5850 4750 2    60   ~ 0
PB6
Text Label 5850 4650 2    60   ~ 0
PF4
Text Label 5850 4550 2    60   ~ 0
PC2
Text Label 5850 4450 2    60   ~ 0
PB1
Text Label 5850 4350 2    60   ~ 0
GND
Text Label 5850 4250 2    60   ~ 0
AGND
Text Label 5850 4150 2    60   ~ 0
AVDD
Wire Wire Line
	5400 5550 5850 5550
Wire Wire Line
	5850 5450 5400 5450
Wire Wire Line
	5400 5350 5850 5350
Wire Wire Line
	5850 5250 5400 5250
Wire Wire Line
	5400 5150 5850 5150
Text Label 5850 5550 2    60   ~ 0
PA0
Text Label 5850 5450 2    60   ~ 0
GND
Text Label 5850 5350 2    60   ~ 0
PE2
Text Label 5850 5250 2    60   ~ 0
PD11
Text Label 5850 5150 2    60   ~ 0
PD12
Text Label 5850 3100 2    60   ~ 0
PC6
Text Label 5850 3200 2    60   ~ 0
PB15
Wire Wire Line
	5400 3100 5850 3100
Wire Wire Line
	5850 3200 5400 3200
Text Label 5850 5650 2    60   ~ 0
PB0
Text Label 5850 5750 2    60   ~ 0
PE0
Wire Wire Line
	5400 5650 5850 5650
Wire Wire Line
	5850 5750 5400 5750
Text Label 2550 3450 2    50   ~ 0
PC8
Wire Wire Line
	2850 3450 2550 3450
Text Label 2550 3550 2    50   ~ 0
PC9
Wire Wire Line
	2850 3550 2550 3550
Text Label 2550 3650 2    50   ~ 0
PC10
Wire Wire Line
	2850 3650 2550 3650
Text Label 2550 3750 2    50   ~ 0
PC11
Wire Wire Line
	2850 3750 2550 3750
Text Label 2550 3850 2    50   ~ 0
PC12
Wire Wire Line
	2850 3850 2550 3850
Text Label 2550 3950 2    50   ~ 0
PD2
Wire Wire Line
	2850 3950 2550 3950
Text Label 2550 4050 2    50   ~ 0
PG2
Wire Wire Line
	2850 4050 2550 4050
Text Label 2550 4150 2    50   ~ 0
PG3
Wire Wire Line
	2850 4150 2550 4150
Text Label 4600 4150 2    50   ~ 0
PF13
Wire Wire Line
	4900 4150 4600 4150
Text Label 4600 4250 2    50   ~ 0
PE9
Wire Wire Line
	4900 4250 4600 4250
Text Label 4600 4350 2    50   ~ 0
PE11
Wire Wire Line
	4900 4350 4600 4350
Text Label 4600 4450 2    50   ~ 0
PF14
Wire Wire Line
	4900 4450 4600 4450
Text Label 4600 4550 2    50   ~ 0
PE13
Wire Wire Line
	4900 4550 4600 4550
Text Label 4600 4650 2    50   ~ 0
PF15
Wire Wire Line
	4900 4650 4600 4650
Text Label 4600 4750 2    50   ~ 0
PG14
Wire Wire Line
	4900 4750 4600 4750
Text Label 4600 4850 2    50   ~ 0
PG9
Wire Wire Line
	4900 4850 4600 4850
Text Label 4600 4950 2    50   ~ 0
PE8
Wire Wire Line
	4900 4950 4600 4950
Text Label 4600 5050 2    50   ~ 0
PE7
Wire Wire Line
	4900 5050 4600 5050
Text Label 4600 5150 2    50   ~ 0
GND
Wire Wire Line
	4900 5150 4600 5150
Text Label 4600 5250 2    50   ~ 0
PE10
Wire Wire Line
	4900 5250 4600 5250
Text Label 4600 5350 2    50   ~ 0
PE12
Wire Wire Line
	4900 5350 4600 5350
Text Label 4600 5450 2    50   ~ 0
PE14
Wire Wire Line
	4900 5450 4600 5450
Text Label 4600 5550 2    50   ~ 0
PE15
Wire Wire Line
	4900 5550 4600 5550
Text Label 4600 5650 2    50   ~ 0
PB10
Wire Wire Line
	4900 5650 4600 5650
Text Label 4600 5750 2    50   ~ 0
PB11
Wire Wire Line
	4900 5750 4600 5750
Text Label 4600 3100 2    50   ~ 0
PB8
Wire Wire Line
	4900 3100 4600 3100
Text Label 4600 3200 2    50   ~ 0
PB9
Wire Wire Line
	4900 3200 4600 3200
Text Label 4600 3300 2    50   ~ 0
AVDD
Wire Wire Line
	4900 3300 4600 3300
Text Label 4600 3400 2    50   ~ 0
GND
Wire Wire Line
	4900 3400 4600 3400
Text Label 4600 3500 2    50   ~ 0
PA5
Wire Wire Line
	4900 3500 4600 3500
Text Label 4600 3600 2    50   ~ 0
PA6
Wire Wire Line
	4900 3600 4600 3600
Text Label 4600 3700 2    50   ~ 0
PA7
Wire Wire Line
	4900 3700 4600 3700
Wire Wire Line
	4900 3900 4600 3900
Wire Wire Line
	4900 3800 4600 3800
Text Label 4600 3800 2    50   ~ 0
PD14
Text Label 4600 3900 2    50   ~ 0
PD15
Wire Wire Line
	4900 4000 4600 4000
Text Label 4600 4000 2    50   ~ 0
PF12
Text Notes 2825 825  0    60   ~ 0
Shield for STM31F767ZI
Wire Notes Line
	4300 900  4300 725 
Wire Notes Line
	2800 900  4300 900 
Text Label 4850 2150 2    60   ~ 0
+5V
Wire Wire Line
	4400 2150 4850 2150
Text Label 3600 2150 2    50   ~ 0
GND
Wire Wire Line
	3900 2150 3600 2150
$Comp
L Connector_Generic:Conn_02x03_Odd_Even Fonte5V1
U 1 1 60C07473
P 4100 2250
F 0 "Fonte5V1" H 4100 3200 50  0000 C CNN
F 1 "Digital" V 4100 2250 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x03_P2.54mm_Vertical" H 4100 1200 50  0001 C CNN
F 3 "" H 4100 1200 50  0000 C CNN
	1    4100 2250
	1    0    0    -1  
$EndComp
Text Label 4850 2350 2    60   ~ 0
+5V
Wire Wire Line
	4850 2350 4400 2350
Text Label 3600 2350 2    50   ~ 0
GND
Wire Wire Line
	3900 2350 3600 2350
Text Label 4850 2600 2    60   ~ 0
+3.3V
Wire Wire Line
	4400 2600 4850 2600
Text Label 3600 2600 2    50   ~ 0
GND
Wire Wire Line
	3900 2600 3600 2600
$Comp
L Connector_Generic:Conn_02x03_Odd_Even Fonte3.3V1
U 1 1 60C46FD2
P 4100 2700
F 0 "Fonte3.3V1" H 4100 3650 50  0000 C CNN
F 1 "Digital" V 4100 2700 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x03_P2.54mm_Vertical" H 4100 1650 50  0001 C CNN
F 3 "" H 4100 1650 50  0000 C CNN
	1    4100 2700
	1    0    0    -1  
$EndComp
Text Label 4850 2800 2    60   ~ 0
+3.3V
Wire Wire Line
	4850 2800 4400 2800
Text Label 3600 2800 2    50   ~ 0
GND
Wire Wire Line
	3900 2800 3600 2800
Text Label 4100 6700 1    60   ~ 0
GND
Wire Wire Line
	4100 6250 4100 6700
$Comp
L Connector_Generic:Conn_01x06 bluetooth1
U 1 1 60C67AF5
P 4000 6050
F 0 "bluetooth1" H 4000 7000 50  0000 C CNN
F 1 "Digital" V 4000 6050 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 4000 5000 50  0001 C CNN
F 3 "" H 4000 5000 50  0000 C CNN
	1    4000 6050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3900 6700 3900 6250
Text Label 4200 6700 1    60   ~ 0
+5V
Wire Wire Line
	4200 6700 4200 6250
Wire Wire Line
	4000 6250 4000 6700
$Comp
L Connector:Screw_Terminal_01x09 SENSOR_LINHA1
U 1 1 60C8A841
P 1450 3100
F 0 "SENSOR_LINHA1" H 1530 3092 50  0000 L CNN
F 1 "Screw_Terminal_01x09" H 1530 3001 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-9_1x09_P5.00mm_Horizontal" H 1450 3100 50  0001 C CNN
F 3 "~" H 1450 3100 50  0001 C CNN
	1    1450 3100
	1    0    0    -1  
$EndComp
Text Label 800  3800 0    60   ~ 0
GND
Text Label 800  3700 0    60   ~ 0
+5V
Text Label 800  3900 0    60   ~ 0
PA3
Wire Wire Line
	1250 3800 800  3800
Wire Wire Line
	800  3700 1250 3700
Wire Wire Line
	1250 3900 800  3900
$Comp
L Connector:Screw_Terminal_01x03 SENSOR_OBSTACULOS1
U 1 1 60C99735
P 1450 3800
F 0 "SENSOR_OBSTACULOS1" H 1530 3792 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 1530 3701 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-3_1x03_P5.00mm_Horizontal" H 1450 3800 50  0001 C CNN
F 3 "~" H 1450 3800 50  0001 C CNN
	1    1450 3800
	1    0    0    -1  
$EndComp
Text Label 800  2700 0    60   ~ 0
GND
Text Label 800  2800 0    60   ~ 0
+3.3V
Text Label 800  2900 0    60   ~ 0
+3.3V
Text Label 800  3000 0    60   ~ 0
PC0
Text Label 800  3100 0    60   ~ 0
PC3
Text Label 800  3200 0    60   ~ 0
PF3
Text Label 800  3300 0    60   ~ 0
PF5
Wire Wire Line
	800  2800 1250 2800
Wire Wire Line
	800  3000 1250 3000
Wire Wire Line
	1250 3100 800  3100
Wire Wire Line
	800  3200 1250 3200
Wire Wire Line
	1250 3300 800  3300
Text Label 800  3400 0    60   ~ 0
PF10
Text Label 800  3500 0    60   ~ 0
PA7
Wire Wire Line
	800  3400 1250 3400
Wire Wire Line
	1250 3500 800  3500
$Comp
L Connector:Screw_Terminal_01x07 DRIVER_MOTOR1
U 1 1 60CE421D
P 6800 5300
F 0 "DRIVER_MOTOR1" H 6880 5292 50  0000 L CNN
F 1 "Screw_Terminal_01x07" H 6880 5201 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-7_1x07_P5.00mm_Horizontal" H 6800 5300 50  0001 C CNN
F 3 "~" H 6800 5300 50  0001 C CNN
	1    6800 5300
	-1   0    0    -1  
$EndComp
Text Label 4000 6700 1    60   ~ 0
PB15
Text Label 3900 6700 1    60   ~ 0
PB6
Text Notes 4250 6800 0    50   ~ 0
EN
Text Notes 4150 6900 0    50   ~ 0
VCC
Text Notes 4050 6800 0    50   ~ 0
GND
Text Notes 3950 6900 0    50   ~ 0
TXD
Text Notes 3850 6800 0    50   ~ 0
RXD
Text Notes 3650 6900 0    50   ~ 0
STATE
Text Notes 500  3900 0    50   ~ 0
S_OBST
Wire Wire Line
	2850 5700 2550 5700
Text Label 2550 5700 2    50   ~ 0
PG1
Wire Wire Line
	2850 5600 2550 5600
Text Label 2550 5600 2    50   ~ 0
PF9
Wire Wire Line
	2850 5500 2550 5500
Text Label 2550 5500 2    50   ~ 0
PF7
Wire Wire Line
	2850 5400 2550 5400
Text Label 2550 5400 2    50   ~ 0
PF8
Wire Wire Line
	2850 5300 2550 5300
Text Label 2550 5300 2    50   ~ 0
PE3
Wire Wire Line
	2850 5200 2550 5200
Text Label 2550 5200 2    50   ~ 0
PE6
Wire Wire Line
	2850 5100 2550 5100
Text Label 2550 5100 2    50   ~ 0
PE5
Wire Wire Line
	2850 5000 2550 5000
Text Label 2550 5000 2    50   ~ 0
PE4
Wire Wire Line
	2850 4900 2550 4900
Text Label 2550 4900 2    50   ~ 0
PE2
Wire Wire Line
	2850 4800 2550 4800
Text Label 2550 4800 2    50   ~ 0
GND
Wire Wire Line
	2850 4700 2550 4700
Text Label 2550 4700 2    50   ~ 0
PD3
Wire Wire Line
	2850 4600 2550 4600
Text Label 2550 4600 2    50   ~ 0
PD4
Wire Wire Line
	2850 4500 2550 4500
Text Label 2550 4500 2    50   ~ 0
PD5
Wire Wire Line
	2850 4400 2550 4400
Text Label 2550 4400 2    50   ~ 0
PD6
Wire Wire Line
	2850 4300 2550 4300
Text Label 2550 4300 2    50   ~ 0
PD7
Text Label 3800 4700 2    60   ~ 0
PF5
Text Label 3800 4800 2    60   ~ 0
PF10
Text Label 3800 4900 2    60   ~ 0
NC
Text Label 3800 5000 2    60   ~ 0
PA7
Text Label 3800 5100 2    60   ~ 0
PF2
Wire Wire Line
	3800 4700 3350 4700
Wire Wire Line
	3350 4800 3800 4800
Wire Wire Line
	3800 4900 3350 4900
Wire Wire Line
	3350 5000 3800 5000
Wire Wire Line
	3800 5100 3350 5100
Text Label 3800 5200 2    60   ~ 0
PF1
Text Label 3800 5300 2    60   ~ 0
PF0
Text Label 3800 5400 2    60   ~ 0
GND
Wire Wire Line
	3800 5200 3350 5200
Wire Wire Line
	3350 5300 3800 5300
Wire Wire Line
	3800 5400 3350 5400
Text Label 3800 4300 2    60   ~ 0
PA3
Text Label 3800 4400 2    60   ~ 0
PC0
Text Label 3800 4500 2    60   ~ 0
PC3
Text Label 3800 4600 2    60   ~ 0
PF3
Wire Wire Line
	3800 4300 3350 4300
Wire Wire Line
	3350 4400 3800 4400
Wire Wire Line
	3800 4500 3350 4500
Wire Wire Line
	3350 4600 3800 4600
Text Label 3800 5500 2    60   ~ 0
PD0
Text Label 3800 5600 2    60   ~ 0
PD1
Wire Wire Line
	3350 5500 3800 5500
Wire Wire Line
	3800 5600 3350 5600
Text Label 3800 5700 2    60   ~ 0
PG0
Wire Wire Line
	3800 5700 3350 5700
Text Notes 7750 5600 2    50   ~ 0
PWM_R
Text Notes 7750 5500 2    50   ~ 0
EN1_R
Text Notes 7750 5400 2    50   ~ 0
EN2_R
Text Notes 7750 5300 2    50   ~ 0
EN1_L
Text Notes 7750 5100 2    50   ~ 0
PWM_L
Text Notes 7750 5200 2    50   ~ 0
EN2_L
Wire Wire Line
	7450 5100 7000 5100
Text Label 7450 5100 2    60   ~ 0
PD15
Wire Wire Line
	7000 5200 7450 5200
Wire Wire Line
	7450 5300 7000 5300
Wire Wire Line
	7000 5400 7450 5400
Wire Wire Line
	7450 5500 7000 5500
Wire Wire Line
	7000 5600 7450 5600
Text Label 7450 5200 2    60   ~ 0
PD14
Text Label 7450 5300 2    60   ~ 0
PA6
Text Label 7450 5400 2    60   ~ 0
PA5
Text Label 7450 5500 2    60   ~ 0
PB9
Text Label 7450 5600 2    60   ~ 0
PB8
$Comp
L Connector:Screw_Terminal_01x08 RFID2
U 1 1 60C1ECB2
P 6800 3700
F 0 "RFID2" H 6880 3692 50  0000 L CNN
F 1 "Screw_Terminal_01x06" H 6880 3601 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-8_1x08_P5.00mm_Horizontal" H 6800 3700 50  0001 C CNN
F 3 "~" H 6800 3700 50  0001 C CNN
	1    6800 3700
	-1   0    0    -1  
$EndComp
Text Notes 7750 3500 2    50   ~ 0
MOSI
Text Notes 7750 3800 2    50   ~ 0
IRQ
Text Notes 7750 4000 2    50   ~ 0
GND
Text Notes 7750 4100 2    50   ~ 0
+3.3V
Text Notes 7750 3900 2    50   ~ 0
RSET
Wire Wire Line
	7450 4100 7000 4100
Text Label 7450 4100 2    60   ~ 0
+3.3V
Wire Wire Line
	7000 3900 7450 3900
Wire Wire Line
	7450 4000 7000 4000
Text Label 7450 3900 2    60   ~ 0
PC9
Text Label 7450 4000 2    60   ~ 0
GND
Text Notes 7750 3400 2    50   ~ 0
SDA
Text Notes 7750 3700 2    50   ~ 0
SCK
Wire Wire Line
	7000 3400 7450 3400
Text Label 7450 3400 2    60   ~ 0
PD2
Text Notes 7750 3600 2    50   ~ 0
MISO
Wire Wire Line
	7450 3700 7000 3700
Text Label 7450 3700 2    60   ~ 0
PC10
Wire Wire Line
	7450 3600 7000 3600
Wire Wire Line
	7000 3500 7450 3500
Text Label 7450 3600 2    60   ~ 0
PC11
Text Label 7450 3500 2    60   ~ 0
PC12
Wire Wire Line
	1250 2700 800  2700
Wire Wire Line
	1250 2900 800  2900
Text Notes 500  2900 0    50   ~ 0
LED_ON
Text Notes 600  3500 0    50   ~ 0
S8
Text Notes 600  3400 0    50   ~ 0
S6
Text Notes 600  3300 0    50   ~ 0
S5
Text Notes 600  3200 0    50   ~ 0
S4
Text Notes 600  3100 0    50   ~ 0
S3
Text Notes 600  3000 0    50   ~ 0
S1
Text Notes 600  2800 0    50   ~ 0
VCC
$Comp
L Device:C C_SLINHA1
U 1 1 60DF57C8
P 1700 1550
F 0 "C_SLINHA1" H 1815 1596 50  0000 L CNN
F 1 "C" H 1815 1505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 1738 1400 50  0001 C CNN
F 3 "~" H 1700 1550 50  0001 C CNN
	1    1700 1550
	1    0    0    -1  
$EndComp
Text GLabel 1700 1700 3    50   Input ~ 0
GND
Text GLabel 1700 1400 1    50   Input ~ 0
+3.3V
Text Notes 7750 5000 2    50   ~ 0
GND
Wire Wire Line
	7450 5000 7000 5000
Text Label 7450 5000 2    60   ~ 0
GND
Text GLabel 2300 1400 1    50   Input ~ 0
+5V
Text GLabel 2300 1700 3    50   Input ~ 0
GND
$Comp
L Device:C C_SOBST1
U 1 1 60E3B31B
P 2300 1550
F 0 "C_SOBST1" H 2415 1596 50  0000 L CNN
F 1 "C" H 2415 1505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2338 1400 50  0001 C CNN
F 3 "~" H 2300 1550 50  0001 C CNN
	1    2300 1550
	1    0    0    -1  
$EndComp
Text GLabel 2850 1400 1    50   Input ~ 0
+5V
Text GLabel 2850 1700 3    50   Input ~ 0
GND
$Comp
L Device:C C_BLUE1
U 1 1 60E502E6
P 2850 1550
F 0 "C_BLUE1" H 2965 1596 50  0000 L CNN
F 1 "C" H 2965 1505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 2888 1400 50  0001 C CNN
F 3 "~" H 2850 1550 50  0001 C CNN
	1    2850 1550
	1    0    0    -1  
$EndComp
$Comp
L Device:C C_RFID1
U 1 1 60E5B397
P 1100 1550
F 0 "C_RFID1" H 1215 1596 50  0000 L CNN
F 1 "C" H 1215 1505 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D4.3mm_W1.9mm_P5.00mm" H 1138 1400 50  0001 C CNN
F 3 "~" H 1100 1550 50  0001 C CNN
	1    1100 1550
	1    0    0    -1  
$EndComp
Text GLabel 1100 1700 3    50   Input ~ 0
GND
Text GLabel 1100 1400 1    50   Input ~ 0
+3.3V
$Comp
L Connector:Screw_Terminal_01x02 BOTAO1
U 1 1 60C27E5A
P 6800 2600
F 0 "BOTAO1" H 6880 2592 50  0000 L CNN
F 1 "Screw_Terminal_01x06" H 6880 2501 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-2_1x02_P5.00mm_Horizontal" H 6800 2600 50  0001 C CNN
F 3 "~" H 6800 2600 50  0001 C CNN
	1    6800 2600
	-1   0    0    -1  
$EndComp
Wire Wire Line
	7450 2600 7000 2600
Text Label 7450 2600 2    60   ~ 0
GND
Wire Wire Line
	7450 2700 7000 2700
Text Label 7450 2700 2    60   ~ 0
PC8
$Comp
L Connector:Screw_Terminal_01x07 CON_LIVRE1
U 1 1 60C72E52
P 1600 6350
F 0 "CON_LIVRE1" H 1680 6342 50  0000 L CNN
F 1 "Screw_Terminal_01x07" H 1680 6251 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-7_1x07_P5.00mm_Horizontal" H 1600 6350 50  0001 C CNN
F 3 "~" H 1600 6350 50  0001 C CNN
	1    1600 6350
	1    0    0    -1  
$EndComp
Text Label 950  6050 0    60   ~ 0
PF2
Text Label 950  6150 0    60   ~ 0
PF1
Text Label 950  6250 0    60   ~ 0
PF0
Text Label 950  6350 0    60   ~ 0
GND
Text Label 950  6450 0    60   ~ 0
PD0
Text Label 950  6550 0    60   ~ 0
PD1
Wire Wire Line
	950  6050 1400 6050
Wire Wire Line
	950  6250 1400 6250
Wire Wire Line
	1400 6350 950  6350
Wire Wire Line
	950  6450 1400 6450
Wire Wire Line
	1400 6550 950  6550
Text Label 950  6650 0    60   ~ 0
PG0
Wire Wire Line
	950  6650 1400 6650
Wire Wire Line
	1400 6150 950  6150
Text Notes 750  6050 0    50   ~ 0
PF2
Text Notes 750  6250 0    50   ~ 0
PF0
Text Notes 750  6350 0    50   ~ 0
GND
Text Notes 750  6450 0    50   ~ 0
PD0
Text Notes 750  6550 0    50   ~ 0
PD1
Text Notes 750  6650 0    50   ~ 0
PG0
Text Notes 750  6150 0    50   ~ 0
PF1
$Comp
L Connector:Screw_Terminal_01x07 CON_LIVRE2
U 1 1 60CB4043
P 2600 6900
F 0 "CON_LIVRE2" H 2680 6892 50  0000 L CNN
F 1 "Screw_Terminal_01x07" H 2680 6801 50  0000 L CNN
F 2 "TerminalBlock_Phoenix:TerminalBlock_Phoenix_MKDS-1,5-7_1x07_P5.00mm_Horizontal" H 2600 6900 50  0001 C CNN
F 3 "~" H 2600 6900 50  0001 C CNN
	1    2600 6900
	0    -1   -1   0   
$EndComp
Text Label 2900 7550 1    60   ~ 0
PE5
Text Label 2800 7550 1    60   ~ 0
PE6
Text Label 2700 7550 1    60   ~ 0
PE3
Text Label 2600 7550 1    60   ~ 0
PF8
Text Label 2500 7550 1    60   ~ 0
PF7
Text Label 2400 7550 1    60   ~ 0
PF9
Wire Wire Line
	2900 7550 2900 7100
Wire Wire Line
	2700 7550 2700 7100
Wire Wire Line
	2600 7100 2600 7550
Wire Wire Line
	2500 7550 2500 7100
Wire Wire Line
	2400 7100 2400 7550
Text Label 2300 7550 1    60   ~ 0
PG1
Wire Wire Line
	2300 7550 2300 7100
Wire Wire Line
	2800 7100 2800 7550
Text Notes 2900 7750 1    50   ~ 0
PE5
Text Notes 2700 7750 1    50   ~ 0
PE3
Text Notes 2600 7750 1    50   ~ 0
PF8
Text Notes 2500 7750 1    50   ~ 0
PF7
Text Notes 2400 7750 1    50   ~ 0
PF9
Text Notes 2300 7750 1    50   ~ 0
PG1
Text Notes 2800 7750 1    50   ~ 0
PE6
$EndSCHEMATC
