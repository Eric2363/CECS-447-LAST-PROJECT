// Team #4
// Team members: Eric Santana; Dante Jimenez; Alexander Zepeda; Kour, Thaisinge

 

#include "../tm4c123gh6pm.h"
#include <stdint.h>

/* List of Fill In Macros */

//clock control for wide timer
#define EN_WTIMER_CLOCK			0x00000002 
// Enable timer A
#define WTIMER_TAEN_BIT			0x00000001
//Enable 32-bit timer configuration
#define WTIMER_32_BIT_CFG		0x00000004
// WTimer A mode 
#define WTIMER_TAMR_R_ONE_SHOT 0x01;
//Interupt flag bit for timer A
#define WTIMER_TIMEOUT_FLAG 0x00000001

//1 ms delay values at 16 MHz clock
#define PRESCALER_VALUE 0x00     //Prescaler for 1ms delay resolution
#define WTIMER_1MS_RELOAD 15999 //Reload value for 1ms delay at 16MHz




void WTIMER_Init(void);
void DELAY_1MS(uint32_t);
int16_t map(int16_t, int16_t, int16_t, int16_t, int16_t);

