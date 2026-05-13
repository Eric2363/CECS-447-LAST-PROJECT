// main.c
// Course number:
// Term: 
// Project number: 
// Project description:
// Team #4
// Team members:

// Header files needed for this program
// Include C library header files, microntroller header files, and 
// project module header files.
#include "/drivers/PLL.h"
#include "/drivers/UART.h"
#include "/drivers/ButtonLED.h"
#include "/drivers/wtimer.h"
#include "/drivers/I2C.h"
#include "/drivers/MPU6050.h"
#include "/drivers/LCD.h"
#include "stdio.h"


// function prototypes
void System_Init(void);
void MPU6050_Test(void);
void UART_OutSDec(int32_t n);
void MPU(void);
void UpdateLCD(void);
void UpdateTerminal(void);
void UART_OutSDec(int32_t n);
void Delay(unsigned long ms);
//global
MPU6050_ANGLE_t angle_data;
char xData[16];
char yData[16];
char zData[16];
volatile bool detectionFlag = true;
volatile bool displayFlag = true;

int main(void){	
	//init
  System_Init();
	
	//start up msg
	LCD_Print_Str((uint8_t*)"System");
	LCD_Set_Cursor(ROW2,0);
	LCD_Print_Str((uint8_t*)"Initialized!");
	DELAY_1MS(200);
	
	//100ms ticks
	uint8_t tick = 0;
	
  while(1){
	  
		
		//Every 100ms read IMU & color
		if(detectionFlag){
			//TO DO
			//ReadColor
			MPU();
		}
		
		//TO DO
		//UpdateServo
		
		//Every 1 sec do this task
		tick++;
		
		if(tick >= 10){
			tick = 0;
			if(displayFlag){
				UpdateLCD();
			}
			UpdateTerminal();
		}
		
		DELAY_1MS(100);
  }
	
}


void MPU(){
	//create struct instances
	MPU6050_ACCEL_t accel_data;
	MPU6050_GYRO_t gyro_data;
	
	
	//read raw data
	MPU6050_Get_Accel(&accel_data);
	MPU6050_Get_Gyro(&gyro_data);
	
	//process data to physical units
	MPU6050_Process_Accel(&accel_data);
	MPU6050_Process_Gyro(&gyro_data);
	
	//calculate angles
	MPU6050_Get_Angle(&accel_data, &gyro_data, &angle_data);
	
}

void UpdateLCD(){
		LCD_Clear();
		LCD_Print_Str((uint8_t*)"COLOR:GREEN");
		LCD_Set_Cursor(ROW2,0);
		
		//print x on LCD
		LCD_Print_Str((uint8_t*)"X:");
		sprintf(xData,"%0.2f",angle_data.ArX);
		LCD_Print_Str((uint8_t*)xData);
		
		//print y on LCD
		LCD_Set_Cursor(ROW2,8);
		LCD_Print_Str((uint8_t*)"Y:");
		sprintf(yData,"%0.2f",angle_data.ArY);
		LCD_Print_Str((uint8_t*)yData);
		
//		//print z on lcd
//		LCD_Set_Cursor(ROW2,8);
//		LCD_Print_Str((uint8_t*)"Z:");
//		sprintf(zData,"%0.2f",angle_data.ArZ);
//		LCD_Print_Str((uint8_t*)zData);
	
	
}
void UpdateTerminal(){
	  // Angles (convert to integers for display)
		UART_OutString((uint8_t*)"Angles: X =");
    UART_OutSDec((int32_t)angle_data.ArX);
    UART_OutString((uint8_t*)" Y=");
    UART_OutSDec((int32_t)angle_data.ArY);
    UART_OutString((uint8_t*)" z=");
    UART_OutSDec((int32_t)angle_data.ArZ);
    UART_OutString((uint8_t*)"\r\n");
	
}
void System_Init(void) {
	PLL_Init();
	WTIMER_Init();
	UART_Init(false,false);
	I2C_Init();
	MPU6050_Init();
	LCD_Init();
	LED_Init();
	BTN_Init();
}

void UART_OutSDec(int32_t n) {
    if (n < 0) {
        UART_OutChar('-');
        n = -n;
    }
    UART_OutUDec((uint32_t)n);
}

//Interrupt Handler for PortF
void GPIOPortF_Handler(void){
	//debounce
	Delay(20);
	
	// Handle  interrupt event here
	//SW1 (start/stop detection)
	if((GPIO_PORTF_DATA_R & SW1) == 0){ //Check if SW1 is pressed
		//update detectionFlag
		detectionFlag = !detectionFlag;
	}
	//SW2 display update
	else if((GPIO_PORTF_DATA_R & SW2) == 0){ //Check if SW2 is pressed
		//update display flag
		displayFlag = !displayFlag;
	}
	
	GPIO_PORTF_ICR_R = SWITCHES; //Clear interrupt flags for switch pins
}
//used for debounce
void Delay(unsigned long ms){
    volatile unsigned long time;

    while(ms){
        time = 5333;   // ~1ms at 16 MHz
        while(time){
            time--;
        }
        ms--;
    }
}

