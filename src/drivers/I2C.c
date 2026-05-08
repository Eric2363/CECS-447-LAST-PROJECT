/*
 * I2C.c
 *
 *	Main implementation of the I2C Init, Read, and Write Function
 *
 * Created on: May 24th, 2023
 *		Author: Jackie Huynh
 *
 */
 
#include "I2C.h"


/*
 *	-------------------I2C0_Init------------------
 *	Basic I2C Initialization function for master mode @ 100kHz
 *	Input: None
 *	Output: None
 Using I2C1: I2C1SCL: PA6, I2C1SDA: PA7
 */
void I2C_Init(void){
	
	/* Enable Required System Clock */
	//Enable I2C0 System Clock
	//Enable GPIOA System Clock
	SYSCTL_RCGCGPIO_R |= EN_GPIOA_CLOCK;
	SYSCTL_RCGCI2C_R |= EN_I2C1_CLOCK;
	//Wait Until GPIOA System Clock is enabled
	while((SYSCTL_RCGCGPIO_R & EN_GPIOA_CLOCK) != EN_GPIOA_CLOCK){};
	
	/* GPIOA I2C Alternate Function Setup	*/
	//Enable Digital I/O
	//Enable Alternate Function Selection
	GPIO_PORTA_DEN_R |= I2C_PINS;
	GPIO_PORTA_DIR_R |= I2C_PINS;//Set Pins 6 & 7 as output
	//Select I2C1 as the alternate function 	
	//Enable Open Drain for SDA pin
	//Disable Analog Mode
	GPIO_PORTA_AFSEL_R |= I2C_PINS;
	GPIO_PORTA_AMSEL_R &= ~I2C_PINS;
	GPIO_PORTA_ODR_R |= I2C_SDA_PIN;
	GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & I2C_ALT_FUNC_MSK) | I2C_ALT_FUNC_SET;
	/*	I2C1 Setup as Master Mode @ 100kBits	*/
	//Configure I2C1 as Master 
	I2C1_MCR_R |= EN_I2C_MASTER;
	/* Configuring I2C Clock Frequency to 100KHz
		
		TPR = (System Clock / (2*(SCL_LP + SCL_HP) * SCL_CLK)) - 1
		SCL_LP and SCL_HP are fixed
		SCL_LP = 6 & SCL_HP = 4
		
		Example if we want to configure I2C speed to 100kHz for 40MHz system clock
		TPR = (40MHz / ((2*(6+4)) * 100kHz)) - 1 		(Convert Everything to Hz)
		TPR = 19
		
	*/
	// take care of master timer period: standard speed and TPR value

	I2C1_MTPR_R = I2C_MTPR_TPR_VALUE;


}

/*
 *	-------------------I2C0_Receive------------------
 *	Polls to receive data from specified peripheral
 *	Input: Slave address & Slave Register Address
 *	Output: Returns 8-bit data that has been received
 */
uint8_t I2C_Receive(uint8_t slave_addr, uint8_t slave_reg_addr){

	char error; //Temp Variable to hold errors
	uint8_t data;

	/* Check if I2C1 is busy: check MCS register Busy bit */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}
	/* Configure I2C0 Slave Address and Read Mode */
	// Slave Address is the 7 MSB
	// Set Data Register to slave register address
	I2C1_MSA_R = (slave_addr << 1); // write mode
	I2C1_MDR_R = slave_reg_addr;

	/* Initiate I2C by generating a START & RUN cmd:
		 Set MCS register START bit to generate and RUN bit to enable I2C Master
	*/
	I2C1_MCS_R = I2C_MCS_START | I2C_MCS_RUN;

	/* Wait until write is done: check MCS register to see is I2C is still busy */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Check for any error: read the error flag from MCS register */
	error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
	if(error){
	return 0;
	}

	/* Set I2C to Receive with Slave Address and change to Read */
	I2C1_MSA_R = (slave_addr << 1) | I2C_MSA_RS; // read mode

	/* Initiate I2C by generating a repeated START, STOP, & RUN cmd */
	I2C1_MCS_R = I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP;

	/* Wait until I2C bus is not busy: check MCS register for I2C bus busy bit */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Check for any error: read the error flag from MCS register */
	error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
	if(error){
	return 0;
	}

	data = (uint8_t)(I2C1_MDR_R & I2C_MDR_DATA_M);
	return data;

}

/*
 *	-------------------I2C0_Transmit------------------
 *	Transmit a byte of data to specified peripheral
 *	Input: Slave address, Slave Register Address, Data to Transmit
 *	Output: Any Errors if detected, otherwise 0
 */
