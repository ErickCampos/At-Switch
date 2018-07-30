EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:inversor7404
LIBS:piezo
LIBS:blow-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
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
L Inversor7404 I1
U 1 1 5A95AA29
P 7000 2900
F 0 "I1" H 7650 3750 60  0000 C CNN
F 1 "Inversor7404" H 7650 3850 60  0000 C CNN
F 2 "Housings_DIP:DIP-14_W7.62mm_LongPads" H 7650 3750 60  0001 C CNN
F 3 "" H 7650 3750 60  0000 C CNN
	1    7000 2900
	1    0    0    -1  
$EndComp
$Comp
L Piezo P1
U 1 1 5A95AA75
P 6400 6750
F 0 "P1" H 3900 10750 60  0000 C CNN
F 1 "Piezo" H 3900 10650 60  0000 C CNN
F 2 "Piezo:piezo" H 3900 10800 60  0001 C CNN
F 3 "" H 3900 10800 60  0000 C CNN
	1    6400 6750
	1    0    0    -1  
$EndComp
$Comp
L LM358 U1
U 1 1 5A95AB94
P 5650 2300
F 0 "U1" H 5600 2500 50  0000 L CNN
F 1 "LM358" H 5600 2050 50  0000 L CNN
F 2 "Housings_DIP:DIP-8_W7.62mm_LongPads" H 5650 2300 50  0001 C CNN
F 3 "" H 5650 2300 50  0000 C CNN
	1    5650 2300
	1    0    0    -1  
$EndComp
$Comp
L BARREL_JACK CON1
U 1 1 5A95ACAC
P 1900 3400
F 0 "CON1" H 1900 3650 50  0000 C CNN
F 1 "BARREL_JACK" H 1900 3200 50  0000 C CNN
F 2 "Connect:BARREL_JACK" H 1900 3400 50  0001 C CNN
F 3 "" H 1900 3400 50  0000 C CNN
	1    1900 3400
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 5A95AD23
P 4400 3300
F 0 "R1" V 4480 3300 50  0000 C CNN
F 1 "R" V 4400 3300 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 4330 3300 50  0001 C CNN
F 3 "" H 4400 3300 50  0000 C CNN
	1    4400 3300
	1    0    0    -1  
$EndComp
$Comp
L LED D1
U 1 1 5A95AD84
P 6400 2300
F 0 "D1" H 6400 2400 50  0000 C CNN
F 1 "LED" H 6400 2200 50  0000 C CNN
F 2 "LEDs:LED-5MM" H 6400 2300 50  0001 C CNN
F 3 "" H 6400 2300 50  0000 C CNN
	1    6400 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2200 3400 2300 3400
Wire Wire Line
	2300 3400 2300 3500
Wire Wire Line
	2300 3500 2200 3500
Wire Wire Line
	2300 3450 2550 3450
Wire Wire Line
	2550 3450 2550 4200
Wire Wire Line
	2550 4200 7200 4200
Wire Wire Line
	3900 3900 3900 4200
Connection ~ 2300 3450
Wire Wire Line
	3900 2200 3900 2800
Wire Wire Line
	3900 2200 5350 2200
$Comp
L POT RV1
U 1 1 5A95B038
P 4700 2400
F 0 "RV1" H 4700 2320 50  0000 C CNN
F 1 "POT" H 4700 2400 50  0000 C CNN
F 2 "Potentiometers:Potentiometer_Alps-RK16-single" H 4700 2400 50  0001 C CNN
F 3 "" H 4700 2400 50  0000 C CNN
	1    4700 2400
	0    1    1    0   
$EndComp
Wire Wire Line
	4850 2400 5350 2400
Wire Wire Line
	4700 2250 4700 1700
Wire Wire Line
	2550 1700 5550 1700
Wire Wire Line
	5550 1700 5550 2000
Wire Wire Line
	4700 4200 4700 2550
Connection ~ 3900 4200
Wire Wire Line
	4400 3450 4400 4000
Wire Wire Line
	4400 4000 3900 4000
Connection ~ 3900 4000
Wire Wire Line
	3900 2450 4400 2450
Wire Wire Line
	4400 2450 4400 3150
Connection ~ 3900 2450
Wire Wire Line
	5550 4200 5550 2600
Connection ~ 4700 4200
Wire Wire Line
	5950 2300 6200 2300
$Comp
L R R2
U 1 1 5A95B640
P 6900 2950
F 0 "R2" V 6980 2950 50  0000 C CNN
F 1 "R" V 6900 2950 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM10mm" V 6830 2950 50  0001 C CNN
F 3 "" H 6900 2950 50  0000 C CNN
	1    6900 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2300 7200 2300
Wire Wire Line
	6900 1800 6900 2800
Wire Wire Line
	6900 4200 6900 3100
Connection ~ 5550 4200
Connection ~ 6900 2300
Wire Wire Line
	6900 2150 7200 2150
Wire Wire Line
	7200 4200 7200 2450
Connection ~ 6900 4200
Wire Wire Line
	2200 3300 2550 3300
Wire Wire Line
	2550 3300 2550 1700
Connection ~ 4700 1700
$Comp
L CONN_01X03 P2
U 1 1 5A9FE019
P 8850 2300
F 0 "P2" H 8850 2500 50  0000 C CNN
F 1 "CONN_01X03" V 8950 2300 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 8850 2300 50  0001 C CNN
F 3 "" H 8850 2300 50  0000 C CNN
	1    8850 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	8100 2300 8650 2300
Wire Wire Line
	8650 2400 8100 2400
Wire Wire Line
	8100 2400 8100 2900
Wire Wire Line
	8100 2900 7200 2900
Connection ~ 7200 2900
Wire Wire Line
	6900 1800 8200 1800
Wire Wire Line
	8200 1800 8200 2200
Wire Wire Line
	8200 2200 8650 2200
Connection ~ 6900 2150
$EndSCHEMATC
