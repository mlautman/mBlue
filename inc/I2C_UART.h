#include "mBus.h"
#include "mGeneral.h"



//////////////////////////////
// General Register Set 
// 
// first set LCR[7]=0 
//////////////////////////////
#define 	_RHR_		0x00<<3 // R
#define 	_THR_		0x00<<3 // W
#define 	_IER_		0x01<<3
#define 	_FCR_		0x02<<3 // W
#define 	_IIR_		0x02<<3 // R
#define 	_LCR_		0x03<<3 
#define 	_MCR_		0x04<<3
#define 	_LSR_		0x05<<3
#define 	_MSR_		0x06<<3
#define 	_TCR_		0x06<<3
#define 	_SPR_		0x07<<3
#define 	_TLR_		0x07<<3 
#define 	_TXLVL_		0x08<<3
#define 	_RXLVL_		0x09<<3

#define		_IODir_		0x0A<<3
#define 	_IOState_	0x0B<<3
#define 	_IOIntEna_	0x0C<<3
#define 	_ALWAYS_0_	0x0D<<3
#define 	_IOControl_	0x0E<<3 // [7:4],[2]=0 [3] software reset [1]=gpio [0]ioLatch
#define 	_EFCR_		0x0F<<3

//////////////////////////////
// Special Register Set 
// 
// first set LCR[7]=1 
// 	     LCR=/=0xBF
//////////////////////////////
#define 	_DLL_		0x00<<3
#define 	_DLH_		0x01<<3

//////////////////////////////
// Enhanced Register Set 
//
// first set: 	LCR=0xBF
//////////////////////////////
#define 	_EFR_		0x02<<3
#define 	_XON1_		0x04<<3
#define 	_XON2_		0x05<<3
#define 	_XOFF1_		0x06<<3
#define 	_XOFF2_		0x07<<3


//////////////////////////////
// Baud generation vals
//////////////////////////////
#define 	DLL_115200	0x08		
#define 	DLH_115200	0x08		

//////////////////////////////
//	LCR settings 
//////////////////////////////
#define _LCR_WRITE_GEN_		0b00010111
#define _LCR_WRITE_SPE_		0b10010111
#define _LCR_WRITE_ENH_		0xBF

