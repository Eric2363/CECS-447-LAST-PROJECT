/*
 * ButtonLED.c
 *
 * Created on: March 1st, 2023
 *		Author: Jackie Huynh
 *
 */
 
#include "ButtonLED.h"
volatile int ledState = 0;

//LED Initialization
void LED_Init(void){
	//Turn on PortF clock
	SYSCTL_RCGCGPIO_R |= PORTF;
	//wait for clock to initalize
	while((SYSCTL_RCGCGPIO_R & PORTF) != PORTF);
	//Unlock PortF
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	//Allow changes to all portf pins
	GPIO_PORTF_CR_R |= 0x1F;

	//LED Congiguration
	GPIO_PORTF_DIR_R |= LEDS; //Set LED pins as output
	GPIO_PORTF_DEN_R |= LEDS; //Enable digital function for LED pins
	GPIO_PORTF_AMSEL_R &=~ LEDS; //Disable analog function for LED pins
	GPIO_PORTF_AFSEL_R &=~ LEDS; //Disable alternate function for LED pins
	
	//GPIO_PORTF_DATA_R = 0x00;
	
}

//Switch Initialization
void BTN_Init(void){
	//Turn on PortF clock
	SYSCTL_RCGCGPIO_R |= PORTF;
	//wait for clock to initalize
	while((SYSCTL_RCGCGPIO_R & PORTF) != PORTF);
	//Unlock PortF
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	//Allow changes to all portf pins
	GPIO_PORTF_CR_R |= 0x1F;

	//Switch Congiguration
	GPIO_PORTF_DIR_R &=~ SWITCHES; //Set switch pins as input
	GPIO_PORTF_DEN_R |= SWITCHES; //Enable digital function for switch pins
	GPIO_PORTF_AMSEL_R &=~ SWITCHES; //Disable analog function for switch pins
	GPIO_PORTF_AFSEL_R &=~ SWITCHES; //Disable alternate function for switch pins
	GPIO_PORTF_PUR_R |= SWITCHES; //Enable internal pull-up resistors for switch pins

	//Interrupt Configuration
	GPIO_PORTF_IS_R &=~ SWITCHES; //Set switch pins to be edge-sensitive
	GPIO_PORTF_IBE_R &=~ SWITCHES; //Set switch pins to trigger on a single edge
	GPIO_PORTF_IEV_R &=~ SWITCHES; //Set switch pins to trigger on falling edge
	GPIO_PORTF_ICR_R = SWITCHES; //Clear any prior interrupt flags for switch pins
	GPIO_PORTF_IM_R |= SWITCHES; //Arm interrupt for switch pins

	//Interupt Priority Configuration
	NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF00FFFF) | LEVEL2; //Set PortF interrupt priority to 2
	NVIC_EN0_R |= 0x40000000; //Enable interrupt for PortF
}



