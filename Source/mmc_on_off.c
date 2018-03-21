//*****************************************************************************
// GP0 - Input: KEY
// GP1 - Input: ACC
// GP2 - Input: M5V
// GP3 - MCLR
// GP4 - NC
// GP5 - NC
//*****************************************************************************

/** I N C L U D E S **********************************************************/
#include <12f675.h>
#include "pic12f675.h"
#include "header.h"

/** C O N F I G U R A T I O N   B I T S **************************************/ 
// configuration bits: intrc_io, nomclr, wdt, nobrownout
#pragma fuses intrc_io, nomclr, wdt, brownout, noprotect
// for used delay_mc(x) and delay_us(x))
//#pragma use delay (clock = 4M)

/** I N T E R R U P T  V E C T O R S *****************************************/
// We use our interrupt function, allocating for it the program memory space
// using the preprocessor #org start, end
#pragma org 0x0004, 0x0014
void Interrupts(void);
void isr(void)
{
 Push();
 Interrupts();
 Pop();
 Retfie();
}

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void InitCPU(void);
void InitVar(void);
void ReadInputs(void);
void ServiceACC(void);
void ServiceM5V(void);

/** V A R I A B L E S ********************************************************/
byte Flag, DelayCount;
int16 TimeOut;

// Bits
#bit fEnableWork	= Flag. 0
#bit fWeakUp_ACC	= Flag. 1
#bit fWeakUp_M5V	= Flag. 2
#bit fWork			= Flag. 3

//
#bit fDelaySS		= Flag. 4
#bit fTimeOut		= Flag. 5
#bit fShutDown		= Flag. 6
#bit fWeakUp		= Flag. 7

/** I N T E R R U P T ********************************************************/
void Interrupts(void)
{
  	// TMR1 - 10ms
  	if(mInterruptTimer1)
  	{
	  	mFlagTimer1 = false;
	  	mLoadTimer1();
	  	Clrwdt();
	  	// Delay Start/Stop -------------------------------
	  	if(fDelaySS)
	  	{
		  	if(DelayCount == 0) 
		  	{
		  		Flag &= 0x0F; // Clear all Delay and Timeout
		  		mUpKEY();	  // Emulation pop Key
		  	}
		  	else
		  		DelayCount--;
		}
		// TimeOut ----------------------------------------
		if(fTimeOut)
		{
			if(DelayCount == 0)
		  	{
				TimeOut--;
				if(TimeOut == 0)
				{
					fTimeOut = false;
					fShutDown = true;
				}
				DelayCount = Delay1Sec;
			}
			else
				DelayCount--;
		}
		// ShutDown ---------------------------------------
		if(fShutDown)
		{
			if(DelayCount == 0)
			{ 
		  		mDownKEY();   // Emulation push Key
		  		Flag &= 0x01; // Clear all bits, except fEnableWork
		  		DelayCount = Delay2Sec; // 2S
				fDelaySS = true; // Delay Start/Stop
		  	}
		  	else
		  		DelayCount--;
		}
		// WeakUp -----------------------------------------
		if(fWeakUp)
		{
			if(DelayCount == 0)
			{ 
		  		mDownKEY();   // Emulation push Key
		  		Flag &= 0x0F; // Clear all Delay and Timeout
		  		DelayCount = Delay2Sec; // 2S
		  		fDelaySS = true; // Delay Start/Stop
		  	}
		  	else
		  		DelayCount--;
		}
  	}
 }//end interrupt	 

/******************************************************************************
 * Function:        void main(void)
 *****************************************************************************/
void main(void)
{
 // Initialization CPU
 LoadOSC();
 InitCPU();
 // Initialization variable
 InitVar();
 // Main cycle
 while(true)
 {
	// Interrupt enable
 	mIsrEN();
	// Delay Start/Stop or M5V_ON
 	while(fDelaySS || fShutDown || M5V_PIN) continue;
 	mUpKEY();
 	mStopTimer1();	// Stop Timer1
 	Flag &= 0x01;	// Clear all bits, except fEnableWork
	// SLEEP, weakup for WDT every one 1152ms -----------------------
	Sleep();
	Nop();
	// Read Inputs: ACC & M5V ---------------------------------------
	ReadInputs();
	// WeakUp
	if(fWeakUp_ACC)
		ServiceACC();
	else if(fWeakUp_M5V)
		ServiceM5V();
 }//end while
}// end main

/******************************************************************************
 * Function:        static void InitCPU(void)
 *****************************************************************************/
void InitCPU(void)
{
	// PORTS
	mResetPorts();
	// Output and Input
	mInitKEY();
	mInitACC();
	mInitM5V();
	mInitWDT();
	// Timer0
	mInitTimer1();
	mLoadTimer1();
	mStartTimer1();
}

/******************************************************************************
 * Function:        static void InitVar(void)
 *****************************************************************************/
void InitVar(void)
{
	Flag = 0;
	DelayCount = Delay1Sec; // 1S
	fDelaySS = true; // Delay Start/Stop
}

/******************************************************************************
 * Function:        static void ReadInputs(void)
 *****************************************************************************/
void ReadInputs(void)
{
	// WeakUp on ACC ----------------------------------
	if(ACC_PIN == ON)
	{
	  	// Start Timer1
		mLoadTimer1();
		mStartTimer1();
		//
	  	if(fEnableWork)
	  	{
	  		DelayCount = Delay1Sec;
	  		fWeakUp = true;
	  		while(fWeakUp || fDelaySS) continue;
	  	}
	  	//
	  	fWeakUp_ACC = true;
	}
	// WeakUP on M5V ----------------------------------
	else if(M5V_PIN == ON)
	{
		// Start Timer1
		mLoadTimer1();
		mStartTimer1();
		//
		DelayCount = Delay1Sec;
	  	TimeOut = Time60Min;
	  	fTimeOut = true;
	  	//
	  	fWeakUp_M5V = true;
	}
}

/******************************************************************************
 * Function:        static void ServiceACC(void)
 *****************************************************************************/
void ServiceACC(void)
{
	while(fWeakUp_ACC){
	// Interrupt disable
	mIsrDI();

	// if ACC == ON
	if(ACC_PIN == ON)
	{
		if(!fWork)
		{
			if(M5V_PIN == ON)
			{
				fWork = true;
				DelayCount = Delay100ms;
				fDelaySS = true;
				// Interrupt enable
				mIsrEN();
				while(fDelaySS) continue;
				// Interrupt enable
				mIsrDI();
			}
		}
		else
		{
			if(M5V_PIN == OFF)
			{
				Flag = 0x00; // Clear all bits
				DelayCount = Delay100ms;
				fDelaySS = true;
			}
		}
	}
	// ACC == OFF
	else
	{
		fWeakUp_ACC = false;
		DelayCount = Delay100ms;
		if(fWork)
		{
			fEnableWork = true;
			fShutDown = true;
		}
		else
		{
			if(fEnableWork)
				fShutDown = true;
			else
				fDelaySS = true;	
		}
	}
	// Interrupt enable
	mIsrEN();
 }//end while
}

/******************************************************************************
 * Function:        static void ServiceM5V(void)
 *****************************************************************************/
void ServiceM5V(void)
{
	while(fWeakUp_M5V){
	// Interrupt disable
	mIsrDI();
	
	// if ACC == ON
	if(ACC_PIN == ON)
		fTimeOut = false;
	// if M5D == OFF
	if(M5V_PIN == OFF)
	{
		Flag &= 0x01;
		DelayCount = Delay100ms;
		fDelaySS = true; 
 	}
	// Interrupt enable
	mIsrEN();
 }//end while
}
