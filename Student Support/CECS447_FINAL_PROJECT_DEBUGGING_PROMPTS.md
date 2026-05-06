# AI Debugging Templates for CECS 447 Final Project: I2C Bus Communication

| Property | Details |
|----------|---------|
| **Course** | CECS 447 (Senior Level Embedded Systems) |
| **Project** | I2C Bus Communication System with Color Sensing & Servo Control |
| **Platform** | TI LaunchPad (TM4C123) with TCS34725 Color Sensor, MPU6050 IMU, 16x2 LCD (I2C), Servo Motor |
| **Workflow** | 3-Step Embedded Systems Design (Requirements & System Design → Module Design & Implementation → Feature Implementation, Integration & Final Submission) |
| **Instructor** | Dr. Min He |
| **Copyright** | © 2026, Computer Engineering Department, California State University, Long Beach |

These templates help you systematically debug common problems in this I2C project. Use them when you're stuck, before you randomly change code.

---

## Project Description

In this project, you'll use **I2C bus communication** to configure and retrieve data from three external I2C devices:

- **TCS34725 RGB Color Sensor** — Detect colors from objects  
- **MPU6050 6-DOF IMU** — Measure tilt and acceleration  
- **16x2 LCD Display** — Show color and angle information  

### Learning Objectives

You will gain practical experience with:

- **I2C Protocol:** Master serial communication for embedded systems
- **Multi-device Integration:** Manage multiple I2C slave devices on a single bus
- **Sensor Data Processing:** Read, interpret, and convert raw sensor data
- **Servo Control:** Generate PWM signals for motor positioning
- **System Integration:** Combine independent modules into a working system

### Project Goals

Through this final project, you will:

1. **Detect colors** using TCS34725 RGB sensor
2. **Measure angles** using MPU6050 IMU (tilt/acceleration)
3. **Control servo position** based on IMU angle
4. **Display sensor data** on LCD and serial terminal
5. **Implement robust error handling** for multi-device systems

---

## Required Components

- TIVA TM4C LaunchPad  
- TCS34725 RGB Color Sensor  
- MPU6050 6-DOF IMU (Inertial Measurement Unit)  
- Angular Servo Motor  
- 16x2 LCD with I2C interface  
- Two 4.7kΩ resistors (for I2C pull-ups)  
- Serial terminal application (Putty, Tera Term, YAT, etc.)

---

## Project Requirements

### Code Implementation Notes

The starter code includes placeholders you must complete:

- **`CONSTANT_FILL`** → Fill in correct constant values (addresses, registers, dividers)
- **`CODE_FILL`** → Implement required logic (initialization, read/write sequences)

All functions must be fully implemented before proceeding to integration. No partial implementations allowed.

---

## System Peripherals & Configuration

- **UART0** → Communication with PC (57600 baud)
- **I2C0** → Standard Mode (100 kHz or Fast Mode 400 kHz) for all sensor communication
- **PWM** → M0PWM0 on PB6 (servo motor control via angular servo)
- **Timer** → WTIMER0 (1 ms delay generation)

---

## Important Constraints to Remember

- 🔴 **I2C Bus:** Requires 4.7kΩ pull-up resistors on SDA and SCL to 3.3V
- 🔴 **Slave Addresses:** 
  - TCS34725 Color Sensor = 0x29
  - MPU6050 IMU = 0x68
  - 16x2 LCD = 0x27 (verify for your hardware!)
- 🔴 **I2C Clock:** Standard Mode (100 kHz) or Fast Mode (400 kHz) — must be compatible with all devices
- 🔴 **Baud Rate:** UART0 @ 57600 baud (verify register configuration)
- 🔴 **Sensor Detection:**
  - TCS34725 ID register (0x12) should read 0x44
  - MPU6050 WHO_AM_I register (0x75) should read 0x68
- 🔴 **PWM Servo:** M0PWM0 on PB6 for servo control (50 Hz frequency, 1-2 ms pulse width)
- 🔴 **Servo Motion Sequence:** 0° → -45° → 0° → +45° → 0° → -90° → 0° → +90° → 0° (1-second delays between positions)
- 🔴 **LCD Display:** 16x2 display via I2C backpack (PCF8574T typical), shows:
  - Row 1: Color name (e.g., "Color: RED")
  - Row 2: Angle/data (e.g., "Angle: 45°")
- 🔴 **WTIMER0:** Wide Timer for 1 ms delay function
- 🔴 **Red LED Blink Test:** In WTIMER0 mode, red LED should blink at 2 Hz
- 🔴 **Switch Controls:**
  - SW1: Toggle between UART test mode and WTIMER0 mode
  - SW2 (in timer mode): Cycle through LEDs (Red → Green → Blue)

---

## Part 1: Module Testing Order (Unit Testing)

The project requires testing modules in this specific order before full integration. Each module must pass its unit test before moving to the next:

### Unit Test Sequence

1. **WTIMER0 (Wide Timer)** 
   - Test: 1 ms delay function accuracy
   - Test: Red LED blinks at 2 Hz (toggle every 500ms)
   - Test: SW1 toggles between UART test mode and WTIMER0 mode
   - Test: SW2 cycles through onboard LEDs (Red → Green → Blue)

