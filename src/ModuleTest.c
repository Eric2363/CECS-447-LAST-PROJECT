//// ModuleTest.c
//// Course number:
//// Term: 
//// Project number: 
//// Module description: 
//// A brief summary on modules tested in this module test file,
//// including module list, responsibility and team member assignment
//// Team #:
//// Team members:


//// Header files needed for this program
//// Include C library header files, microntroller header files, and 
//// project module header files. 
//// Example:
//// #include module1_driver.h
//#include <stdint.h>
//#include <stdbool.h>
//#include <stdio.h>
//#include "/drivers/PLL.h"
//#include "/drivers/UART.h"
//#include "/drivers/wtimer.h"
//#include "/drivers/ButtonLED.h"
//#include "/drivers/Latch.h"
//#include "/drivers/I2C.h"
//#include "/drivers/MPU6050.h"



//// preprocessor directives for module name
//// Example:
////#define MODULE_1_TEST
////#define MODULE_3_TEST
////#define MODULE_6_TEST

//// functions prototypes
//void System_Init(void);

//// Module test function prototypes & variables
//#if defined(MODULE_1_TEST)
//void Module_1_Test(void);
//bool runTest = true;
//#endif

//#if defined(MODULE_3_TEST)
//void Module_3_Test(void);
//void Delay(unsigned long ms);
//#endif

//#if defined(MODULE_6_TEST)
//void Module_6_Test(void);
//void UART_OutSDec(int32_t n);
//#endif

//int main(void){
//  System_Init();
//	
//  while(1){
//    // Call individual module test functions here
//	// Example:
//	#if defined(MODULE_1_TEST)
//	Module_1_Test();
//		
//	#endif

//	#if defined(MODULE_3_TEST)
//	Module_3_Test();
//	OutCRLF();
//  	UART_OutString((uint8_t *)"--Press any key to restart test--\r\n");
//  	OutCRLF();
//  	UART_InChar(); // Wait for user input before ending test
//	#endif
//		
//	#if defined(MODULE_6_TEST)
//		Module_6_Test();
//		DELAY_1MS(100);
//		
//	#endif
//  }
//}

//void System_Init(void){
//  // Example:
//  #if defined(MODULE_1_TEST)
//  LED_Init();
//	BTN_Init();
//	WTIMER_Init();
//	Latch_Init();
//  #endif	

//  #if defined(MODULE_3_TEST)
//  PLL_Init(); // Initialize PLL @ 50 MHz
//  UART_Init(false,false); // Initialize UART without interrupts for testing
//  #endif	
//	
//	#if defined (MODULE_6_TEST)
//	PLL_Init();
//	UART_Init(false,false);
//	I2C_Init();
//	WTIMER_Init();
//	MPU6050_Init();
//	#endif
//	
//}

//// Module test function definitions
//#if defined(MODULE_1_TEST)
//void Module_1_Test(void){
//	if(runTest){
//		GPIO_PORTF_DATA_R |= RED;
//		DELAY_1MS(500);
//		GPIO_PORTF_DATA_R &=~RED;
//		DELAY_1MS(500);
//		GPIO_PORTF_DATA_R |= GREEN;
//		DELAY_1MS(500);
//		GPIO_PORTF_DATA_R &=~GREEN;
//		DELAY_1MS(500);
//		GPIO_PORTF_DATA_R |=BLUE;
//		DELAY_1MS(500);
//		GPIO_PORTF_DATA_R &=~BLUE;
//		runTest = false;
//	}
//	GPIO_PORTF_DATA_R |=RED;
//	GPIO_PORTE_DATA_R |=0x01;
//	DELAY_1MS(500);
//	GPIO_PORTF_DATA_R &=~RED;
//	GPIO_PORTE_DATA_R &=~0x01;
//	DELAY_1MS(500);
//	
//	
//}
//#endif

//#if defined(MODULE_3_TEST)
//void Module_3_Test(void){
//	char buffer[80];
//	int num1 = 12; // for testing int
//	float num2 = 3.14; // for testing float
//	
//	// Testing basic string
//	UART_OutString((uint8_t *)"Hello World");
//    OutCRLF();
//	
//	// Sending a single character
//	UART_OutString((uint8_t *)"Single char test: ");
//  	UART_OutChar('A');
//  	OutCRLF();
//	
//	// Sending an integer with sprintf
//	sprintf(buffer, "Integer test: %d", num1);
//  	UART_OutString((uint8_t *)buffer);
//  	OutCRLF();
//	
//	// Sending a float with sprintf
//	sprintf(buffer, "Float test: %.2f", num2);
//  	UART_OutString((uint8_t *)buffer);
//  	OutCRLF();
//	
//	// Testing recieving and echoing one character
//	UART_OutString((uint8_t *)"Type a character: ");
//  	char c = UART_InChar();
//  	UART_OutString((uint8_t *)"\r\nThe character is: ");
//  	UART_OutChar(c); // echo
//  	OutCRLF();
//	
//	Delay(1000);
//}
//#endif

