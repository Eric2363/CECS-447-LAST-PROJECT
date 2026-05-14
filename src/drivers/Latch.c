// Team #4
// Team members: Eric Santana; Dante Jimenez; Alexander Zepeda; Kour, Thaisinge

#include "Latch.h"


void Latch_Init(){
  //Enable Clock for portE
  SYSCTL_RCGCGPIO_R |= PORTE;
  //wait for it finish set up (use PRGPIO, not RCGCGPIO)
  while((SYSCTL_RCGCGPIO_R & PORTE) != PORTE){}

  //GPIO config
  //Enable E0
  GPIO_PORTE_DEN_R |= LATCH_PIN;
  //E0 as output
  GPIO_PORTE_DIR_R |= LATCH_PIN;
  //Disable Analog mode
  GPIO_PORTE_AMSEL_R &= ~LATCH_PIN;
  //Disable alternate function mode
  GPIO_PORTE_AFSEL_R &= ~LATCH_PIN;

  // start low
  GPIO_PORTE_DATA_R &= ~LATCH_PIN;
}

