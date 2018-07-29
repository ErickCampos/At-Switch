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
LIBS:special
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
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "18 may 2017"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED D1
U 1 1 591DA180
P 3750 1750
F 0 "D1" H 3750 1850 50  0000 C CNN
F 1 "LED" H 3750 1650 50  0000 C CNN
F 2 "~" H 3750 1750 60  0000 C CNN
F 3 "~" H 3750 1750 60  0000 C CNN
	1    3750 1750
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 591DA192
P 3050 2300
F 0 "R1" V 3130 2300 40  0000 C CNN
F 1 "R" V 3057 2301 40  0000 C CNN
F 2 "~" V 2980 2300 30  0000 C CNN
F 3 "~" H 3050 2300 30  0000 C CNN
	1    3050 2300
	0    -1   -1   0   
$EndComp
$Comp
L BC548 Q1
U 1 1 591DA1EF
P 3650 2300
F 0 "Q1" H 3650 2151 40  0000 R CNN
F 1 "BC548" H 3650 2450 40  0000 R CNN
F 2 "TO92" H 3550 2402 29  0000 C CNN
F 3 "" H 3650 2300 60  0000 C CNN
	1    3650 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2100 3750 1950
Wire Wire Line
	3300 2300 3450 2300
$Comp
L R R2
U 1 1 591DA227
P 3750 2900
F 0 "R2" V 3830 2900 40  0000 C CNN
F 1 "R" V 3757 2901 40  0000 C CNN
F 2 "~" V 3680 2900 30  0000 C CNN
F 3 "~" H 3750 2900 30  0000 C CNN
	1    3750 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 2500 3750 2650
$Comp
L CONN_3 K1
U 1 1 591DA243
P 2050 2300
F 0 "K1" V 2000 2300 50  0000 C CNN
F 1 "CONN_3" V 2100 2300 40  0000 C CNN
F 2 "" H 2050 2300 60  0000 C CNN
F 3 "" H 2050 2300 60  0000 C CNN
	1    2050 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	2400 2200 2650 2200
Wire Wire Line
	2650 2200 2650 1450
Wire Wire Line
	2650 1450 3750 1450
Wire Wire Line
	3750 1450 3750 1550
Wire Wire Line
	2400 2300 2800 2300
Wire Wire Line
	2400 2400 2650 2400
Wire Wire Line
	2650 2400 2650 3350
Wire Wire Line
	2650 3350 3750 3350
Wire Wire Line
	3750 3350 3750 3150
$EndSCHEMATC
