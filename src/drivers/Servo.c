/*
 * Servo.c
 *
 *  Full implementation of PWM-based servo motor control.
 *  Target:   TM4C123GH6PM (Tiva C LaunchPad)
 *  Servo:    Tower Pro SG90 Micro Servo 9g
 *  PWM Out:  M0PWM1 (Module 0, Generator 0, Output B) on PB7
 *
 *  PWM Clock Math
 *  --------------
 *  System clock  : 16 MHz  (default, no PLL)
 *  RCC Divider   : /64  ->  PWM clock = 250 kHz
 *  Period (50 Hz): 5000 ticks  ->  LOAD register = 4999
 *
 *  Pulse-width mapping (count-down mode, high-time = LOAD - CMPB):
 *    Angle    Pulse    Ticks    CMPB (= LOAD - ticks)
 *    -90 deg  1.0 ms   250      4749
 *      0 deg  1.5 ms   375      4624
 *    +90 deg  2.0 ms   500      4499
 *
 * Created on: June 11th, 2023
 *     Author: Jackie Huynh
 */

/* NOTE: tm4c123gh6pm.h defines every hardware register used below.
 *       It must be included here directly (not just through Servo.h)
 *       because Servo.h intentionally does not pull in the device header. */
#include "tm4c123gh6pm.h"
#include "Servo.h"
#include "wtimer.h"

/* ================================================================
 *  Servo_Init
 *  Configures PWM0, Generator 0, Output B (M0PWM1) on PB7.
 *
 *  Bringup order (TM4C datasheet section 20.4):
 *    1. Gate clocks to GPIOB and PWM0.
 *    2. Set PWM clock divider in SYSCTL_RCC_R (/64 -> 250 kHz).
 *    3. Mux PB7 to alternate function 4 (M0PWM1).
 *    4. Disable Generator 0, program GENB, LOAD, and CMPB.
 *    5. Enable generator, then enable output pin.
 * ================================================================ */
void Servo_Init(void) {

    /* ----------------------------------------------------------
     * 1. Enable peripheral clocks
     * ---------------------------------------------------------- */
    SYSCTL_RCGCGPIO_R |= EN_PWM0_GPIOB_CLOCK;   /* clock to GPIO Port B */
    SYSCTL_RCGCPWM_R  |= EN_PWM0_CLOCK;          /* clock to PWM Module 0 */

    /* ----------------------------------------------------------
     * 2. Configure PWM clock divider: 16 MHz / 64 = 250 kHz
     *    Read-modify-write preserves all other RCC fields.
     * ---------------------------------------------------------- */
    SYSCTL_RCC_R |=  EN_USE_PWM_DIV;    /* enable the divider          */
    SYSCTL_RCC_R &= ~CLEAR_PWM_DIV;     /* clear PWMDIV field          */
    SYSCTL_RCC_R |=  PWM0_DIV_VALUE;    /* set /64 (0b110)             */

    /* ----------------------------------------------------------
     * 3. Wait for GPIO clock to settle (>= 3 bus cycles)
     * ---------------------------------------------------------- */
    volatile uint32_t delay = SYSCTL_RCGCGPIO_R;
    (void)delay;

    /* ----------------------------------------------------------
     * 4. Configure PB7 as M0PWM1 (Alternate Function 4)
     * ---------------------------------------------------------- */
    GPIO_PORTB_AFSEL_R |= PWM0_PIN;              /* enable alt func on PB7  */
    GPIO_PORTB_PCTL_R  &= ~CLEAR_ALT_FUNCTION;   /* clear PB7 mux field     */
    GPIO_PORTB_PCTL_R  |=  PWM0_ALT_FUNCTION;    /* set AF4 = M0PWM1        */
    GPIO_PORTB_DEN_R   |= PWM0_PIN;              /* digital enable          */
    GPIO_PORTB_DIR_R   |= PWM0_PIN;              /* set as output           */

    /* ----------------------------------------------------------
     * 5. Program Generator 0
     *    - Disable generator first (required before changing GENB/LOAD)
     *    - GENB = 0x80C: HIGH at LOAD, LOW at CMPB decrement
     *    - LOAD = 4999  (20 ms period at 250 kHz)
     *    - CMPB parked at minimum pulse (-90 deg) on startup
     * ---------------------------------------------------------- */
    PWM0_0_CTL_R  = PWM0_DEFAULT_CONFIG;             /* disable generator     */
    PWM0_0_GENB_R = PWM0_GEN_CONFIG;                 /* output B action       */
    PWM0_0_LOAD_R = PWM0_COUNTER;                    /* 20 ms period          */
    PWM0_0_CMPB_R = PWM0_COUNTER - SERVO_MIN_CNT;   /* park at -90 deg       */

    /* ----------------------------------------------------------
     * 6. Start generator, then enable output to pin
     *    (enable output AFTER generator starts to avoid glitch)
     * ---------------------------------------------------------- */
    PWM0_0_CTL_R   = PWM0_START;           /* run generator               */
    PWM0_ENABLE_R |= EN_PWM0_FUNCTION;     /* enable M0PWM1 output on PB7 */
}

/* ================================================================
 *  Drive_Servo
 *  Maps angle [-90, +90] degrees to a PWM pulse width and updates
 *  the CMPB register immediately.
 *
 *  Linear interpolation:
 *    pulse_ticks = MIN_CNT + (angle - MIN_ANGLE)
 *                            * (MAX_CNT - MIN_CNT)
 *                            / (MAX_ANGLE - MIN_ANGLE)
 *
 *  Then:  CMPB = LOAD - pulse_ticks
 *  (because high-time = LOAD - CMPB in count-down mode)
 *
 *  Input : angle - target position in degrees, clamped to [-90, +90]
 *  Output: none (CMPB register updated immediately)
 * ================================================================ */
void Drive_Servo(int16_t angle) {

    /* Clamp to valid mechanical range */
    if (angle < SERVO_MIN_ANGLE) { angle = (int16_t)SERVO_MIN_ANGLE; }
    if (angle > SERVO_MAX_ANGLE) { angle = (int16_t)SERVO_MAX_ANGLE; }

    /* Map angle to pulse tick count.
     * int32_t prevents overflow: max product = 180 * 250 = 45000 */
    int32_t pulse_ticks =
        (int32_t)SERVO_MIN_CNT
        + ( (int32_t)(angle - SERVO_MIN_ANGLE)
            * (int32_t)(SERVO_MAX_CNT - SERVO_MIN_CNT) )
        / (int32_t)(SERVO_MAX_ANGLE - SERVO_MIN_ANGLE);

    /* Update compare register */
    PWM0_0_CMPB_R = (uint32_t)((int32_t)PWM0_COUNTER - pulse_ticks);
}

/* ================================================================
 *  Servo_UnitTest
 *  Project spec §5.7 motion sequence, 1 s between positions:
 *    0 -> -45 -> 0 -> +45 -> 0 -> -90 -> 0 -> +90 -> 0
 * ================================================================ */
void Servo_UnitTest(void) {
    const int16_t seq[] = { 0, -45, 0, 45, 0, -90, 0, 90, 0 };
    uint8_t i;
    for (i = 0; i < 9; i++) {
        Drive_Servo(seq[i]);
        DELAY_1MS(1000);
    }
}