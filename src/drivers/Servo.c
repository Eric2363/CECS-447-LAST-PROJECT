// Team #4
// Team members: Eric Santana; Dante Jimenez; Alexander Zepeda; Kour, Thaisinge


#include "Servo.h"
#include "tm4c123gh6pm.h"

/*
 *  -------------------Servo_Init------------------
 *  Basic Servo Initialization function for PWM Generation
 *  Input: None
 *  Output: None
 */
void Servo_Init(void){

    // Enable Clocks
    SYSCTL_RCGCGPIO_R |= EN_PWM0_GPIOB_CLOCK;
    SYSCTL_RCGCPWM_R  |= EN_PWM0_CLOCK;

    // Small Delay
    volatile uint32_t delay;
    delay = SYSCTL_RCGCGPIO_R;

    // Configure PWM Clock Divider
    SYSCTL_RCC_R |= EN_USE_PWM_DIV;
    SYSCTL_RCC_R &= ~CLEAR_PWM_DIV;
    SYSCTL_RCC_R |= PWM0_DIV_VALUE;

    // Configure PB7 Alternate Function
    GPIO_PORTB_AFSEL_R |= PWM0_PIN;

    // Configure PB7 as M0PWM1
    GPIO_PORTB_PCTL_R &= CLEAR_ALT_FUNCTION;
    GPIO_PORTB_PCTL_R |= PWM0_ALT_FUNCTION;

    // Enable Digital I/O
    GPIO_PORTB_DEN_R |= PWM0_PIN;

    // Disable Analog
    GPIO_PORTB_AMSEL_R &= ~PWM0_PIN;

    // Configure PWM Generator
    PWM0_0_CTL_R = PWM0_DEFAULT_CONFIG;
    PWM0_0_GENB_R = PWM0_GEN_CONFIG;

    // Set PWM Period
    PWM0_0_LOAD_R = PWM0_COUNTER;

    // Default Servo Position (Center)
    PWM0_0_CMPB_R = PWM0_COUNTER - 375;

    // Start PWM
    PWM0_0_CTL_R |= PWM0_START;

    // Enable PWM Output
    PWM0_ENABLE_R |= EN_PWM0_FUNCTION;
}

/*
 *  -------------------Drive_Servo------------------
 *  Drives the Servo Motor to a specified angle
 *  Input: Desired Angle
 *  Output: None
 */
void Drive_Servo(int16_t angle){

    uint32_t duty;

    // Clamp Angle
    if(angle < SERVO_MIN_ANGLE){
        angle = SERVO_MIN_ANGLE;
    }

    if(angle > SERVO_MAX_ANGLE){
        angle = SERVO_MAX_ANGLE;
    }

    // Convert Angle to PWM Counts
    duty = SERVO_MIN_CNT +
          ((angle - SERVO_MIN_ANGLE) *
          (SERVO_MAX_CNT - SERVO_MIN_CNT)) /
          (SERVO_MAX_ANGLE - SERVO_MIN_ANGLE);

    // Update PWM Duty Cycle
    PWM0_0_CMPB_R = PWM0_COUNTER - duty;
}