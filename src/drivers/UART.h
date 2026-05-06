#include "../tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>  // for C boolean data type

// standard ASCII symbols
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F
#define NULL 0

#define NVIC_EN0_UART0 0x20     // UART0 IRQ number 5

// UART Functions
// --------------------

void UART_Init(bool RxInt, bool TxInt);
void OutCRLF(void);

uint8_t UART_InChar(void);
void UART_OutChar(uint8_t data);
void UART_OutString(uint8_t *pt);

uint32_t UART_InUDec(void);
void UART_OutUDec(uint32_t n);
uint32_t UART_InUHex(void);
void UART_OutUHex(uint32_t number);
void UART_InString(uint8_t *bufPt, uint16_t max);

// ring buffer helper API
bool UART_Available(void);

// ISR
void UART0_Handler(void);