// Team #4
// Team members: Eric Santana; Dante Jimenez; Alexander Zepeda; Kour, Thaisinge

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



