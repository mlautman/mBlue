
/*
 * File:   pca9685_reg.h
 * Author: MLAUTMAN 
 */

#ifndef pca9685_H
#define pca9685_H
/* General registers */
#define Reset   0x01         // Reset the device
#define MODE1   0x00          // 0x00 location for Mode1 register address
#define MODE2   0x01          // 0x01 location for Mode2 reigster address
//#define LED0    0x06          // location for start of LED0 registers
//#define LEDCOUNT 15          // number of LEDS to light 15 max
/* MODE1 bits */
#define	PRE_SCALE	0xFE
/* MODE2 bits */
#define PCA9685_INVRT   0x10
#define PCA9685_OCH     0x08
#define PCA9685_OUTDRV  0x04
#define PCA9685_OUTNE1  0x02
#define PCA9685_OUTNE0  0x01

/* LEDX_ON_H bits */
#define PCA9685_LED_ON 0x10

/* LEDX_OFF_H bits */
#define PCA9685_LED_OFF 0x10

#define LED0_ON_L	0x06
#define LED0_ON_H	0x07
#define LED0_OFF_L	0x08
#define LED0_OFF_H	0x09
#define LED1_ON_L	0x0A
#define LED1_ON_H	0x0B
#define LED1_OFF_L	0x0C
#define LED1_OFF_H	0x0D
#define LED2_ON_L	0x0E
#define LED2_ON_H	0x0F
#define LED2_OFF_L	0x10
#define LED2_OFF_H	0x11
#define LED3_ON_L	0x12
#define LED3_ON_H	0x13
#define LED3_OFF_L	0x14
#define LED3_OFF_H	0x15
#define LED4_ON_L	0x16
#define LED4_ON_H	0x17
#define LED4_OFF_L	0x18
#define LED4_OFF_H	0x19
#define LED5_ON_L	0x1A
#define LED5_ON_H	0x1B
#define LED5_OFF_L	0x1C
#define LED5_OFF_H	0x1D
#define LED6_ON_L	0x1E
#define LED6_ON_H	0x1F
#define LED6_OFF_L	0x20
#define LED6_OFF_H	0x21
#define LED7_ON_L	0x22
#define LED7_ON_H	0x23
#define LED7_OFF_L	0x24
#define LED7_OFF_H	0x25
#define LED8_ON_L	0x26
#define LED8_ON_H	0x27
#define LED8_OFF_L	0x28
#define LED8_OFF_H	0x29
#define LED9_ON_L	0x2A
#define LED9_ON_H	0x2B
#define LED9_OFF_L	0x2C
#define LED9_OFF_H	0x2D
#define LED10_ON_L	0x2E
#define LED10_ON_H	0x2F
#define LED10_OFF_L	0x30
#define LED10_OFF_H	0x31
#define LED11_ON_L	0x32
#define LED11_ON_H	0x33
#define LED11_OFF_L	0x34
#define LED11_OFF_H	0x35
#define LED12_ON_L	0x36
#define LED12_ON_H	0x37
#define LED12_OFF_L	0x38
#define LED12_OFF_H	0x39
#define LED13_ON_L	0x3A
#define LED13_ON_H	0x3B
#define LED13_OFF_L	0x3C
#define LED13_OFF_H	0x3D
#define LED14_ON_L	0x3E
#define LED14_ON_H	0x3F
#define LED14_OFF_L	0x40
#define LED14_OFF_H	0x41
#define LED15_ON_L	0x42
#define LED15_ON_H	0x43
#define LED15_OFF_L	0x44
#define LED15_OFF_H	0x45




#endif
