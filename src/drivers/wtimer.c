// Team #4
// Team members: Eric Santana; Dante Jimenez; Alexander Zepeda; Kour, Thaisinge

 

#include "../tm4c123gh6pm.h"
#include "wtimer.h"

 

// Wide Timer Initialization
void WTIMER_Init(void){
    SYSCTL_RCGCWTIMER_R |= EN_WTIMER_CLOCK;
    while((SYSCTL_RCGCWTIMER_R & EN_WTIMER_CLOCK) == 0);
    
	//disable timer before configuration
    WTIMER1_CTL_R &= ~WTIMER_TAEN_BIT;
	//configure timer for 32bit mode
    WTIMER1_CFG_R = WTIMER_32_BIT_CFG;
	//configure timer for one shot mode
    WTIMER1_TAMR_R = WTIMER_TAMR_R_ONE_SHOT;
	//Load 1ms delay values
    WTIMER1_TAPR_R = PRESCALER_VALUE;  // 0 since we are using 32bit mode
    WTIMER1_TAILR_R = WTIMER_1MS_RELOAD; // For 1ms delay at 16MHz

	//clear timeout flag
	WTIMER1_ICR_R = WTIMER_TIMEOUT_FLAG;
}

//Provides delay in milliseconds using Wide Timer 1
void DELAY_1MS(uint32_t delay){

    for (uint32_t i = 0; i < delay; i++)
    {
        /* Disable timer before reload */
        WTIMER1_CTL_R &= ~WTIMER_TAEN_BIT;

        /* Reload 1 ms values */
				WTIMER1_TAPR_R  = PRESCALER_VALUE;
        WTIMER1_TAILR_R = WTIMER_1MS_RELOAD;

        /* Clear timeout flag */
        WTIMER1_ICR_R = WTIMER_TIMEOUT_FLAG;

        /* Start timer */
        WTIMER1_CTL_R |= WTIMER_TAEN_BIT;

        /* Wait for timeout */
        while ((WTIMER1_RIS_R & WTIMER_TIMEOUT_FLAG) == 0x00)
        {
        }

        /* Clear timeout flag */
        WTIMER1_ICR_R = WTIMER_TIMEOUT_FLAG;
    }
}