2. **UART0 (Serial Communication)**
   - Test: Send strings to PC at 57600 baud
   - Test: Send integer values using sprintf()
   - Test: Send floating-point values using sprintf()
   - Test: Update output every 1 second

3. **TCS34725 Color Sensor**
   - Test: Detect sensor via ID register (register 0x12 = 0x44)
   - Test: Configure sensor and enable
   - Test: Read RGB values and print to UART
   - Test: Verify values change with different colored objects

4. **MPU6050 IMU**
   - Test: Detect sensor via WHO_AM_I register (register 0x75 = 0x68)
   - Test: Configure sensor and enable
   - Test: Read acceleration (X, Y, Z axes)
   - Test: Read gyroscope (X, Y, Z axes)
   - Test: Output data to serial terminal

5. **16x2 LCD Display**
   - Test: Display full name (First name → wait 1 sec → Last name → wait 1 sec → clear → repeat)
   - Test: Verify text alignment (Row 1 vs Row 2)
   - Test: Verify display updates without corruption

6. **Servo Motor**
   - Test: Move through complete motion sequence: 0° → -45° → 0° → +45° → 0° → -90° → 0° → +90° → 0°
   - Test: 1-second delay between each position
   - Test: Smooth movement without jitter

7. **Full System Integration**
   - Test: All modules working together
   - Test: SW1 starts detection
   - Test: SW2 updates display
   - Test: Servo responds to IMU tilt
   - Test: LCD shows color name and angle
   - Test: UART shows continuous color and angle updates

---

## Part 2: Full System Behavior & Integration

**System Overview:**

The complete I2C bus system integrates all hardware and software modules into a coordinated application:

- **Color Detection:** RGB paper attached to servo motor
- **Color Sensor:** TCS34725 reads current paper color
- **Motion Control:** MPU6050 IMU controls servo movement based on tilt/acceleration
- **Display:** LCD displays detected color name and current angle
- **Data Logging:** UART continuously outputs all sensor data to PC terminal
- **Status Indication:** Onboard LEDs show color detection status

**Hardware Integration:**

- RGB paper sample mounted on servo arm
- Color sensor pointed at the paper
- IMU measures servo arm tilt and acceleration
- Servo motor controlled by PWM signal (M0PWM0)
- All I2C devices connected on common I2C0 bus with pull-up resistors
- LCD backpack provides I2C-to-parallel conversion for display

**Controls & User Interaction:**

- **SW1** → Start color detection (initiate sensing cycle)
- **SW2** → Update display (manually refresh or cycle display information)

**System Outputs:**

- **LCD (16x2 Display):**
  - Row 1: Color name (e.g., "Color: RED", "Color: GREEN", "Color: BLUE")
  - Row 2: Angle value (e.g., "Angle: 45°") or acceleration reading
  - Display updates every 1 second or on SW2 press

- **UART Terminal (57600 baud):**
  - Continuous output every 1 second
  - Format: `Color: R=###, G=###, B=### | Angle: X=##°, Y=##°, Z=##°`
  - Useful for debugging and data logging

- **Servo Motor Movement:**
  - Responds to IMU tilt angle
  - Maps: IMU angle → PWM duty cycle → servo position
  - Smooth continuous movement based on sensor input

- **Onboard LEDs:**
  - Red LED: Lights when red color detected
  - Green LED: Lights when green color detected
  - Blue LED: Lights when blue color detected
  - Status indicator for system state

**System Data Flow:**

```
1. Startup:
   - Initialize all peripherals (UART0, I2C0, PWM, WTIMER0)
   - Detect all sensors (verify ID/WHO_AM_I registers)
   - Display ready message on LCD

2. Continuous Operation:
   - Timer interrupt fires (10 Hz or 100 Hz)
   - Read color sensor (TCS34725) → get RGB values
   - Read IMU (MPU6050) → get tilt angle
   - Calculate matching color (Red/Green/Blue)
   - Light corresponding LED
   - Move servo to commanded angle (via PWM)

3. Display Update (every 1 second):
   - Format sensor data for LCD and UART
   - Send to LCD via I2C
   - Send to UART terminal
   
4. User Input:
   - SW1 press: Enter detection mode or reset
   - SW2 press: Manually update display or cycle output

5. Shutdown:
   - Servo to center (0°)
   - Turn off all LEDs
   - Display "System Off" on LCD
```

**Integration Sequence (What Happens When System Runs):**

1. Power on → All modules initialize
2. LEDs blink to show ready state
3. LCD shows startup message (name or "I2C System Ready")
4. User presses SW1 → Color detection begins
5. Color sensor samples RGB continuously
6. IMU reads tilt angle continuously
7. Servo smoothly moves to match IMU angle
8. LCD updates every 1 second with latest color and angle
9. UART outputs data every 1 second to PC terminal
10. Press SW2 to manually update display or trigger new detection
11. System repeats steps 5-10 until power off

---

## Template 1: I2C Communication Diagnosis & Root Cause Analysis

**When to use:** **Step 2 (Module Testing) or Step 3 (Integration)** when I2C isn't working  
**Why:** I2C problems have many causes (hardware, addressing, timing, protocol). Diagnosis first = faster debugging.

