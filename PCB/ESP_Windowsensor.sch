EESchema Schematic File Version 4
EELAYER 30 0
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
L power:+BATT #PWR0101
U 1 1 605A35AE
P 2400 2200
F 0 "#PWR0101" H 2400 2050 50  0001 C CNN
F 1 "+BATT" H 2415 2373 50  0000 C CNN
F 2 "" H 2400 2200 50  0001 C CNN
F 3 "" H 2400 2200 50  0001 C CNN
	1    2400 2200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0102
U 1 1 605A3D5F
P 2400 3600
F 0 "#PWR0102" H 2400 3350 50  0001 C CNN
F 1 "GND" H 2405 3427 50  0000 C CNN
F 2 "" H 2400 3600 50  0001 C CNN
F 3 "" H 2400 3600 50  0001 C CNN
	1    2400 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT1
U 1 1 605A4932
P 2400 2850
F 0 "BT1" H 2518 2946 50  0000 L CNN
F 1 "Battery_Cell" H 2518 2855 50  0000 L CNN
F 2 "Battery:BatteryHolder_Keystone_1042_1x18650" V 2400 2910 50  0001 C CNN
F 3 "~" V 2400 2910 50  0001 C CNN
	1    2400 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 2650 2400 2200
Wire Wire Line
	2400 2950 2400 3600
$Comp
L RF_Module:ESP-07 IC2
U 1 1 605A54DA
P 9100 2150
F 0 "IC2" H 9100 3131 50  0000 C CNN
F 1 "ESP-07" H 9100 3040 50  0000 C CNN
F 2 "RF_Module:ESP-07" H 9100 2150 50  0001 C CNN
F 3 "http://wiki.ai-thinker.com/_media/esp8266/esp8266_series_modules_user_manual_v1.1.pdf" H 8750 2250 50  0001 C CNN
	1    9100 2150
	1    0    0    -1  
$EndComp
$Comp
L MCU_Microchip_ATtiny:ATtiny13A-SSU IC1
U 1 1 605A6231
P 5700 2300
F 0 "IC1" H 5170 2346 50  0000 R CNN
F 1 "ATtiny13A-SSU" H 5170 2255 50  0000 R CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 5700 2300 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/doc8126.pdf" H 5700 2300 50  0001 C CNN
	1    5700 2300
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0103
U 1 1 605A6F9C
P 5700 1150
F 0 "#PWR0103" H 5700 1000 50  0001 C CNN
F 1 "+BATT" H 5715 1323 50  0000 C CNN
F 2 "" H 5700 1150 50  0001 C CNN
F 3 "" H 5700 1150 50  0001 C CNN
	1    5700 1150
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0104
U 1 1 605A7143
P 8150 1050
F 0 "#PWR0104" H 8150 900 50  0001 C CNN
F 1 "+BATT" H 8165 1223 50  0000 C CNN
F 2 "" H 8150 1050 50  0001 C CNN
F 3 "" H 8150 1050 50  0001 C CNN
	1    8150 1050
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0105
U 1 1 605A739C
P 10300 1000
F 0 "#PWR0105" H 10300 850 50  0001 C CNN
F 1 "+BATT" H 10315 1173 50  0000 C CNN
F 2 "" H 10300 1000 50  0001 C CNN
F 3 "" H 10300 1000 50  0001 C CNN
	1    10300 1000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 605A75EC
P 5700 3650
F 0 "#PWR0106" H 5700 3400 50  0001 C CNN
F 1 "GND" H 5705 3477 50  0000 C CNN
F 2 "" H 5700 3650 50  0001 C CNN
F 3 "" H 5700 3650 50  0001 C CNN
	1    5700 3650
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0107
U 1 1 605A76FD
P 9100 3750
F 0 "#PWR0107" H 9100 3500 50  0001 C CNN
F 1 "GND" H 9105 3577 50  0000 C CNN
F 2 "" H 9100 3750 50  0001 C CNN
F 3 "" H 9100 3750 50  0001 C CNN
	1    9100 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1750 8150 1750
