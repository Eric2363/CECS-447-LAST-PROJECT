/*
 * I2C.h
 *
 *	Provides the I2C Init, Read, and Write Function
 *
 * Created on: May 24th, 2023
 *		Author: Jackie Huynh
 *
 */

#ifndef I2C_H_
#define I2C_H_

#include "../tm4c123gh6pm.h"
#include <stdint.h>

#include "wtimer.h"

/* List of Fill In Macros */

//Init Function
#define EN_I2C1_CLOCK		(0x02) //Enable I2C1 System Clock
#define EN_GPIOA_CLOCK		(0x01) //Enable GPIOA System Clock
#define I2C_PINS			(0xC0) //Pins 6 & 7
#define I2C_ALT_FUNC_MSK	(0x00FFFFFF) //Alternate Function Mask
#define I2C_ALT_FUNC_SET	(0x33000000) //Alternate Function Set
#define I2C_SDA_PIN			(0x80) //Pin 7
#define I2C_SCL_PIN			(0x40) //Pin 6
#define EN_I2C_MASTER		(0x10) //Enable I2C Master Functionality
#define I2C_MTPR_TPR_VALUE	(7) //Value to set for Master Timer Period Register for 100kHz I2C Speed
#define I2C_MTPR_STD_SPEED (CONSTANT_FILL)


//Transmit Function (Most came from above Macros)
#define I2C0_RW_PIN				(CONSTANT_FILL)

//Burst Transmit Function
#define RUN_CMD						(CONSTANT_FILL)

/*
 *	-------------------I2C0_Init------------------
 *	Basic I2C Initialization function for master mode @ 100kHz
 *	Input: None
 *	Output: None
 */
void I2C_Init(void);

/*
 *	-------------------I2C0_Receive------------------
 *	Polls to receive data from specified peripheral
 *	Input: Slave address & Slave Register Address
 *	Output: Returns 8-bit data that has been received
 */
uint8_t I2C_Receive(uint8_t slave_addr, uint8_t slave_reg_addr);

/*
 *	-------------------I2C0_Transmit------------------
 *	Transmit a byte of data to specified peripheral
 *	Input: Slave address, Slave Register Address, Data to Transmit
 *	Output: Any Errors if detected, otherwise 0
 */
uint8_t I2C_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t data);

//Has Yet to be Implemented
/*
 *	----------------I2C0_Burst_Receive-----------------
 *	Polls to receive multiple bytes of data from specified
 *  peripheral by incrementing starting slave register address
 *	Input: Slave address, Slave Register Address, Data Buffer
 *	Output: None
 */
void I2C_Burst_Receive(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size);

/*
 *	----------------I2C0_Burst_Transmit-----------------
 *	Transmit multiple bytes of data to specified peripheral
 *  by incrementing starting slave address
 *	Input: Slave address, Slave Register Address, Data Buffer to transmit, Size of Transmit
 *	Output: None
 */
uint8_t I2C_Burst_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size);

#endif //I2C_H_


