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
LIBS:ht12d
LIBS:Rx-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "3 may 2017"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L HT12D Decoder1
U 1 1 5909F402
P 1650 4300
F 0 "Decoder1" H 1950 7100 60  0000 C CNN
F 1 "HT12D" H 1950 7200 60  0000 C CNN
F 2 "~" H 1950 7100 60  0000 C CNN
F 3 "~" H 1950 7100 60  0000 C CNN
	1    1650 4300
	1    0    0    -1  
$EndComp
$Comp
L CONN_4 RF1
U 1 1 5909F4A7
P 3600 3050
F 0 "RF1" V 3550 3050 50  0000 C CNN
F 1 "RX" V 3650 3050 50  0000 C CNN
F 2 "" H 3600 3050 60  0000 C CNN
F 3 "" H 3600 3050 60  0000 C CNN
	1    3600 3050
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 5909F4B8
P 2900 2100
F 0 "R1" V 2980 2100 40  0000 C CNN
F 1 "50k" V 2907 2101 40  0000 C CNN
F 2 "~" V 2830 2100 30  0000 C CNN
F 3 "~" H 2900 2100 30  0000 C CNN
	1    2900 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1400 1650 1300 1650
Wire Wire Line
	1300 1650 1300 3650
Wire Wire Line
	1300 1800 1400 1800
Wire Wire Line
	1300 1950 1400 1950
Connection ~ 1300 1800
Wire Wire Line
	1300 2100 1400 2100
Connection ~ 1300 1950
Wire Wire Line
	1300 2250 1400 2250
Connection ~ 1300 2100
Wire Wire Line
	1300 2400 1400 2400
Connection ~ 1300 2250
Wire Wire Line
	1300 2550 1400 2550
Connection ~ 1300 2400
Wire Wire Line
	1300 2700 1400 2700
Connection ~ 1300 2550
Wire Wire Line
	1300 2850 1400 2850
Connection ~ 1300 2700
Wire Wire Line
	2500 2100 2650 2100
Wire Wire Line
	3750 1450 3750 2700
Wire Wire Line
	3650 2250 3650 2700
Wire Wire Line
	3650 2250 2500 2250
Wire Wire Line
	3450 1950 3450 2700
Wire Wire Line
	1300 3100 3100 3100
Wire Wire Line
	3100 3100 3100 2450
Wire Wire Line
	3100 2450 3450 2450
Connection ~ 3450 2450
Connection ~ 1300 2850
Wire Wire Line
	2500 1650 3300 1650
Wire Wire Line
	3300 1650 3300 1800
Wire Wire Line
	3300 1800 3750 1800
Connection ~ 3750 1800
$Comp
L LED D1
U 1 1 5909F77F
P 2850 3350
F 0 "D1" H 2850 3450 50  0000 C CNN
F 1 "LED Status" H 2850 3250 50  0000 C CNN
F 2 "~" H 2850 3350 60  0000 C CNN
F 3 "~" H 2850 3350 60  0000 C CNN
	1    2850 3350
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 5909F7CA
P 2100 3650
F 0 "R2" V 2180 3650 40  0000 C CNN
F 1 "220" V 2107 3651 40  0000 C CNN
F 2 "~" V 2030 3650 30  0000 C CNN
F 3 "~" H 2100 3650 30  0000 C CNN
	1    2100 3650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2350 3650 2850 3650
Wire Wire Line
	2850 3650 2850 3550
Wire Wire Line
	1300 3650 1850 3650
Connection ~ 1300 3100
Wire Wire Line
	2500 2850 2850 2850
Wire Wire Line
	2850 2350 2850 3150
Wire Wire Line
	2500 1950 3200 1950
Wire Wire Line
	3200 1950 3200 2100
Wire Wire Line
	3200 2100 3150 2100
$Comp
L CONN_3 K?
U 1 1 590A019B
P 3650 1100
F 0 "K?" V 3600 1100 50  0000 C CNN
F 1 "CONN_3" V 3700 1100 40  0000 C CNN
F 2 "" H 3650 1100 60  0000 C CNN
F 3 "" H 3650 1100 60  0000 C CNN
	1    3650 1100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3450 1950 3650 1950
Wire Wire Line
	3650 1950 3650 1450
Wire Wire Line
	2850 2350 3400 2350
Wire Wire Line
	3400 2350 3400 1650
Wire Wire Line
	3400 1650 3550 1650
Wire Wire Line
	3550 1650 3550 1450
Connection ~ 2850 2850
$EndSCHEMATC
