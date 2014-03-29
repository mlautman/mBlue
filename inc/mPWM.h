#ifndef __M_PWM
#define __M_PWM

#include "mGeneral.h"
#include "mBus.h"

#define 	_MODE1		0x00
#define 	_Mode_1		0b00101110
#define		_Mode_2		0b00000100
#define 	_PRE_SCALE	0xFE
#define 	_RESTART	0b10100000
#define 	_AI		0b00100000
#define 	_SLEEP		0b00110000
//	#define 	_SUB1		0b00001000
//	#define 	_SUB1		0b00000100
//	#define 	_SUB1		0b00000010
//	#define 	_SUB1		0b00000001

#define ALL_PWM 0xFA

uint8_t mPWMinit(uint8_t address, uint16_t freq);
/*************************************************************
 *
 * 	initializes the mPWM device at the specified address
 *
 * 	params: I2C address  	-- 	address
 *		Target PWM freq	--	freq  (24 - 1525 Hz)
 *	return:	uint8_t 
 *			0 - desired frequency out of range 
 *
 *		infinite blue	> unable to make sleep
 *			+white	> unable to set prescaler
 *			+green  > unable to wake up
 *************************************************************/ 

uint8_t mPWMsetDuty( uint8_t address, uint8_t PWMchan, float duty );
/*************************************************************
 *
 * 	sets duty for a PWM channel to the desired amount
 *
 * 	params: I2C address  	-- 	address
 *		Target PWM chan	--	char (1-16)
 *		Duty cycle 	-- 	float (0-100.0)
 *	return:	uint8_t 
 *			0 - desired frequency out of range 
 *
 *		infinite blue	> unable to make sleep
 *			+white	> unable to set prescaler
 *			+green  > unable to wake up
 *************************************************************/



uint8_t mPWMsetDuties( uint8_t address, uint8_t firstChan,  uint8_t numberChan, uint16_t *duties);
/*************************************************************
 *
 * 	sets duty cycle for a number of channels starting 
 * 	with firstChan to the corresponding value in duties
 *
 * 	params: I2C address  	-- 	address
 *		Target PWM chan	--	char (1-16)
 *		Duty cycle 	-- 	float (0-100.0)
 *	return:	uint8_t 
 *			0 - desired frequency out of range 
 *
 *************************************************************/

	
uint8_t mPWMallOn(uint8_t address );
/*************************************************************
 * 	sets all pwm channels to always on
 *
 * 	params: I2C address  	-- 	address
 *	return:	uint8_t	0 	> 	Failure
 *			1 	>	Success
 *************************************************************/


uint8_t mPWMallOff(uint8_t address );
/*************************************************************
 * 	sets all pwm channels to always off
 *
 * 	params: I2C address  	-- 	address
 *	return:	uint8_t 0 	> 	Failure
 *			1 	>	Success
 *************************************************************/
#endif 
