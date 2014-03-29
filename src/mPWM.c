/****************************************
 ****************************************
 **
 **		mPWM library
 **		Author: Michael Lautman
 **		TODO:	- mServo function
 **				- change output settings
 **					(open drain etc...)
 **				- better calibrate freq_Pre_scaler
 ****************************************
 ****************************************/ 

#include 	"mPWM.h"
//#define 	mPWMDebug	1

uint8_t targetFreqPreScale = 0 ; 

uint8_t cleanall[64]={0};

uint8_t mPWMinit(uint8_t address, uint16_t freq){
	//////////////////////////////////////////////////////////////
	//	no negative frequencies
	//////////////////////////////////////////////////////////////
	if (freq<=0) {return 0;}
	//////////////////////////////////////////////////////////////
	//	Put the mPWM to sleep
	//////////////////////////////////////////////////////////////
	while(!mBusWrite(address, _MODE1, _SLEEP ));
	//////////////////////////////////////////////////////////////
	//	Set frequency while mPWM is asleep
	//	targetFreqPreScale = 25MHz/(4096*freq) 
	//	+1 is to improve accuracy in low frequencies 
	//	if you need frequencies greater than 300Hz try -1
	//		Best is to hand calibrate targetFreqPreScale
	//////////////////////////////////////////////////////////////
	targetFreqPreScale= (uint8_t)((0x17D7)/freq) + 1 ;
	//////////////////////////////////////////////////////////////
	//	crop off frequencies beyond the capabilities 
	//	of the device
	//////////////////////////////////////////////////////////////
	if 	(targetFreqPreScale > 0xFF) { targetFreqPreScale=0xFF; }
	else if (targetFreqPreScale < 0x03) { targetFreqPreScale=0x03; } 

#ifdef mPWMDebug
	printf("freq Prescaler: \t%d\r\n",(uint8_t)((0x17D7)/freq));
#endif
	//////////////////////////////////////////////////////////////
	//	finally write the prescaler register
	//////////////////////////////////////////////////////////////
	while(!mBusWrite(address, _PRE_SCALE, targetFreqPreScale));
	//////////////////////////////////////////////////////////////
	//	Wake the mPWM up
	//////////////////////////////////////////////////////////////
	while(!mBusWrite(address, _MODE1, _AI ));
	////////////////////////////////////////////////////////////// 	
	// 	sets all values in PWM registers to 0
	//////////////////////////////////////////////////////////////
	mBusWriteBurst(address, 0x06, 64, cleanall);
	return 1; 
}


#define resolution 	   = 100.0;
volatile uint16_t new_end  = 0x0000; 

uint8_t startStopData[ 4 ] 	= {0};
uint8_t alwaysOnData[4] 	= {0x00,0x10,0x00,0x00};
uint8_t alwaysOffData[4] 	= {0x00,0x00,0x00,0x10};
uint8_t regLength 		= 4;
uint8_t targetChan 		= 0x00;
uint8_t targetChanOffset	=0x06;

uint8_t mPWMsetDuty( uint8_t address, uint8_t PWMchan, float duty ){

	//////////////////////////////////////////////////////////////
	//	The registers for the PWM signals are equal to 
	//	register = 0x06 + 4 * (PWMchan)
	//////////////////////////////////////////////////////////////
	targetChan = (targetChanOffset + regLength*PWMchan);
#ifdef mPWMDebug
	printf("setting channel: \t%d\r\n", targetChan);
	printf("setting Duty to:\t%f\r\n", duty);
#endif
	if (duty >= 99.98){
		while(!mBusWriteBurst(address,targetChan,regLength,alwaysOnData ));
		return 1; }
	else if (duty<0.024){
		while(!mBusWriteBurst(address,targetChan, regLength, alwaysOffData ));
		return 1; }
	startStopData[0] = startStopData[2];
	startStopData[1] = startStopData[3];

	new_end =  (uint16_t)((double)duty*40.960) ; 
	new_end = ((startStopData[1]<<8)+(startStopData[0]))+new_end;
	new_end = new_end & 0x0FFF;
	// ^^ can be made faster if you use the integer cast jawn 
	// 	in order to do this I must flip the order of the 
	// 	low and hi
	
#ifdef mPWMDebug
	printf("length: \t%d\r\n", new_end);
	printf("new End: \t%d\r\n", new_end);
#endif
	startStopData[3] = (uint8_t)(new_end >>8);
	startStopData[2] = (uint8_t)(new_end & 0x00FF);
#ifdef mPWMDebug
	mWait(500);
	printf("old End low: \t%d\r\n", startStopData[0]);
	mWait(500);
	printf("old End hi: \t%d\r\n", startStopData[1]);
	mWait(500);
	printf("new End low: \t%d\r\n", startStopData[2]);
	mWait(500);
	printf("new End hi: \t%d\r\n", startStopData[3]);
	mWait(500);
#endif
	while(!mBusWriteBurst(address, targetChan, regLength, startStopData));
	return 1;
}

uint8_t i;

uint8_t mPWMsetDuties( uint8_t address, uint8_t firstChan,  uint8_t numberChan, uint16_t *duties){
	for (i=0; i<numberChan; i++){
		mPWMsetDuty( address, firstChan+i, duties[i]); }
	return 1;
}

uint8_t mPWMallOff(uint8_t address )
	{return (mBusWriteBurst(address,ALL_PWM,regLength,alwaysOffData ));}
uint8_t mPWMallOn(uint8_t address )
	{return (mBusWriteBurst(address,ALL_PWM,regLength,alwaysOnData )); }
