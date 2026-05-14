// Team #4
// Team members: Eric Santana; Dante Jimenez; Alexander Zepeda; Kour, Thaisinge


#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
#include "wtimer.h"

/*
 * USE HARDWARE PWM MODULE 0
 * GENERATOR 0
 * CHANNEL 1
 * PB7 -> M0PWM1
 */

/* List of Fill In Macros */

// Enable GPIOB Clock
#define EN_PWM0_GPIOB_CLOCK     (0x02)

// PB7
#define PWM0_PIN                (0x80)

// Clear PB7 PCTL bits
#define CLEAR_ALT_FUNCTION      (0x0FFFFFFF)

// Set PB7 as M0PWM1
#define PWM0_ALT_FUNCTION       (0x40000000)

// Enable PWM0 module clock
#define EN_PWM0_CLOCK           (0x01)

// Enable PWM divider
#define EN_USE_PWM_DIV          (0x00100000)

// Clear PWM divider bits
#define CLEAR_PWM_DIV           (0x000E0000)

// PWM Divider = /64
#define PWM0_DIV_VALUE          (0x000E0000)

// Disable PWM during setup
#define PWM0_DEFAULT_CONFIG     (0x00000000)

// PWM Generator B actions
#define PWM0_GEN_CONFIG         (0x0000080C)

// 20ms Period
#define PWM0_COUNTER            (5000 - 1)

// Start PWM Counter
#define PWM0_START              (0x01)

// Enable PWM Output 1
#define EN_PWM0_FUNCTION        (0x02)

/* 0.5ms (2.5%) - 2.5ms (12.5%) Duty Cycle */
#define SERVO_MIN_CNT           (125)
#define SERVO_MAX_CNT           (625)

/* Max Range of Either -90 to 90 or 0 to 180 */
#define SERVO_MIN_ANGLE         (-90)
#define SERVO_MAX_ANGLE         (90)

/*
 *  -------------------Servo_Init------------------
 *  Basic Servo Initialization function for PWM Generation
 *  Input: None
 *  Output: None
 */
void Servo_Init(void);

/*
 *  -------------------Drive_Servo------------------
 *  Drives the Servo Motor to a specified angle
 *  Input: Desired Angle
 *  Output: None
 */
void Drive_Servo(int16_t angle);

#endif