uint8_t I2C_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t data){
	
	char error;																	//Temp Variable to hold errors
	
	/* Check if I2C0 is busy: check MCS register Busy bit */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Configure I2C Slave Address, R/W Mode, and what to transmit */
	//Slave Address is the first 7 MSB
	// Clear LSB to write
	//Transmit register addr to interact
	I2C1_MSA_R = (slave_addr << 1); // write mode
	I2C1_MDR_R = slave_reg_addr;
	/* Initiate I2C by generate a START bit and RUN cmd */
	I2C1_MCS_R = I2C_MCS_START | I2C_MCS_RUN;

	/* Wait until write has been completed */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Update Data Register with data to be transmitted */
	I2C1_MDR_R = data;
	
	/* Initiate I2C by generating a STOP & RUN cmd */
	I2C1_MCS_R = I2C_MCS_STOP | I2C_MCS_RUN;

	/* Wait until write has been completed: check MCS register Busy bit */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Wait until bus isn't busy: check MCS register for I2C bus busy bit */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Check for any error: read the error flag from MCS register */
	error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
	if(error){
		return 1;
	}
	return 0;
}

//Has Yet to be Implemented
/*
 *	----------------I2C0_Burst_Receive-----------------
 *	Polls to receive multiple bytes of data from specified
 *  peripheral by incrementing starting slave register address
 *	Input: Slave address, Slave Register Address, Data Buffer
 *	Output: None
 */
void I2C_Burst_Receive(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size){
	
}

/*
 *	----------------I2C1_Burst_Transmit-----------------
 *	Transmit multiple bytes of data to specified peripheral
 *  by incrementing starting slave address
 *	Input: Slave address, Slave Register Address, Data Buffer to transmit
 *	Output: None
 */
uint8_t I2C_Burst_Transmit(uint8_t slave_addr, uint8_t slave_reg_addr, uint8_t* data, uint32_t size){
	
	char error; //Temp Error Variable
	uint8_t* ptr = data;

	/* Asserting Param */
	if((ptr == 0) || (size == 0)){
		return 1;
	}

	/* Check if I2C1 is busy */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}


	/* Configure I2C Slave Address, R/W Mode, and what to transmit */
	//Slave Address is the first 7 MSB
	//Clear LSB to write
	//Transmit register addr to interact
	I2C1_MSA_R = (slave_addr << 1); // write mode
	I2C1_MDR_R = slave_reg_addr;

	/* Initiate I2C by generate a START bit and RUN cmd */
	I2C1_MCS_R = I2C_MCS_START | I2C_MCS_RUN;

	/* Wait until write has been completed */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Check for any error */
	error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
	if(error){
		return 1;
	}

	/* Loop to Burst Transmit what is stored in data buffer */
	while(size > 1){
		
		//Deference Pointer from data array and load into data reg. Post-Increment the pointer after
		I2C1_MDR_R = *ptr++;
		//Initiate I2C RUN CMD
		I2C1_MCS_R = I2C_MCS_RUN;
		//Wait until transmit is complete
		while(I2C1_MCS_R & I2C_MCS_BUSY) {}

		/* Check for any error */
		error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
		if(error){
			return 1;
		}
		size--;//Reduce size until 1 is left
		
	}
	
	//Deference Pointer from data array and load into data reg
	I2C1_MDR_R = *ptr;
	//Initiate I2C STOP condition and RUN CMD
	I2C1_MCS_R = I2C_MCS_STOP | I2C_MCS_RUN;

	/* Wait until write has been completed */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}

	/* Wait until bus isn't busy */
	while(I2C1_MCS_R & I2C_MCS_BUSY) {}
	
	/* Check for any error */
	error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
	if(error){
		return 1;
	}
	return 0;
}

uint8_t I2C_Burst_Transmit_NoReg(uint8_t slave_addr, uint8_t* data, uint32_t size){
    char error;
    uint8_t* ptr = data;

    if((ptr == 0) || (size == 0)){
        return 1;
    }

    while(I2C1_MCS_R & I2C_MCS_BUSY) {}

    I2C1_MSA_R = (slave_addr << 1); // write mode
    I2C1_MDR_R = *ptr++;
    I2C1_MCS_R = I2C_MCS_START | I2C_MCS_RUN;

    while(I2C1_MCS_R & I2C_MCS_BUSY) {}
    error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
    if(error){
        return 1;
    }

    while(size > 1){
        I2C1_MDR_R = *ptr++;
        I2C1_MCS_R = I2C_MCS_RUN;
        while(I2C1_MCS_R & I2C_MCS_BUSY) {}
        error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
        if(error){
            return 1;
        }
        size--;
    }

    I2C1_MDR_R = *ptr;
    I2C1_MCS_R = I2C_MCS_STOP | I2C_MCS_RUN;
    while(I2C1_MCS_R & I2C_MCS_BUSY) {}
    while(I2C1_MCS_R & I2C_MCS_BUSY) {}
    error = (I2C1_MCS_R & I2C_MCS_ERROR) ? 1 : 0;
    if(error){
        return 1;
    }
    return 0;
}