//#if defined(MODULE_6_TEST)
//	void Module_6_Test(){
//		// Create struct instances
//    MPU6050_ACCEL_t accel_data;
//    MPU6050_GYRO_t gyro_data;
//    MPU6050_ANGLE_t angle_data;
//    
//    // Read raw accelerometer data
//    MPU6050_Get_Accel(&accel_data);
//    
//    // Read raw gyroscope data
//    MPU6050_Get_Gyro(&gyro_data);
//    
//    // Process accelerometer data to physical units
//    MPU6050_Process_Accel(&accel_data);
//    
//    // Process gyroscope data to physical units
//    MPU6050_Process_Gyro(&gyro_data);
//    
//    // Calculate angles
//    MPU6050_Get_Angle(&accel_data, &gyro_data, &angle_data);
//    
//    // Print results
//    UART_OutString((uint8_t*)"\r\n=== MPU6050 Test ===\r\n");
//    
//    // Raw accelerometer data
//    UART_OutString((uint8_t*)"Accel RAW - X: ");
//    UART_OutSDec(accel_data.Ax_RAW);
//    UART_OutString((uint8_t*)" Y: ");
//    UART_OutSDec(accel_data.Ay_RAW);
//    UART_OutString((uint8_t*)" Z: ");
//    UART_OutSDec(accel_data.Az_RAW);
//    UART_OutString((uint8_t*)"\r\n");
//    
//    // Processed accelerometer data (convert to integers for display)
//    UART_OutString((uint8_t*)"Accel Processed - X: ");
//    UART_OutSDec((int32_t)(accel_data.Ax * 100));
//    UART_OutString((uint8_t*)" Y: ");
//    UART_OutSDec((int32_t)(accel_data.Ay * 100));
//    UART_OutString((uint8_t*)" Z: ");
//    UART_OutSDec((int32_t)(accel_data.Az * 100));
//    UART_OutString((uint8_t*)"\r\n");
//    
//    // Raw gyroscope data
//    UART_OutString((uint8_t*)"Gyro RAW - X: ");
//    UART_OutSDec(gyro_data.Gx_RAW);
//    UART_OutString((uint8_t*)" Y: ");
//    UART_OutSDec(gyro_data.Gy_RAW);
//    UART_OutString((uint8_t*)" Z: ");
//    UART_OutSDec(gyro_data.Gz_RAW);
//    UART_OutString((uint8_t*)"\r\n");
//    
//    // Processed gyroscope data (convert to integers for display)
//    UART_OutString((uint8_t*)"Gyro Processed - X: ");
//    UART_OutSDec((int32_t)(gyro_data.Gx * 10));
//    UART_OutString((uint8_t*)" Y: ");
//    UART_OutSDec((int32_t)(gyro_data.Gy * 10));
//    UART_OutString((uint8_t*)" Z: ");
//    UART_OutSDec((int32_t)(gyro_data.Gz * 10));
//    UART_OutString((uint8_t*)"\r\n");
//    
//    // Angles (convert to integers for display)
//    UART_OutString((uint8_t*)"Angles - Pitch: ");
//    UART_OutSDec((int32_t)angle_data.ArX);
//    UART_OutString((uint8_t*)" Roll: ");
//    UART_OutSDec((int32_t)angle_data.ArY);
//    UART_OutString((uint8_t*)" Yaw: ");
//    UART_OutSDec((int32_t)angle_data.ArZ);
//    UART_OutString((uint8_t*)"\r\n");

//	}
//#endif
//// Busy-wait delay for 50 MHz system clock
// void Delay(unsigned long ms){
//     volatile unsigned long time;
//      
//     while(ms){
//         time = 16667;   // 1ms at 50 MHz
//         while(time){
//             time--;
//         }
//         ms--;
//     }
//  }

//	void UART_OutSDec(int32_t n) {
//    if (n < 0) {
//        UART_OutChar('-');
//        n = -n;
//    }
//    UART_OutUDec((uint32_t)n);
//}