**AI Policy:** AI can help you think through likely root causes, but YOU must perform diagnostics with oscilloscope or debug output.

**Context:** I2C communication failures fall into distinct categories:
1. **Hardware:** Pull-ups missing, wires loose, power problem
2. **Addressing:** Wrong slave address, address conflict
3. **Initialization:** Clock frequency wrong, sensor not responding
4. **Protocol:** Incorrect read/write sequence, timing violations
5. **Data:** Correct communication but sensor data is garbage

Systematic diagnosis narrows down which category your problem falls into.

### I2C Diagnosis Flow

```
DEBUGGING PROMPT FOR I2C COMMUNICATION:

Project Phase: [Unit Test #3 (Color Sensor) / #4 (IMU) / #5 (LCD) / Integration]
Module: [TCS34725 / MPU6050 / LCD / Full System]

WHAT I OBSERVE (the symptom):
  [Be specific and concrete, e.g.,
   "I2C_Read always returns 0xFF or timeout error"
   "Sensor doesn't respond to address 0x29"
   "Data reads work, but RGB values are always 65535 (garbage)"
   "I2C_Write succeeds but register isn't updated"
   "System freezes when trying to read sensor"
   "LCD shows nothing (blank screen)"]

WHAT SHOULD HAPPEN:
  [State the expected behavior clearly, e.g.,
   "I2C_Read(0x29, 0x12) should return 0x44 (TCS34725 ID)"
   "RGB values should change when I hold different colors in front of sensor"
   "LCD should display color name and angle"]

EVIDENCE I HAVE:
  [ ] Oscilloscope trace: [Describe SDA/SCL signals]
       Example: "SDA/SCL both high at rest, no clock pulses"
       Example: "Clock runs at 100 kHz, ACK bits visible after slave address"
       Example: "SDA stuck low, SCL toggling (bus error condition)"
  
  [ ] Debug output: [Paste printf or return values]
       Example: "I2C_Write returned 0 (success)"
       Example: "I2C_Read returned 0xFF (no acknowledge)"
       Example: "Read 4 bytes: [FF FF FF FF]"
  
  [ ] Hardware check: [Have you verified?]
       - [ ] Pull-up resistors present and 4.7kΩ on both SDA and SCL
       - [ ] SDA/SCL wired to correct pins (PB3 and PB2 for I2C0)
       - [ ] Sensor power supply is 3.3V (measure with multimeter on VCC)
       - [ ] Sensor ground connected to LaunchPad ground
       - [ ] No loose wires or cold solder joints
       - [ ] I2C0 clock enabled in SYSCTL_RCGI2C_R
  
  [ ] Code location: [Which function is broken?]
       Example: "I2C0_Init()" or "I2C0_Read()" or "TCS34725_Init()"
  
  [ ] When it fails: [Always? Intermittently? Only on first read? After sensor unplugged?]

MY TOP HYPOTHESES (before I ask AI):
  1. [First guess at root cause — ranked by likelihood]
  2. [Second guess]
  3. [Third guess]

MY QUESTIONS FOR YOU:

1. Given this symptom, what are the TOP 3 root causes I should investigate?
   [Ranked by likelihood and investigation speed]

2. For EACH suspected cause, what diagnostic test would I run?
   [Concrete: "Check SYSCTL_RCGI2C_R bit 0", "Measure SDA/SCL voltage at rest",
    "Add printf before/after I2C call", "Measure SDA/SCL waveform on oscilloscope"]

3. What's the FASTEST way to narrow it down? (Don't want to waste time on dead ends!)

4. What EDGE CASES could hide the problem?
   [Examples: "Works at 100 kHz but fails at 400 kHz",
    "Works on first read but fails on subsequent reads"]
```

### Example: "I2C_Read Always Returns 0xFF (Timeout)"

```
DEBUGGING PROMPT FOR I2C COMMUNICATION:

Project Phase: Unit Test #3 (TCS34725 Color Sensor)
Module: TCS34725 Color Sensor via I2C

WHAT I OBSERVE:
  "I call I2C_Read(0x29, 0x12, &buffer) to read the TCS34725 ID register.
   The function returns timeout error (0xFF or error status), no matter what address or register.
   Every read returns timeout, including addresses I know are wrong (0x00, 0xFF)."

WHAT SHOULD HAPPEN:
  "Reading address 0x29 register 0x12 should return 0x44 (TCS34725 ID) with success status.
   Reading a wrong address should return a timeout or NAK status quickly."

EVIDENCE:
  Hardware:
  - [ ] Pull-up resistors: YES, confirmed 4.7kΩ on SDA/SCL to 3.3V
  - [ ] SDA/SCL pins: Correct (PB3 and PB2)
  - [ ] Sensor power: 3.3V (verified with multimeter on VCC pin)
  - [ ] Sensor ground: Connected to LaunchPad ground
  
  Oscilloscope trace:
  - "SDA and SCL are both stuck LOW. No clock pulses visible. Bad sign!"
  
  Code:
  - I2C0_Init() called before I2C0_Read()
  - I2C0_Write() also returns timeout
  - No data being transmitted on I2C bus at all
  
MY TOP HYPOTHESES:
  1. SDA/SCL lines stuck low → I2C bus is frozen (master can't drive)
  2. I2C0 module not enabled in SYSCTL_RCGI2C_R (clock gating off)
  3. I2C0 initialization sequence incomplete (pins not configured as AF3)
  4. Pull-up resistors missing or wrong value (SDA/SCL can't be pulled high)
  5. Sensor powered off or power pin not connected

DIAGNOSTIC STEPS:
1. Check SYSCTL_RCGI2C_R bit 0 — is I2C0 clock enabled? (SYSCTL_RCGI2C_R0)
2. Measure SDA/SCL voltage at rest with multimeter — should be 3.3V (pulled high by resistors)
3. Check I2C0_Init() code — are you enabling the peripheral and setting up pins?
4. Manually toggle SCL with GPIO to verify pin control works
5. Check pin configuration — are PB2 and PB3 set to alternate function AF3?
```