Wire Wire Line
	8150 1750 8150 1050
Wire Wire Line
	5700 1700 5700 1150
Wire Wire Line
	5700 2900 5700 3650
$Comp
L Device:R R1
U 1 1 605A93C6
P 10300 1350
F 0 "R1" H 10370 1396 50  0000 L CNN
F 1 "10k" H 10370 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10230 1350 50  0001 C CNN
F 3 "~" H 10300 1350 50  0001 C CNN
	1    10300 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10300 1200 10300 1000
Wire Wire Line
	10300 1500 10300 1750
Wire Wire Line
	10300 1750 9700 1750
$Comp
L Transistor_FET:BSP129 Q1
U 1 1 605AB378
P 9000 3350
F 0 "Q1" H 9204 3396 50  0000 L CNN
F 1 "BSP129" H 9204 3305 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 9200 3275 50  0001 L CIN
F 3 "https://www.infineon.com/dgdl/Infineon-BSP129-DS-v01_42-en.pdf?fileId=db3a30433c1a8752013c1fc296d2395f" H 9000 3350 50  0001 L CNN
	1    9000 3350
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3750 9100 3550
Wire Wire Line
	9100 3150 9100 2850
Text GLabel 6500 2400 2    50   Input ~ 0
ESP_ON
Text GLabel 8550 3350 0    50   Input ~ 0
ESP_ON
Wire Wire Line
	6500 2400 6300 2400
Wire Wire Line
	8550 3350 8800 3350
$Comp
L Switch:SW_Reed_SPDT SW1
U 1 1 605AD366
P 3850 3850
F 0 "SW1" H 3900 3569 50  0000 C CNN
F 1 "SW_Reed_SPDT" H 3900 3660 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 3850 3850 50  0001 C CNN
F 3 "~" H 3850 3850 50  0001 C CNN
	1    3850 3850
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0108
U 1 1 605ADD19
P 3250 4550
F 0 "#PWR0108" H 3250 4300 50  0001 C CNN
F 1 "GND" H 3255 4377 50  0000 C CNN
F 2 "" H 3250 4550 50  0001 C CNN
F 3 "" H 3250 4550 50  0001 C CNN
	1    3250 4550
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0109
U 1 1 605AE07E
P 3250 3150
F 0 "#PWR0109" H 3250 3000 50  0001 C CNN
F 1 "+BATT" H 3265 3323 50  0000 C CNN
F 2 "" H 3250 3150 50  0001 C CNN
F 3 "" H 3250 3150 50  0001 C CNN
	1    3250 3150
	1    0    0    -1  
$EndComp
Text GLabel 4300 3850 2    50   Input ~ 0
SENSOR
Text GLabel 6500 2300 2    50   Input ~ 0
SENSOR
Wire Wire Line
	6500 2300 6300 2300
Wire Wire Line
	4300 3850 4050 3850
Wire Wire Line
	3550 3750 3250 3750
Wire Wire Line
	3250 3750 3250 3150
Wire Wire Line
	3550 3950 3250 3950
Wire Wire Line
	3250 3950 3250 4550
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 605B2031
P 10050 2950
F 0 "JP?" V 10004 3018 50  0000 L CNN
F 1 "SolderJumper_2_Open" V 10095 3018 50  0000 L CNN
F 2 "" H 10050 2950 50  0001 C CNN
F 3 "~" H 10050 2950 50  0001 C CNN
	1    10050 2950
	0    1    1    0   
$EndComp
$Comp
L Jumper:SolderJumper_2_Open JP?
U 1 1 605B2A13
P 10550 2700
F 0 "JP?" V 10504 2768 50  0000 L CNN
F 1 "SolderJumper_2_Open" V 10595 2768 50  0000 L CNN
F 2 "" H 10550 2700 50  0001 C CNN
F 3 "~" H 10550 2700 50  0001 C CNN
	1    10550 2700
	0    1    1    0   
$EndComp
$EndSCHEMATC
