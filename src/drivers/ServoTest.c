/*
 * Servo_Test.c
 *
 *  Standalone module test for the Servo PWM driver.
 *  This file has its own main() so the project's main.c can be
 *  excluded from the build during servo testing.
 *
 *  HOW TO USE IN KEIL
 *  ------------------
 *  1. Right-click your existing main.c in the Project pane.
 *     Choose "Options for File" and UNCHECK "Include in Target Build".
 *  2. Add this file to your project (same group as your drivers).
 *  3. Build and flash as normal.
 *  4. Watch the onboard RGB LED and the servo for test results.
 *
 *  TEST SEQUENCE  (7 tests)
 *  ----------------------------------------------------------------
 *  T1  Register Check   Verify LOAD/CMPB/ENABLE wrote correctly
 *  T2  Center  (  0 deg)  CMPB == 4624, servo centers
 *  T3  Min     (-90 deg)  CMPB == 4749, servo hard-left
 *  T4  Max     (+90 deg)  CMPB == 4499, servo hard-right
 *  T5  Clamp low  (-120)  Must equal T3 (clamped to -90)
 *  T6  Clamp high (+120)  Must equal T4 (clamped to +90)
 *  T7  Motion sequence    Spec sweep: 0->-45->0->+45->0->-90->0->+90->0
 *
 *  LED FEEDBACK  (PF1=Red, PF2=Blue, PF3=Green)
 *  ----------------------------------------------------------------
 *  All LEDs ON  (white)   -> startup flash, board is alive
 *  GREEN                  -> test just PASSED
 *  RED                    -> test just FAILED
 *  BLUE                   -> T7 motion sequence is running
 *  All LEDs OFF           -> 0.5 s gap between tests
 *  Cycling G->B->R        -> all tests complete, idle loop
 *
 * Target:  TM4C123GH6PM
 * Author:  Jackie Huynh
 */

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Servo.h"
#include "wtimer.h"

/* ================================================================
 *  Onboard RGB LED  (Port F: PF1=Red, PF2=Blue, PF3=Green)
 * ================================================================ */
#define LED_RED     0x02U
#define LED_BLUE    0x04U
#define LED_GREEN   0x08U
#define LED_ALL     (LED_RED | LED_BLUE | LED_GREEN)

static void LED_Init(void) {
    SYSCTL_RCGCGPIO_R |= 0x20U;               /* clock to Port F          */
    volatile uint32_t d = SYSCTL_RCGCGPIO_R;  /* let clock settle         */
    (void)d;
    GPIO_PORTF_LOCK_R = 0x4C4F434BU;          /* unlock (needed for PF0)  */
    GPIO_PORTF_CR_R  |= LED_ALL;
    GPIO_PORTF_DIR_R |= LED_ALL;               /* PF1-3 as outputs         */
    GPIO_PORTF_DEN_R |= LED_ALL;               /* digital enable           */
    GPIO_PORTF_DATA_R &= ~LED_ALL;             /* start with LEDs off      */
}

static void LED_Set(uint8_t mask) {
    GPIO_PORTF_DATA_R = (GPIO_PORTF_DATA_R & ~(uint32_t)LED_ALL)
                        | ((uint32_t)mask & LED_ALL);
}

/* ================================================================
 *  Test result counters
 * ================================================================ */
static uint8_t tests_passed = 0;
static uint8_t tests_failed = 0;

/* Show GREEN (pass) or RED (fail) for 1 s, then 0.5 s gap */
static void Record_Result(uint8_t passed) {
    if (passed) {
        tests_passed++;
        LED_Set(LED_GREEN);
    } else {
        tests_failed++;
        LED_Set(LED_RED);
    }
    DELAY_1MS(1000);
    LED_Set(0);
    DELAY_1MS(500);
}

/* ================================================================
 *  T1 – Register Verification (software check, no oscilloscope)
 *  After Servo_Init():
 *    PWM0_0_LOAD_R  must equal PWM0_COUNTER       (4999)
 *    PWM0_0_CMPB_R  must equal LOAD - MIN_CNT     (4749)
 *    PWM0_ENABLE_R  bit 1 must be set
 *    PWM0_0_CTL_R   bit 0 must be set (generator running)
 * ================================================================ */
