/*
 * ButtonLED.h
 *
 *	Provides function to initialize the onboard RGB LED and
 *	buttons on the TIVA TM4C as well as macros for the different
 *	possible color combination 
 *
 * Created on: March 1st, 2023
 *		Author: Jackie Huynh
 *
 */
 #include "../tm4c123gh6pm.h"

#define PORTF 0x20
#define LEVEL2 0x00400000

//LEDS
#define LEDS 0x0E
#define RED 0x02
#define BLUE 0x04
#define GREEN 0x08



//Switches
#define SWITCHES 0x11
#define SW1 0x10
#define SW2 0x01


void LED_Init(void);
void BTN_Init(void);



