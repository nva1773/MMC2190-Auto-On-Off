#ifndef _HEADER_H
#define _HEADER_H

/** O S C ***********************************************************/
// OSC = 4 MHz
#define OSCILLATOR	4000000
#define INSTRUCTION_CYCLE (OSCILLATOR)/4

/** I S R  *********************************************************/
#define mIsrEN() PEIE = 1; GIE = 1
#define mIsrDI() PEIE = 0; GIE = 0

/** P O R T S ******************************************************/
#define mResetPorts() {CMCON = 0x07;		\
					   ANSEL = 0x00;		\
					   GPIO = 0xFF;			\
					   TRISIO = 0xFF;		\
					   IOCB = 0x00;			\
					   WPU = 0x00;}

/** T I M E R 1 *****************************************************/
// Timer1 = 100Hz -> 10ms (Fosc/4, prescale 1:1)
#define TMR1_VALUE 65535 - 10000 + 22
#define mInitTimer1() T1CON = 0x00
#define mStartTimer1() TMR1IF = 0; TMR1IE = 1; TMR1ON = 1
#define mStopTimer1() TMR1ON = 0; TMR1IF = 0; TMR1IE = 0
#define mLoadTimer1() TMR1 = TMR1_VALUE
#define mFlagTimer1 TMR1IF
#define mInterruptTimer1 TMR1IE&&TMR1IF

/** W D T **********************************************************/
// Wdt = 18ms, Prescale = 1:64, Delay = 18*64 = 1152ms
#define mInitWDT() OPTION_REG &= 0b11001110

/** K E Y **********************************************************/
#define KEY_PIN GP0			// In or Out - Emulation Key Press (Pin7)
#define mInitKEY() TRIS0 = 1
#define mDownKEY() TRIS0 = 0; KEY_PIN = 0
#define mUpKEY() TRIS0 = 1

/** A C C & M 5 V **************************************************/
#define ACC_PIN GP1			// Input ACC (Pin6)
#define M5V_PIN GP2			// Input M5V (Pin5)
#define mInitACC() TRIS1 = 1
#define mInitM5V() TRIS2 = 1
#define ON 1
#define OFF 0

/** D E F I N E ****************************************************/
// One Tick = 10ms
#define Delay100ms 10		// For contact bounce
#define Delay1Sec 100		// For one second tick
#define Delay2Sec 200		// For emulation key down
#define Time60Min 3600		// For timeout

// end file
#endif