**Most likely root cause:** I2C0 clock not enabled in SYSCTL. Check:
```c
// In I2C0_Init():
SYSCTL_RCGI2C_R |= SYSCTL_RCGI2C_R0;  // Enable I2C0 clock
```

---

## Template 2: Sensor Not Responding (No ACK / Wrong Address)

**When to use:** **Step 2 - When initializing a new sensor for the first time**  
**Why:** Sensors often fail to respond because of addressing, initialization, or configuration problems.

```
DEBUGGING PROMPT FOR SENSOR NOT RESPONDING:

SYMPTOM:
"I'm trying to initialize the TCS34725 Color Sensor. I call TCS34725_Init(), 
then try to read the ID register (address 0x29, register 0x12, should return 0x44).
My I2C_Read returns an error (timeout or NAK - No Acknowledge)."

DIAGNOSIS CHECKLIST:

1. ADDRESS VERIFICATION:
   [ ] Datasheet says TCS34725 default address is 0x29? Check the spec.
   [ ] Are there any address selection pins or jumpers on your sensor board?
   [ ] Try different addresses: 0x29 (default), maybe 0x28 or 0x39
   
2. POWER VERIFICATION:
   [ ] Multimeter on VCC: Should read 3.3V (LaunchPad supply voltage)
   [ ] Multimeter on GND: Should read 0V (ground reference)
   [ ] Are capacitors on the sensor board soldered correctly?
   [ ] Is the sensor board powered from the LaunchPad 3V3 pin?
   
3. I2C BUS VERIFICATION:
   [ ] Oscilloscope on SDA: Is it pulled high at rest (3.3V)?
   [ ] Oscilloscope on SCL: Is it pulled high at rest (3.3V)?
   [ ] Do you see clock pulses when I2C_Read is called?
   [ ] Do you see a NAK bit (low pulse) from the slave when address is sent?
   
4. INITIALIZATION SEQUENCE:
   [ ] Is I2C0 enabled in SYSCTL_RCGI2C_R?
   [ ] Is I2C master mode enabled (I2CMCS_STOP)?
   [ ] Is I2C clock frequency set correctly (100 kHz for standard, 400 kHz for fast)?
   [ ] Is I2CMTPR (Master Timer Period Register) calculated correctly?
   
5. PIN ASSIGNMENT:
   [ ] SDA connected to PB3?
   [ ] SCL connected to PB2?
   [ ] Correct alternate function (AF3 for I2C)?
   [ ] No other GPIO code fighting with I2C pins?

LIKELY ROOT CAUSES (ranked by likelihood):
  1. Wrong slave address (tried 0x29 but sensor is at different address?)
  2. Missing pull-up resistors (SDA/SCL stuck low, can't communicate)
  3. I2C0 clock not enabled in SYSCTL_RCGI2C_R
  4. Sensor power supply missing or voltage too low (brownout)
  5. I2C clock frequency too high (sensor doesn't support 400 kHz)
  6. Pin configuration wrong (not set to alternate function AF3)

VERIFICATION STEPS:
1. Query all I2C addresses (0x00-0x7F) to find your sensor
2. Confirm sensor ID register returns expected value
3. Confirm I2C clock frequency matches all sensor datasheets
```

---

## Template 3: Sensor Data is Garbage or Wrong Values

