# Step 1 – System Design

## 1. Functional Requirements

List all functional requirements using IDs (RQ-##).

- RQ-01:  
- RQ-02:  
- RQ-03:  

---

## 2. Constraints

List all system constraints using IDs (CN-##).

- CN-01:  
- CN-02:  
- CN-03:  

---

## 3. System Design

### 3.1 Hardware Plan
- GPIO assignments
  - UART0
  - PA0 = UART0 RX
  - PA1 = UART0 TX
  - I2C1
  - PA6 = I2C1 SCL
  - PA7 = I2C1 SDA
  - Servo PWM
  - PB5 = PWM output to servo control line (M0PWM3, allowed)
  - Onboard inputs
  - PF4 = SW1
  - PF0 = SW2
  - Onboard LEDs
  - PF1 = Red LED
  - PF3 = Green LED
  - PF2 = Blue LED
  - WTIMER
  - WTIMER1 selected; no external GPIO required for delay mode
- Peripherals used
  - WTIMER1 for 1 ms delay generation
  - UART0 for terminal/debug output
  - I2C1 as the master bus controller
- External components
  - TCS34725 RGB color sensor (0x29)
  - MPU6050 IMU (0x68)
  - 16x2 LCD with PCF8574T I2C backpack (0x27)
  - Standard hobby servo motor
  - Two external 4.7 kOhm pull-up resistors on SDA and SCL
  - USB serial terminal on PC 

### 3.2 Software Architecture
- High-level module list
  - main.c / System Controller
  - wtimer.c / wtimer.h
  - uart0.c / uart0.h
  - i2c.c / i2c.h
  - tcs34725.c / tcs34725.h
  - mpu6050.c / mpu6050.h
  - lcd_i2c.c / lcd_i2c.h
  - servo_pwm.c / servo_pwm.h
  - app_logic.c / app_logic.h
- Responsibilities of each module
  - System Controller
    - Calls all init functions in required order
    - Runs the startup LCD sequence
    - Schedules 100 ms sampling and 1 s display/UART updates
    - Handles SW1/SW2 behavior if used in full integration
  - WTIMER module
    - Provides WTIMER_Init()
    - Provides WTIMER_Delay(ms)
    - Supplies consistent blocking delays for sensor startup, LCD timing, and unit tests
  - UART0 module
    - Handles serial initialization and formatted printing
    - Supports char, string, integer, and float output
    - Used for debugging, sensor visibility, and test logs
  - I2C module
    - Abstracts low-level bus control
    - Provides I2C_Init(), I2C_Write(), and I2C_Read()
    - Centralizes timeout/NAK handling
    - Shared by TCS34725, MPU6050, and LCD drivers
  - TCS34725 module
    - Verifies sensor ID register
    - Enables the sensor
    - Reads RGB registers
    - Returns clean 16-bit color data to application logic
  - MPU6050 module
    - Verifies WHO_AM_I
    - Wakes/configures the sensor
    - Reads accel/gyro registers
    - Supplies raw motion data for angle calculation
  - LCD module
    - Initializes LCD through PCF8574T backpack
    - Supports clear, cursor positioning, and text output
    - Displays startup name sequence and runtime color/angle output
  - Servo PWM module
    - Initializes 50 Hz PWM
    - Converts desired angle into pulse width/duty cycle
    - Updates servo position smoothly
  - Application Logic module
    - Converts RGB data to dominant color name
    - Converts IMU reading to display/control angle
    - Applies limits, filtering, and formatting before output


---

## 4. Design Justification

Explain:
- Why this design was chosen  
- Tradeoffs considered (optional alternatives)  

---

## 5. AI Verification Summary

- What AI was used for  
- What was verified  
- What was accepted/rejected  