static void Test_RegisterCheck(void) {
    uint8_t ok = 1u;

    if (PWM0_0_LOAD_R != (uint32_t)PWM0_COUNTER)
        { ok = 0u; }

    if (PWM0_0_CMPB_R != (uint32_t)(PWM0_COUNTER - SERVO_MIN_CNT))
        { ok = 0u; }

    if ((PWM0_ENABLE_R & 0x02U) == 0u)
        { ok = 0u; }

    if ((PWM0_0_CTL_R & 0x01U) == 0u)
        { ok = 0u; }

    Record_Result(ok);
}

/* ================================================================
 *  T2 – Center Position (0 deg -> 1.5 ms)
 *  Expected CMPB = 4999 - 375 = 4624
 * ================================================================ */
static void Test_Center(void) {
    Drive_Servo(0);
    DELAY_1MS(500);
    uint8_t ok = (PWM0_0_CMPB_R == (uint32_t)(PWM0_COUNTER - 375u));
    Record_Result(ok);
}

/* ================================================================
 *  T3 – Minimum Angle (-90 deg -> 1.0 ms)
 *  Expected CMPB = 4999 - 250 = 4749
 * ================================================================ */
static void Test_MinAngle(void) {
    Drive_Servo(-90);
    DELAY_1MS(500);
    uint8_t ok = (PWM0_0_CMPB_R == (uint32_t)(PWM0_COUNTER - SERVO_MIN_CNT));
    Record_Result(ok);
}

/* ================================================================
 *  T4 – Maximum Angle (+90 deg -> 2.0 ms)
 *  Expected CMPB = 4999 - 500 = 4499
 * ================================================================ */
static void Test_MaxAngle(void) {
    Drive_Servo(90);
    DELAY_1MS(500);
    uint8_t ok = (PWM0_0_CMPB_R == (uint32_t)(PWM0_COUNTER - SERVO_MAX_CNT));
    Record_Result(ok);
}

/* ================================================================
 *  T5 – Clamp Below Minimum (-120 deg, out of range)
 *  Driver must clamp to -90; CMPB must equal T3's value.
 * ================================================================ */
static void Test_ClampLow(void) {
    Drive_Servo(-120);
    DELAY_1MS(500);
    uint8_t ok = (PWM0_0_CMPB_R == (uint32_t)(PWM0_COUNTER - SERVO_MIN_CNT));
    Record_Result(ok);
}

/* ================================================================
 *  T6 – Clamp Above Maximum (+120 deg, out of range)
 *  Driver must clamp to +90; CMPB must equal T4's value.
 * ================================================================ */
static void Test_ClampHigh(void) {
    Drive_Servo(120);
    DELAY_1MS(500);
    uint8_t ok = (PWM0_0_CMPB_R == (uint32_t)(PWM0_COUNTER - SERVO_MAX_CNT));
    Record_Result(ok);
}

/* ================================================================
 *  T7 – Full Motion Sequence (project spec section 5.7)
 *  0->-45->0->+45->0->-90->0->+90->0, 1 s per position.
 *  LED is BLUE during sweep; result is always marked PASS
 *  (visual / oscilloscope verification expected here).
 * ================================================================ */
static void Test_MotionSequence(void) {
    LED_Set(LED_BLUE);
    Servo_UnitTest();
    LED_Set(0);
    DELAY_1MS(500);
    Record_Result(1u);
}

/* ================================================================
 *  Idle loop: cycle GREEN->BLUE->RED at 1 Hz to signal completion
 * ================================================================ */
static void Done_Cycle(void) {
    const uint8_t colors[3] = { LED_GREEN, LED_BLUE, LED_RED };
    uint8_t i = 0u;
    while (1) {
        LED_Set(colors[i % 3u]);
        DELAY_1MS(1000);
        i++;
    }
}

/* ================================================================
 *  main
 *  Comment out (exclude from build) your project's main.c,
 *  then build and flash this file instead.
 * ================================================================ */
int main(void) {

    /* Init hardware */
    WTIMER_Init();    /* must be first — all delays depend on it */
    LED_Init();
    Servo_Init();

    /* Startup flash: all LEDs on for 0.5 s -> confirm board alive */
    LED_Set(LED_ALL);
    DELAY_1MS(500);
    LED_Set(0);
    DELAY_1MS(500);

    /* Run all 7 tests */
    Test_RegisterCheck();    /* T1 */
    Test_Center();           /* T2 */
    Test_MinAngle();         /* T3 */
    Test_MaxAngle();         /* T4 */
    Test_ClampLow();         /* T5 */
    Test_ClampHigh();        /* T6 */
    Test_MotionSequence();   /* T7 */

    /* Spin forever showing completion pattern */
    Done_Cycle();

    return 0;
}