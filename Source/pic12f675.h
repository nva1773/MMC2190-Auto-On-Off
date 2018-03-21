/* PIC12F675 Register Library for programming on the PICC as in MCC18 */
#ifndef _PIC12F675
#define _PIC12F675

/*-------------------------------------------------------------------------*/
// Processor registers PIC12F675
/*-------------------------------------------------------------------------*/
// Bank 0
#byte INDF			= 0x00
#byte TMR0			= 0x01
#byte PCL			= 0x02
#byte STATUS		= 0x03
#byte FSR			= 0x04
#byte GPIO			= 0x05
#byte PCLATH		= 0x0A
#byte INTCON		= 0x0B
#byte PIR1			= 0x0C
#byte TMR1L			= 0x0E
#byte TMR1H			= 0x0F
#byte T1CON			= 0x10
#byte CMCON			= 0x19
#byte ADRESH		= 0x1E
#byte ADCON0		= 0x1F
// Bank 1
#byte OPTION_REG	= 0x81
#byte TRISIO		= 0x85
#byte PIE1			= 0x8C
#byte PCON			= 0x8E
#byte OSCCAL		= 0x90
#byte WPU			= 0x95
#byte IOCB			= 0x96
#byte VRCON			= 0x99
#byte EEDATA		= 0x9A
#byte EEADR			= 0x9B
#byte EECON1		= 0x9C
#byte EECON2		= 0x9D
#byte ADRESL		= 0x9E
#byte ANSEL			= 0x9F

/*-------------------------------------------------------------------------*/
// Processor Processor Bits PIC12F675
/*-------------------------------------------------------------------------*/
// Bank 0
#bit C				= STATUS. 0
#bit DC				= STATUS. 1
#bit Z				= STATUS. 2
#bit RP0			= STATUS. 5
//
#bit GP0			= GPIO. 0
#bit GP1			= GPIO. 1
#bit GP2			= GPIO. 2
#bit GP3			= GPIO. 3
#bit GP4			= GPIO. 4
#bit GP5			= GPIO. 5
//
#bit GPIF			= INTCON. 0
#bit INTIF			= INTCON. 1
#bit T0IF			= INTCON. 2
#bit GPIE			= INTCON. 3
#bit INTIE			= INTCON. 4
#bit T0IE			= INTCON. 5
#bit PEIE			= INTCON. 6
#bit GIE			= INTCON. 7
//
#bit TMR1IF			= PIR1. 0
#bit CMIF			= PIR1. 3
#bit ADIF			= PIR1. 6
#bit EEIF			= PIR1. 7
//
#bit TMR1ON			= T1CON. 0
#bit TMR1CS			= T1CON. 1
#bit T1SYNC			= T1CON. 2
#bit T1OSCEN		= T1CON. 3
#bit T1CKPS0		= T1CON. 4
#bit T1CKPS1		= T1CON. 5
#bit TMR1GE			= T1CON. 6
//
#bit CM0			= CMCON. 0
#bit CM1			= CMCON. 1
#bit CM2			= CMCON. 2
#bit CIS			= CMCON. 3
#bit CINV			= CMCON. 4
#bit COUT			= CMCON. 6
//
#bit ADON			= ADCON0. 0
#bit GO				= ADCON0. 1
#bit CHS0			= ADCON0. 2
#bit CHS1			= ADCON0. 3
#bit VCFG			= ADCON0. 6
#bit ADFM			= ADCON0. 7
// Bank 1
#bit PS0			= OPTION_REG. 0
#bit PS1			= OPTION_REG. 1
#bit PS2			= OPTION_REG. 2
#bit PSA			= OPTION_REG. 3
#bit T0SE			= OPTION_REG. 4
#bit T0CS			= OPTION_REG. 5
#bit INTEDG			= OPTION_REG. 6 
#bit NOT_RBPU		= OPTION_REG. 7
//
#bit TRIS0			= TRISIO. 0
#bit TRIS1			= TRISIO. 1
#bit TRIS2			= TRISIO. 2
#bit TRIS3			= TRISIO. 3
#bit TRIS4			= TRISIO. 4
#bit TRIS5			= TRISIO. 5
//
#bit TMR1IE			= PIE1. 0
#bit CMIE			= PIE1. 3
#bit ADIE			= PIE1. 6
#bit EEIE			= PIE1. 7
//
#bit NOT_BOD			= PCON. 0
#bit NOT_POR			= PCON. 1
//
#bit WPU0			= WPU. 0
#bit WPU1			= WPU. 1
#bit WPU2			= WPU. 2
#bit WPU4			= WPU. 4
#bit WPU5			= WPU. 5
//
#bit IOCB0			= IOCB. 0
#bit IOCB1			= IOCB. 1
#bit IOCB2			= IOCB. 2
#bit IOCB3			= IOCB. 3
#bit IOCB4			= IOCB. 4
#bit IOCB5			= IOCB. 5
//
#bit VR0			= VRCON. 0
#bit VR1			= VRCON. 1
#bit VR2			= VRCON. 2
#bit VR3			= VRCON. 3
#bit VRR			= VRCON. 5
#bit VREN			= VRCON. 7
//
#bit RD				= EECON1. 0
#bit WR				= EECON1. 1
#bit WREN			= EECON1. 2
#bit WRERR			= EECON1. 3
//
#bit ANS0			= ANSEL. 0
#bit ANS1			= ANSEL. 1
#bit ANS2			= ANSEL. 2
#bit ANS3			= ANSEL. 3
#bit ADCS0			= ANSEL. 4
#bit ADCS1			= ANSEL. 5
#bit ADCS2			= ANSEL. 6

/*-------------------------------------------------------------------------*/
// Local Registers and Variables
/*-------------------------------------------------------------------------*/
int16 TMR1;
#locate TMR1		= 0x0E
//
#byte SavePORT		= 0x5C
#byte SaveFSR		= 0x5D
#byte SaveWREG		= 0x5E
#byte SaveSTATUS	= 0x5F

/*-------------------------------------------------------------------------*/
// Command and Type Defines
/*-------------------------------------------------------------------------*/
#define _asm #asm
#define _endasm #endasm
#define ClrWdt() _asm clrwdt _endasm
#define Sleep()  _asm sleep _endasm
#define Reset()  _asm reset _endasm
#define Swapf(dest,access) _asm swapf dest,access _endasm
#define Nop() _asm nop _endasm
#define Retfie() _asm retfie _endasm
#define W 0
#define F 1
#define word long

/*-------------------------------------------------------------------------*/
// Functions of loading the OSCCAL register with a table value
/*-------------------------------------------------------------------------*/
void LoadOSC(void)
{
 _asm 
 clrf	STATUS
 bsf	STATUS, 5 
 call	0x3ff 
 movwf	OSCCAL
 _endasm
}

/*-------------------------------------------------------------------------*/
// Functions for saving and restoring the context during an interrupt
/*-------------------------------------------------------------------------*/
void Push(void)
{
 _asm 
 movwf	SaveWREG
 swapf	STATUS, W
 movwf	SaveSTATUS
 swapf	FSR, W
 movwf	SaveFSR
 _endasm
}

void Pop(void)
{
 _asm
 swapf	SaveFSR, W
 movwf	FSR
 swapf	SaveSTATUS, W
 movwf	STATUS
 swapf	SaveWREG, F
 swapf	SaveWREG, W
 _endasm
}

#endif
