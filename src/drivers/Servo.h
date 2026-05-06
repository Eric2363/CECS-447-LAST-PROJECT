/*
 * Servo.h
 *
 *  Provides functions to interact with a standard angular Servo Motor.
 *  Target:      TM4C123GH6PM (Tiva C LaunchPad)
 *  PWM Output:  M0PWM1 (Module 0, Generator 0, Output B) on PB7
 *  Frequency:   50 Hz (20 ms period)
 *  Pulse Range: 1.0 ms (-90 deg) to 2.0 ms (+90 deg)
 *  Servo:       Tower Pro SG90 Micro Servo 9g
 *
 *  NOTE: The starter comment referenced PB6/M0PWM0, but M0PWM0 is
 *        explicitly prohibited by the project spec.  PB7/M0PWM1 is
 *        used instead (same generator, output B instead of A).
 *
 * Created on: June 11th, 2023
 *     Author: Jackie Huynh
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

/* =========================================================
 *  Hardware Assignment
 *  Module : PWM0, Generator 0, Output B  -> M0PWM1
 *  Pin    : PB7 (Alternate Function 4)
 * ========================================================= */

/* --- GPIO & peripheral clock enables --- */
#define EN_PWM0_GPIOB_CLOCK     0x00000002U   /* RCGCGPIO bit 1  -> Port B   */
#define PWM0_PIN                0x80U          /* PB7 bit mask                */
#define EN_PWM0_CLOCK           0x00000001U   /* RCGCPWM  bit 0  -> PWM0     */

/* --- GPIO pin-mux (PCTL register) --- */
#define CLEAR_ALT_FUNCTION      0xF0000000U   /* clear PB7 mux field bits 31:28 */
#define PWM0_ALT_FUNCTION       0x40000000U   /* AF4 = M0PWM1, bits 31:28       */

/* --- PWM clock divider (SYSCTL_RCC_R) ---
 *  System clock 16 MHz / 64 = 250 kHz PWM clock
 *  USEPWMDIV = bit 20,  PWMDIV field = bits 19:17  (0b110 = /64) */
#define EN_USE_PWM_DIV          0x00100000U   /* bit 20                      */
#define CLEAR_PWM_DIV           0x000E0000U   /* bits 19:17 mask             */
#define PWM0_DIV_VALUE          0x000C0000U   /* 0b110 << 17  -> divide /64  */

/* --- PWM Generator 0 control ---
 *  PWM0_DEFAULT_CONFIG : written first to disable gen before programming
 *  PWM0_START          : written last to start the generator              */
#define PWM0_DEFAULT_CONFIG     0x00000000U
#define PWM0_START              0x00000001U

/* PWM0_0_GENB_R value for Output B (M0PWM1):
 *   bits  3:2  ACTLOAD  = 0b11 -> drive HIGH when counter == LOAD
 *   bits 11:10 ACTCMPBD = 0b10 -> drive LOW  when counter decrements past CMPB
 *   Pulse high-time = (LOAD - CMPB) ticks                                     */
#define PWM0_GEN_CONFIG         0x0000080CU

/* LOAD = (PWM_clock / frequency) - 1 = (250000 / 50) - 1 = 4999 */
#define PWM0_COUNTER            4999U

/* PWM0_ENABLE_R bit 1 -> enable M0PWM1 output to pin */
#define EN_PWM0_FUNCTION        0x00000002U

/* =========================================================
 *  Servo Pulse-Width Tick Counts  (250 kHz PWM clock)
 *    1.0 ms = 250 ticks  -> -90 degrees
 *    1.5 ms = 375 ticks  ->   0 degrees
 *    2.0 ms = 500 ticks  -> +90 degrees
 * ========================================================= */
#define SERVO_MIN_CNT           250U
#define SERVO_MAX_CNT           500U

/* =========================================================
 *  Servo Angle Range (degrees)
 * ========================================================= */
#define SERVO_MIN_ANGLE         (-90)
#define SERVO_MAX_ANGLE         (90)

/* =========================================================
 *  Public API
 * ========================================================= */

/*
 * Servo_Init
 * Initialises PWM0 Gen0 Output B (M0PWM1) on PB7 for 50 Hz.
 * Must be called once before Drive_Servo().
 */
void Servo_Init(void);

/*
 * Drive_Servo
 * Moves servo to requested angle in degrees [-90, +90].
 * Out-of-range values are silently clamped.
 */
void Drive_Servo(int16_t angle);

/*
 * Servo_UnitTest
 * Spec-required motion sequence with 1 s between positions:
 *   0 -> -45 -> 0 -> +45 -> 0 -> -90 -> 0 -> +90 -> 0
 * Requires wtimer to be initialised first.
 */
void Servo_UnitTest(void);

#endif /* SERVO_H_ */