**When to use:** **Step 2 - When sensor responds but data is incorrect**  
**Why:** Wrong sensor data causes integration failures later (servo won't move correctly, wrong colors detected).

```
DEBUGGING PROMPT FOR GARBAGE DATA:

SYMPTOM:
"The TCS34725 color sensor responds and I can read registers successfully.
But the RGB values are always the same (65535, 65535, 65535) or always zero,
no matter what color I show to the sensor. The values never change."

ROOT CAUSE ANALYSIS:

1. SENSOR INITIALIZATION (TCS34725):
   [ ] Did you verify sensor ID by reading register 0x12? Should return 0x44
   [ ] Is the sensor enabled? Check ENABLE register (0x80), bit 0 should be 1
   [ ] Did you wait for sensor to stabilize after power-up?
       (TCS34725 needs ~50-100ms after enabling RGBC before reading valid data)
   [ ] Are you reading the correct registers for RGB data?
       Red: 0x94-0x95 (RDATAL, RDATAH)
       Green: 0x96-0x97 (GDATAL, GDATAH)
       Blue: 0x98-0x99 (BDATAL, BDATAH)
   
2. SENSOR CONFIGURATION (TCS34725):
   [ ] Is the color sensor in RGBC measurement mode?
   [ ] Is the integration time set correctly? (ATIME register 0x81)
   [ ] Is the sensor gain set correctly? (CONTROL register 0x8F)
   [ ] Are timing registers configured to give time for measurement?
   
3. DATA INTERPRETATION:
   [ ] Are you reading 16-bit values or 8-bit values? (TCS34725 uses 16-bit)
   [ ] Are you combining LSB/MSB correctly?
       Example: value = (DATAH << 8) | DATAL
   [ ] Are you reading bytes in the correct order from I2C?
   [ ] Are you accounting for 2-byte register pairs?
   
4. I2C TIMING:
   [ ] Are you waiting long enough between I2C reads?
   [ ] Are you reading data faster than sensor can update?
       (Integration time determines measurement speed)
   [ ] Did you enable the sensor AND wait for stabilization before first read?
   
5. EXPECTED VALUES SANITY CHECK:
   [ ] RGB values of 65535 = maximum (sensor saturated or not measuring)
   [ ] RGB values of 0 = sensor off or integration time wrong
   [ ] Real colors should give different R, G, B values
   [ ] White light should have R≈G≈B (similar values)
   [ ] Red object should have R>>G, R>>B (red dominant)

MOST LIKELY ROOT CAUSES:
  1. Sensor not enabled (integration time zero, no time for measurement)
  2. Not waiting after sensor power-up (data not valid yet)
  3. Reading wrong registers (constants are default/uninitialized values)
  4. MSB/LSB combined incorrectly (data scrambled)
  5. I2C read too fast (faster than integration time)

DEBUGGING STRATEGY:
  1. Verify sensor ID returns 0x44 (sensor is responding correctly)
  2. Read ENABLE register (0x80) — bit 0 should be 1 if sensor enabled
  3. Read ATIME register (0x81) — should be non-zero (integration time)
  4. Add delay(100) after TCS34725_Init()
  5. Read raw register values and verify they change when you change lighting
```

**Example fix:**
```c
// After TCS34725_Init(), wait for stabilization
delay_ms(100);  // Wait 100ms for first measurement to complete

// When reading color:
uint8_t buffer[6];
I2C0_Read(0x29, 0x94, buffer, 6);  // Read all 6 bytes at once
uint16_t red = (buffer[1] << 8) | buffer[0];    // RDATAL, RDATAH
uint16_t green = (buffer[3] << 8) | buffer[2];  // GDATAL, GDATAH
uint16_t blue = (buffer[5] << 8) | buffer[4];   // BDATAL, BDATAH
```

---

## Template 4: UART Output Isn't Updating / Blank Terminal

**When to use:** **Step 2 - When UART communication fails (Unit Test #2)**  
**Why:** UART debugging is essential before integrating I2C sensors. Good test baseline.

```
DEBUGGING PROMPT FOR UART PROBLEMS:

SYMPTOM:
"My code calls UART0_SendString('Hello World') but nothing appears in the terminal.
The terminal application is open but receiving no output. I see no text at all."

DIAGNOSIS CHECKLIST:

1. TERMINAL APPLICATION CHECK:
   [ ] Is terminal application actually running and visible? (Check window title)
   [ ] Is it set to correct COM port? (Right-click Properties → Port)
   [ ] Baud rate set to 57600? (Check UART0_Init code)
   [ ] Data bits: 8, Stop bits: 1, Parity: None (standard)
   [ ] Check for "Connect" button if application has one
   
2. HARDWARE CONNECTION:
   [ ] TX wire connected to LaunchPad RX pin (PA0)?
   [ ] RX wire connected to LaunchPad TX pin (PA1)?
       NOTE: RX goes TO the LaunchPad, TX comes FROM the LaunchPad
   [ ] Are wires soldered/seated properly or in correct USB port?
   [ ] USB cable securely connected to LaunchPad Debug port?
   
3. INITIALIZATION CODE (UART0_Init):
   [ ] Is UART0 enabled in SYSCTL_RCGUART_R?
       Code: SYSCTL_RCGUART_R |= SYSCTL_RCGUART_R0;
   [ ] Is UART0 configured for 57600 baud? Check BRD calculation:
       BRD = (System Clock) / (16 * BaudRate)
       For 40MHz clock: BRD = 40,000,000 / (16 * 57600) ≈ 43.4
       Rounded to 43 should give ~57,870 baud (close enough)
   [ ] Are GPIO pins PA0/PA1 configured as UART alternate function?
       Need to set alternate function to AF1 for UART
   [ ] Is UART transmit enabled (UART_CTL_TXE bit set)?
   [ ] Is UART receive enabled (UART_CTL_RXE bit set)?
   
4. CODE EXECUTION:
   [ ] Does code reach UART0_SendString() call? (Add LED toggle before it)
   [ ] Does UART_SendString() return successfully or error status?
   [ ] Are you sending one character at a time or whole strings?
   [ ] Is there a newline character (\\n) at end of strings?
   
5. TERMINAL APPLICATION TROUBLESHOOTING:
   [ ] Try unplugging USB and plugging into different USB port
   [ ] Try different terminal application (Putty, Tera Term, YAT, hyperterminal)
   [ ] Close and reopen terminal application
   [ ] Check Windows Device Manager: Does LaunchPad show up as COM port?
   [ ] In Device Manager, check for unknown/error devices with yellow !

MOST LIKELY ROOT CAUSES:
  1. UART0 clock not enabled in SYSCTL (most common!)
  2. Wrong COM port selected in terminal
  3. TX/RX wires reversed (TX should go to RX, RX to TX)
  4. Baud rate mismatch (e.g., code says 57600 but terminal set to 115200)
  5. USB not plugged into Debug port (some LaunchPads have multiple USB ports)
  6. GPIO pins PA0/PA1 not configured as alternate function (AF1 for UART)

VERIFICATION STEPS:
1. Add LED blink before UART_SendString() — if LED blinks, code reaches UART
2. Check System Clock — make sure PLL is configured correctly
3. Recalculate BRD and verify it matches code
4. Use oscilloscope to measure TX pin (PA1) — should see data pulses
```

---

## Template 5: LCD Display Shows Garbage or Nothing

**When to use:** **Step 2 - Unit Test #5 (LCD via I2C)**  
**Why:** LCD problems are usually I2C addressing, initialization, or backpack configuration.

```
DEBUGGING PROMPT FOR LCD PROBLEMS:

SYMPTOM:
"I'm trying to display text on the 16x2 LCD via I2C. The display shows
garbage characters (like █▓▒ instead of letters), blank screen, or nothing at all.
I2C reads/writes seem to complete without error status."

ROOT CAUSE ANALYSIS:

1. I2C ADDRESS VERIFICATION (LCD Backpack):
   [ ] Does your LCD board use address 0x27? (Very common default)
   [ ] Is there a way to change the address? (Some boards have jumpers)
   [ ] Try scanning all I2C addresses (0x00-0x7F) to find your LCD
       Use a simple loop: for addr = 0 to 127, try I2C0_Read(addr, 0, buffer)
   [ ] Typical addresses for LCD backpacks: 0x20, 0x27, 0x3F (try these)
   
2. BACKPACK CONTROL BYTE FORMAT (PCF8574T typical):
   The backpack uses a single I2C write to control the LCD:
   
   Bit 7 (BL): Backlight (1=on, 0=off) — If 0, display appears dark!
   Bit 6 (EN): Enable pulse (toggle 1→0 to latch command/data)
   Bit 5 (RW): Read/Write (0=write, 1=read) — Usually write (0)
   Bit 4 (RS): Register Select (0=command, 1=data)
   Bits 3-0: Data nibble (upper 4 bits of data)
   
   [ ] Are you setting backlight bit (bit 7)? If bit 7=0, display is dark
   [ ] Are you toggling Enable bit correctly? (pulse from 1→0 for each nibble)
   [ ] Are you sending RS (command vs. data) bits correctly?
   
3. LCD INITIALIZATION SEQUENCE:
   [ ] Wait 15ms after power-up before sending any commands
   [ ] Standard init (4-bit mode):
       1. Send 0x33 (Set to 8-bit mode, sent twice to ensure)
       2. Send 0x32 (Set to 4-bit mode)
       3. Send 0x28 (Function set: 4-bit, 2-line, 5×8 font)
       4. Send 0x0F (Display ON, cursor ON, blink ON)
       5. Send 0x01 (Clear display)
       6. Send 0x06 (Entry mode: increment cursor, no shift)
   [ ] Wait 1ms between commands
   [ ] Wait 10-15ms after clear command
   
4. DATA FORMAT (4-bit mode via I2C):
   [ ] LCD expects 4-bit data format (upper nibble = data)
   [ ] Each character sent as TWO I2C bytes:
       Byte 1: Upper nibble + control bits, EN high (1)
       Byte 2: Upper nibble + control bits, EN low (0)
   [ ] Then send lower nibble same way
   [ ] Control bits: RS bit tells LCD if it's data (1) or command (0)
   
5. TIMING:
   [ ] Wait 1ms between I2C writes
   [ ] Wait 100µs between EN pulses (high→low)
   [ ] Wait 50ms after initialization before sending data
   [ ] Wait 2ms after clear/home commands

MOST LIKELY ROOT CAUSES:
  1. Backlight bit (bit 7) not set → display is dark/invisible
  2. Wrong I2C address (LCD at 0x27 but code uses 0x20)
  3. Initialization sequence incomplete or wrong order
  4. RS (command/data) bit wrong → commands interpreted as data or vice versa
  5. Enable pulse too short or not toggled correctly (needs 1→0 transition)
  6. Not waiting 15ms after power-up (LCD not ready for commands)

EXAMPLE (PCF8574T I2C Backpack):
```

Write sequence to display "Hello":
1. Send backlight on + clear display command
2. Wait 2ms (clear takes time)
3. Set RS=1 (data mode)
4. For each character:
   - Send upper nibble with EN=1, then EN=0
   - Send lower nibble with EN=1, then EN=0
5. Characters appear on LCD

---

## Template 6: Servo Motor Not Moving / Jittering / Wrong Position

**When to use:** **Step 2 - Unit Test #6 (Servo Motor)**  
**Why:** Servo problems are usually PWM frequency, duty cycle, or power supply issues.

```
DEBUGGING PROMPT FOR SERVO PROBLEMS:

SYMPTOM:
"I'm trying to control a servo motor with PWM. The servo doesn't move,
it moves to wrong position, or it jitters and vibrates unnaturally."

ROOT CAUSE ANALYSIS:

1. PWM SIGNAL VERIFICATION (Oscilloscope):
   [ ] Oscilloscope on servo PWM pin (PB6): Do you see a pulse train?
   [ ] Expected frequency: 50 Hz (20ms period, standard for servos)
   [ ] Pulse width range: 1.0-2.0ms (1ms = -90°, 1.5ms = 0°, 2ms = +90°)
       - 1.0ms (5% duty) = -90° (full left)
       - 1.5ms (7.5% duty) = 0° (center)
       - 2.0ms (10% duty) = +90° (full right)
   [ ] Is signal stable or noisy?
   [ ] Is duty cycle in range 5-10%? (Outside range = servo won't respond)
   
2. PWM MODULE INITIALIZATION (TM4C123):
   [ ] PWM module enabled in SYSCTL_RCGPWM_R?
       Code: SYSCTL_RCGPWM_R |= SYSCTL_RCGPWM_R0;
   [ ] Correct PWM output: M0PWM0 on pin PB6?
   [ ] PWM clock divider set correctly?
   [ ] Load value (PWM period) calculated correctly?
       Period = Load / (Clock / Divider)
       For 50 Hz: Load = (40MHz / 64) / 50 = 12,500
   
3. DUTY CYCLE CALCULATION:
   [ ] Servo angle = position from -90° to +90°
   [ ] Pulse width = 1.5ms + (angle / 90°) × 0.5ms
       Examples:
       -90° → 1.0ms
       -45° → 1.25ms
        0° → 1.5ms
       +45° → 1.75ms
       +90° → 2.0ms
   [ ] Compare pulse width to oscilloscope reading — does it match?
   [ ] Is duty cycle in 5-10% range for typical servo?
   
4. POWER SUPPLY:
   [ ] Servo power: Most servos need 5V, some accept 3.3V
   [ ] LaunchPad GPIO outputs 3.3V — is servo rated for this?
   [ ] If servo needs 5V, you need a level shifter or external 5V supply
   [ ] Servo ground: Is it connected to LaunchPad ground?
   [ ] Servo power: Is it adequately powered (not under-voltage)?
   
5. SIGNAL PIN ASSIGNMENT:
   [ ] Servo signal pin connected to M0PWM0 (PB6)?
   [ ] Not connected to wrong PWM output?
   [ ] GPIO PB6 configured for PWM alternate function (AF1)?
   [ ] Not being overwritten by GPIO code?
   
6. MOVEMENT SEQUENCE TEST:
   [ ] Servo should move through: 0° → -45° → 0° → +45° → 0° → -90° → 0° → +90° → 0°
   [ ] Each position held for 1 second
   [ ] Movement should be smooth, not jerky
   [ ] Servo should stop at each position (not drift)

MOST LIKELY ROOT CAUSES (ranked):
  1. Duty cycle wrong (outside 5-10% range) → servo doesn't recognize signal
  2. PWM frequency wrong (not 50 Hz) → servo doesn't recognize timing
  3. Servo power not connected or voltage too low → no torque to move
  4. Level shifter needed (LaunchPad 3.3V too low for servo) → servo weak
  5. PWM load value calculated wrong → frequency off
  6. Angle calculation wrong → servo told to go to wrong position

VERIFICATION STEPS:
1. Measure PWM frequency with oscilloscope — should be exactly 50 Hz
2. Measure pulse width at center position (1.5ms) — should be 7.5% duty cycle
3. Manually move servo by hand — does it have torque/resistance?
4. Check servo power supply voltage with multimeter — should be rated voltage
5. Try different angles (0°, +90°, -90°) and verify oscilloscope shows different pulse widths
```

---

## Template 7: System Integration Crash or Lockup

**When to use:** **Step 3 - When combining all modules**  
**Why:** Integration often reveals timing, priority, and resource conflicts not visible in unit tests.

```
DEBUGGING PROMPT FOR SYSTEM LOCKUP:

SYMPTOM:
"When I run all modules together (UART + I2C + Servo), the system hangs
or crashes unexpectedly. It works fine when testing each module alone.
UART output stops, LED stops blinking, or system becomes unresponsive."

ROOT CAUSE ANALYSIS:

1. INITIALIZATION ORDER & DEPENDENCIES:
   [ ] Which modules depend on others?
       Example: TCS34725 needs I2C0_Init() first
       Example: Servo needs WTIMER0_Init() and PWM_Init()
   [ ] Are you initializing in dependency order?
       Safe order: UART0 → WTIMER0 → I2C0 → Individual sensors → Full system
   [ ] Are there any circular dependencies? (Module A needs B, B needs A)
   [ ] Are all peripherals clocked? (Check SYSCTL_RCGUART_R, SYSCTL_RCGI2C_R, etc.)
   
2. INTERRUPT CONFLICTS & PRIORITIES:
   [ ] Which interrupts are enabled? (Timer, UART, I2C, GPIO)
   [ ] Do interrupt handlers share variables? (Race conditions!)
       Example: Main loop reads sensor_value, interrupt sets sensor_value
   [ ] Are interrupt priorities set correctly?
   [ ] Is a high-priority interrupt blocking a low-priority one?
   [ ] Is an interrupt handler hanging (infinite loop)?
   
3. RESOURCE CONFLICTS:
   [ ] Are two modules using the same peripheral?
       Example: Both using Timer0? Both using PWM?
   [ ] Are two I2C transactions happening simultaneously?
       (Only one can happen at a time on I2C0 bus)
   [ ] Is UART blocking while waiting for I2C?
   [ ] Is main loop blocked waiting for interrupt that never fires?
   
4. INFINITE LOOPS & HANGS:
   [ ] Add a simple task: Print "System Running\n" every 1 second via UART
       If printing stops → infinite loop or deadlock somewhere
   [ ] Add LED blink in main loop (if it stops, you're in infinite loop)
   [ ] Check for while(1) loops with no escape condition
   [ ] Check for I2C_Read() calls with no timeout (waits forever if sensor unplugged)
   
5. STACK & MEMORY ISSUES:
   [ ] Check for buffer overflows (arrays written past end)
   [ ] Check for large local arrays on stack (could overflow stack)
   [ ] Check for memory leaks in malloc/free
   [ ] Each function uses stack — deeply nested calls use more stack
   
6. TIMING & DEADLOCK DETECTION:
   [ ] One module waiting for another that's stuck?
       Example: Main loop waiting for I2C0_Read() that never returns
   [ ] Add timeout checking to all blocking operations:
   
   ```c
   uint32_t timeout = 1000000;  // ~1 second at 1M iterations/sec
   while (!I2C_Done && timeout--) { }
   if (timeout == 0) { 
       printf("I2C Timeout! Sensor not responding\\n"); 
       // Reset or skip this sensor
   }
   ```

DIAGNOSTIC APPROACH:
  1. Test with only UART + Timer (no I2C, no sensors)
     → If this works, problem is with I2C or sensors
  2. Add I2C0_Init() but don't read any sensors yet
     → Does system still work?
  3. Add one sensor at a time (TCS34725, then MPU6050, then LCD)
     → First sensor that causes crash identifies the problem
  4. Check interrupt nesting — is a high-priority interrupt blocking a low-priority one?
  5. Add timeout handling to all I2C operations

MOST LIKELY ROOT CAUSES:
  1. Infinite loop in I2C_Read() (no timeout handling) — waits forever
  2. Race condition: interrupt modifying variable while main loop reads it
  3. Initialization order wrong (using uninitialized peripheral)
  4. Two modules using same peripheral → conflicts
  5. Stack overflow from large arrays or deep function calls
  6. Interrupt priority wrong → deadlock between handlers
  7. Sensor disconnected/unplugged → I2C_Read hangs without timeout
```

---

## Common I2C Error Codes & What They Mean

| Return Value | Meaning | Likely Cause | Fix |
|---|---|---|---|
| **0** | Success | Operation completed successfully | N/A |
| **-1** | No ACK from slave | Wrong address, sensor not powered, pull-ups missing | Check address, power, pull-ups |
| **-2** | Bus busy/timeout | Slave holding SCL/SDA low (stuck), I2C hardware error | Check I2C hardware, reset I2C |
| **-3** | Data corrupted | CRC error or noise on I2C bus | Check wiring, reduce clock speed |
| **0xFF** | Timeout error | No response from slave within timeout period | Verify slave address and presence |
| **Hangs/Freezes** | Infinite wait | No timeout handler in I2C_Read/Write | Add timeout logic to I2C functions |

---

## Expected Debugging Frequency by Step

| Step | Debug Interactions | Focus Area |
|---|---|---|
| **Step 1** (Requirements & Design) | 0 | None (design phase) |
| **Step 2** (Module Testing) | 2-4 | I2C initialization, sensor communication, module isolation |
| **Step 3** (Integration & Final) | 1-3 | Integration issues, timing, system stability, servo movement |
| **TOTAL** | **3-7** | Spread across Steps 2-3 |

**Note:** Most debugging happens in Step 2 when individual modules are tested. Good module debugging prevents 80% of integration problems.

---

## Quick Debugging Checklist

When stuck, go through this systematically:

- [ ] **Hardware:** Wires connected? Power on (3.3V)? Pull-ups present (4.7kΩ)?
- [ ] **Initialization:** Clocks enabled in SYSCTL? I2C configured? Sensors detected via ID?
- [ ] **Communication:** Do you see signals on oscilloscope? ACK bits present?
- [ ] **Data:** Are values in expected range? Changing over time? Not garbage?
- [ ] **Timing:** Is system responsive? Any hangs or timeouts? UART still printing?
- [ ] **Integration:** Does it work with all modules? Just some? Which combination breaks?

---

*Copyright © 2026, Computer Engineering Department, California State University, Long Beach.*  
*Instructor: Dr. Min He*  
*This document is for educational use in CECS 447 Final Project, April 20 — May 13, 2026.*