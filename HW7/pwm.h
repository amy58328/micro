/*
 * pwm.h
 *
 *  Created on: Nov 26, 2016
 *      Author: KHWANG-HOME
 */

#ifndef PWM_H_
#define PWM_H_
#define NOTE_C0 16.35
#define NOTE_CS0 17.32
#define NOTE_D0 18.35
#define NOTE_EB0 19.45
#define NOTE_E0 20.60
#define NOTE_F0 21.83
#define NOTE_FS0 23.12
#define NOTE_G0 24.50
#define NOTE_GS0 25.96
#define NOTE_A0 27.50
#define NOTE_BB0 29.14
#define NOTE_B0 30.87

#define NOTE_C1 32.70
#define NOTE_CS1 34.65
#define NOTE_D1 36.71
#define NOTE_EB1 38.89
#define NOTE_E1 41.20
#define NOTE_F1 43.65
#define NOTE_FS1 46.25
#define NOTE_G1 49.00
#define NOTE_GS1 51.91
#define NOTE_A1 55.00
#define NOTE_BB1 58.27
#define NOTE_B1 61.74

#define NOTE_C2 65.41
#define NOTE_CS2 69.30
#define NOTE_D2 73.42
#define NOTE_EB2 77.78
#define NOTE_E2 82.41
#define NOTE_F2 87.31
#define NOTE_FS2 92.50
#define NOTE_G2 98.00
#define NOTE_GS2 103.83
#define NOTE_A2 110.00
#define NOTE_BB2 116.54
#define NOTE_B2 123.47

#define NOTE_C3 130.81
#define NOTE_CS3 138.59
#define NOTE_D3 146.83
#define NOTE_EB3 155.56
#define NOTE_E3 164.81
#define NOTE_F3 174.61
#define NOTE_FS3 185.00
#define NOTE_G3 196.00
#define NOTE_GS3 207.65
#define NOTE_A3 220.00
#define NOTE_BB3 233.08
#define NOTE_B3 246.94
//低音--------------------
#define NOTE_C4 261.63		//1
#define NOTE_CS4 277.18		//#1
#define NOTE_D4 293.66		//2
#define NOTE_EB4 311.13		//#2
#define NOTE_E4 329.63		//3
#define NOTE_F4 349.23		//4
#define NOTE_FS4 369.99		//#4
#define NOTE_G4 392.00		//5
#define NOTE_GS4 415.30		//#5
#define NOTE_A4 440.00		//6
#define NOTE_BB4 466.16		//#6
#define NOTE_B4 493.88		//7
//中音--------------------
#define NOTE_C5 523.25
#define NOTE_CS5 554.37
#define NOTE_D5 587.33
#define NOTE_EB5 622.25
#define NOTE_E5 659.26
#define NOTE_F5 698.46
#define NOTE_FS5 739.99
#define NOTE_G5 783.99
#define NOTE_GS5 830.61
#define NOTE_A5 880.00
#define NOTE_BB5 932.33
#define NOTE_B5 987.77
//高音---------------------
#define NOTE_C6 1046.50
#define NOTE_CS6 1108.73
#define NOTE_D6 1174.66
#define NOTE_EB6 1244.51
#define NOTE_E6 1318.51
#define NOTE_F6 1396.91
#define NOTE_FS6 1479.98
#define NOTE_G6 1567.98
#define NOTE_GS6 1661.22
#define NOTE_A6 1760.00
#define NOTE_BB6 1864.66
#define NOTE_B6 1975.53

#define NOTE_C7 2093.00
#define NOTE_CS7 2217.46
#define NOTE_D7 2349.32
#define NOTE_EB7 2489.02
#define NOTE_E7 2637.02
#define NOTE_F7 2793.83
#define NOTE_FS7 2959.96
#define NOTE_G7 3135.96
#define NOTE_GS7 3322.44
#define NOTE_A7 3520.01
#define NOTE_BB7 3729.31
#define NOTE_B7 3951.07

#define NOTE_C8 4186.01
#define NOTE_CS8 4434.92
#define NOTE_D8 4698.64
#define NOTE_EB8 4978.03

#define ONE_SECOND 1000000

#define t 250000
#define pause 0

/*
#define GPIO_ACT_PD *((unsigned int *)0x001F6980) //GPIO port D
#define PWM_EN *((unsigned int *)0x001F6000)
#define PWM_BAS_CLK *((unsigned int *)0x001F6004)
#define PWM_CLK2 *((unsigned int *)0x001F6010)
#define PWM2 *((unsigned int *)0x001F6020)
#define PERIOD_2 *((unsigned int *)0x001F6030)
*/


/*int music[][2]={
	           {NOTE_G4,1},{NOTE_C5,1},{NOTE_D5,1},
			   {NOTE_E5,2},{NOTE_E5,2},
			   {pause,1},{NOTE_E5,1},{NOTE_EB5,1},{NOTE_E5,1},
			   {NOTE_C5,2},{NOTE_C5,2},

			   {pause,1},{NOTE_C5,1},{NOTE_D5,1},{NOTE_E5,1},
			   {NOTE_F5,2},{NOTE_A5,2},
			   {pause,1},{NOTE_A5,1 },{NOTE_G5,1 },{NOTE_F5,1},
			   {NOTE_E5,4},
			   {pause,1},{NOTE_C5,1},{NOTE_D5,1},{NOTE_E5,1},


			   };*/



#endif /* PWM_H_ */
