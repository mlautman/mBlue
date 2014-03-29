#include "mGeneral.h"
#include "mBus.h"
#include "mUSB.h"

#define 	SLAVE 		0x98
#define 	SLAVEr		0x99

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



uint8_t toggle_lights( uint16_t n );


volatile char ioSt,ioSt2;
char ioStat[1]={0};
int main(void)
{
	mInit(); mBusInit();
	//	mYellowON; mUSBInit(); mWaitms(3000); mYellowOFF;
	mRedON; while(!mBusPeriphReady(SLAVE)); mRedOFF;
	mBlueON;
	//	printf("set LCR \r\n");
	while(!mBusWrite(SLAVE, _LCR_, _LCR_WRITE_GEN_));
	//		mWait(2500);
	//	ioSt = mBusRead(SLAVEr, _LCR_);
	//		mWait(2500);
	//	printf("IO LCR; \t%c\r\n",ioSt );
	//		mWait(2500);
	//	printf("set IOIntEna \r\n");
	mBusWrite(SLAVE, _IOIntEna_, 0x00);
	//		mWait(2500);
	//	printf("set IOCont \r\n");
	mBusWrite(SLAVE, _IOControl_, 0x02);
	//		mWait(2500);
	//	printf("set IOdir \r\n");
	mBusWrite(SLAVE, _IODir_, 0xFF);
	//		mWait(2500);
	while(1)
	{
		toggle_lights(1000);
	
	}	
}

uint16_t i;
uint8_t toggle_lights( uint16_t n ){
	for (i = 0 ; i<n; i++){
		mWaitms(100);
		while(!mBusWrite(SLAVE, _IOState_, 0x0F));
		mWait( 500);
		while(!mBusReadBurst(SLAVE, _IOState_, 1, ioStat));
		mWait( 500);
	//	ioSt = mBusRead(SLAVE, _IOState_);
		if (ioStat[0]){ mBlueON;mRedOFF; }
		else {mBlueOFF; mRedON;}
		//		printf("IO DIR 0xFF; \t%c\r\n",ioSt );
		mWaitms(100);
		while(!mBusWrite(SLAVE, _IOState_, 0x00));
		mWait( 500);
	//	ioSt = mBusRead(SLAVE, _IOState_);
		//		printf("IO DIR 0x00; \t%c\r\n",ioSt2 );
		//(must be done while device is awake and LCR[7]=1)
		while(!mBusReadBurst(SLAVE, _IOState_, 1, ioStat));
		mWait( 500);
		if (ioStat[0]){ mBlueON;mRedOFF; }
		else {mBlueOFF; mRedON;}
	}

}
