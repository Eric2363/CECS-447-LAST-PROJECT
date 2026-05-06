# CECS 447 Final Project: AI Tutoring Prompts by Step

**Course:** CECS 447 (Senior Level Embedded Systems)  
**Project:** I2C Bus Communication System (Multi-Device Sensor Integration)  
**Author:** Dr. Min He  
**Copyright:** © 2026, Computer Engineering Department, California State University, Long Beach

---

## How to Use This Document

This document provides **ready-to-use tutoring prompts** for each step of the 3-step final project workflow.

**For each step, you'll find:**
- ✅ Detailed prompt examples you can paste into ChatGPT/Claude
- ✅ Multiple prompt variations for different aspects of that step
- ✅ Tips on what to focus on at each stage
- ✅ What AI can help with (and what you must do yourself)

**Important:** These prompts are **guides**, not scripts. Adapt them to your specific questions and designs.

---

## STEP 1: Requirements & System Design (Apr 20–22, 3 days)

### Goal

Identify all functional requirements and hardware constraints for your I2C multi-device system. Don't skip this—constraints discovered in Step 2 or 3 will force costly redesigns.

### AI Use Policy
- ✅ AI can help you understand what constraints *mean*
- ✅ AI can guide you to find constraints in datasheets
- ❌ Don't ask AI to just list constraints for you—discover them yourself

---

### Prompt 1A: Requirements & Specification Analysis

**When to use:** Early in Step 1 (first day)

```
You are a helpful tutor for embedded systems design.

I'm starting Step 1 of the I2C Communication final project. My first task is to 
extract and organize all the requirements from the project specification.

HERE'S WHAT I UNDERSTAND SO FAR:

The project spec says:
- This is a 24-day project (April 20–May 13) divided into 3 steps
- I need to build an "I2C-based sensor fusion system"
- The system reads color and motion data, displays on LCD, controls servo
- I have specific components: TCS34725 sensor, MPU6050 sensor, 16x2 LCD, servo motor

MY QUESTIONS:

QUESTION 1: FUNCTIONAL REQUIREMENTS
- What does "functional requirement" mean? (vs. non-functional)
- Looking at the spec, what is the system supposed to DO?
  * Read color from the color sensor?
  * Display color on LCD?
  * Move the servo based on motion?
  * All of the above? Anything else?
- How do I extract these from the project description vs. make assumptions?

QUESTION 2: PERFORMANCE REQUIREMENTS
- The spec mentions "Every 100 milliseconds" for sampling and "Every 1 second" for display
  * Is 100ms a hard constraint or a target?
  * What happens if sampling is slower? Faster?
- Are there other timing requirements I should find?
- Should I list minimum/maximum/target values?

QUESTION 3: HARDWARE CONSTRAINTS
- The spec lists specific components (TCS34725, MPU6050, LCD, servo)
  * Are these fixed, or can I substitute?
  * What does it mean that "students choose I2C1-3" and "WTIMER1-5"?
  * How does "student choice" differ from "required component"?
- What constraints do these components impose on the system?
  (E.g., "servo needs 50Hz PWM" is a constraint from the component)

QUESTION 4: INTERFACE REQUIREMENTS
- The spec mentions LCD output: "Color: [RED/GREEN/BLUE]" and "Angle: [−90° to +90°]"
  * Is this the exact format required, or just an example?
  * What if my color detection algorithm works differently?
- For UART output, the spec shows a format: "Color: R=12345, G=02345, B=01234 | Angle: X=45°..."
  * Is this required, or can I choose my own format?
- What are the actual display requirements vs. suggested examples?

QUESTION 5: QUALITY & ACCEPTANCE CRITERIA
- The spec says "no compiler warnings"—is this a hard requirement?
- The spec says "smooth, jitter-free movement" for servo—how do I measure this?
- How do I know when my system "meets requirements"?
- What are PASS vs. FAIL criteria?

MY CURRENT UNDERSTANDING:
[List what you think are the main functional requirements]
[List what you think are the performance requirements]
[List what you think are the hardware constraints]

Help me organize the specification into clear, testable requirements so that 
Step 2 designers know exactly what to build.

[Paste the project specification or key sections]
```

**Expected AI response:** Guidance on requirements analysis, help organizing specs into functional/non-functional categories, identifying ambiguities or missing requirements

**Verification checklist:**
- ☐ Listed at least 5 functional requirements (what the system must do)
- ☐ Listed all performance requirements (timing, response times, accuracy)
- ☐ Listed all hardware constraints (component-specific requirements)
- ☐ Listed all interface requirements (LCD format, UART format, input handling)
- ☐ Identified which requirements are fixed vs. flexible
- ☐ Identified any ambiguities that need clarification

---

### Prompt 1B: Hardware Design & Peripheral Configuration

**When to use:** Middle of Step 1 (day 2)

```
You are a helpful tutor for embedded systems hardware design.

I'm designing the hardware configuration for my I2C system. The spec gives me 
flexibility on which peripheral modules to use, and I need to make good choices.

MY DESIGN CHALLENGES:

QUESTION 1: I2C MODULE SELECTION & CLOCK DESIGN
The spec says I can choose I2C1, I2C2, or I2C3. My questions:

- I have three I2C devices (TCS34725 at 0x29, MPU6050 at 0x68, LCD at 0x27)
  * Do they ALL share the same I2C bus, or can I split them?
  * The spec says one "I2C module" (singular), so I think they share. Correct?

- I found that I2C supports different clock speeds:
  * Standard Mode: 100 kHz
  * Fast Mode: 400 kHz
  * Fast Mode Plus: 1 MHz
  Looking at component datasheets, what clock speed should I choose?
  (Hint: One device might have a slower max speed than the others)

- I2C requires pull-up resistors on SDA and SCL. The spec mentions "4.7kΩ pull-ups"
  * Where do these go? On the TM4C123 side? On the sensor side? Both?
  * Do I need one set (shared) or multiple sets?

- The three devices have different slave addresses. How do I know these won't conflict?
  * How do I verify the LCD backpack address (the spec suggests 0x27)?

QUESTION 2: PWM MODULE & SERVO CONTROL
The spec says I can choose M0PWM1-7 or M1PWM0-7 for servo control. My questions:

- Servo motors need a 50 Hz PWM signal. 
  * Why 50 Hz specifically? What does this frequency mean?
  * What is the relationship between 50 Hz and servo position (0-180°)?
  * How does PWM duty cycle control servo angle?

- I have multiple PWM channels to choose from. Does it matter which one?
  * Could I use multiple PWM outputs (e.g., PWM1 and PWM2)?
  * Or should I stick with just one?

- What are the pin constraints?
  * If I choose M0PWM1, which TM4C123 pin controls it?
  * Could this pin conflict with my I2C pins?

QUESTION 3: TIMER MODULE & TIMING REQUIREMENTS
The spec says "I need 1 millisecond delays" using WTIMER1-5 (my choice). My questions:

- The spec mentions "Every 100ms read sensors" and "Every 1 second update LCD"
  * Do I need a 1ms timer, or a 100ms timer, or both?
  * If I have only a 1ms timer, how do I generate 100ms and 1000ms delays?

- Timing accuracy: Does 1ms mean exactly 1ms, or approximately?
  * If I'm off by 5%, does the system break?

- Should I use timer interrupts or polling?
  * Interrupts are more efficient but harder to debug
  * Polling is simpler but wastes CPU time

QUESTION 4: BLOCK DIAGRAM & PIN ASSIGNMENT
I need to plan how everything connects:

- Draw a block diagram showing:
  * TM4C123 (with labeled I2C, PWM, UART, WTIMER modules)
  * TCS34725, MPU6050, LCD, Servo
  * How they connect (I2C bus, PWM signal, power, ground)

- Create a pin assignment table:
  * Which TM4C123 pins are used for I2C1 (SDA/SCL)?
  * Which pin for PWM (servo signal)?
  * Which pins for UART0 (debugging)?

- Identify potential conflicts:
  * Could any two peripherals share the same pins?
  * Could pull-up resistors cause signal issues?

QUESTION 5: SIGNAL INTEGRITY & HARDWARE CONSTRAINTS
- I2C is a shared bus with open-drain drivers. What does this mean?
  * Why do we need external pull-up resistors?
  * What happens if I don't have them?

- The spec mentions "no compiler warnings" and "smooth servo movement"
  * Are there hardware-level constraints that affect these? (e.g., timing precision)

MY CURRENT DESIGN:
[Sketch: Which I2C module? Clock speed? PWM channel? WTIMER channel?]
[Sketch: Block diagram of hardware connections]
[Sketch: Pin assignment table]

Help me verify my hardware design:
1. Peripheral choices are sensible (no conflicts, good use of available modules)
2. Clock speeds and pin assignments are correct
3. I understand WHY each choice matters for the final system

[Paste your block diagram and pin assignment thoughts]
```

**Expected AI response:** Hardware constraint validation, signal integrity guidance, pin conflict checking, clock speed selection rationale

**Verification checklist:**
- ☐ Selected I2C module (I2C1, I2C2, or I2C3) and justified choice
- ☐ Determined correct I2C clock frequency based on all devices
- ☐ Planned pull-up resistor placement and verified no conflicts
- ☐ Selected PWM module and channel for servo control
- ☐ Understood relationship between 50 Hz and servo positioning
- ☐ Selected WTIMER module for system timing
- ☐ Created block diagram showing all connections
- ☐ Created pin assignment table (I2C SDA/SCL, PWM pin, UART pins)
- ☐ Identified and resolved any pin conflicts
- ☐ Verified slave addresses don't conflict

---

### Prompt 1C: Software Architecture & Module Design

**When to use:** End of Step 1 (day 2-3)

```
You are a helpful tutor for embedded systems software design.

I'm designing the high-level software architecture for my I2C system. I need to 
decide how to organize my code into modules, what data structures to use, and how 
modules will communicate.

MY DESIGN CHALLENGES:

QUESTION 1: MODULE BOUNDARIES & RESPONSIBILITIES
Looking at my system, I need to think about what modules to create. Currently thinking:

- I2C Hardware Layer: Low-level I2C read/write operations
- Sensor Drivers: TCS34725 (color), MPU6050 (motion), LCD display
- Servo Controller: PWM-based servo positioning
- Timer Module: Delay functions using WTIMER
- Main Application: Reads sensors, calculates, controls servo, displays output

My questions:
- Should each sensor have its own module, or should all sensors share one module?
- Should I have separate modules for "reading data" vs. "processing data"?
  (e.g., separate ColorSensor_ReadRaw() from ColorSensor_DetectColor())
- What is the "right" granularity? How many modules is too many?
- How do I know if my module boundaries are good?

QUESTION 2: DATA STRUCTURES & INFORMATION FLOW
I need to plan what data flows between modules:

- The I2C hardware layer will read raw bytes from sensors
- The sensor drivers will convert these bytes to meaningful values
  (e.g., TCS34725 returns R/G/B; MPU6050 returns acceleration X/Y/Z)
- The main app will use these values to control the servo

Specifically:
- What data structure should hold color data? (struct? array? individual values?)
- What data structure should hold motion data?
- How does the servo controller receive its target angle?
- How does the LCD know what to display?

QUESTION 3: MODULE INTERFACES (HIGH-LEVEL)
I need to design how modules communicate without specifying implementation:

Example: For the TCS34725 color sensor, I might have:
- Module responsibility: "Read RGB color values from TCS34725"
- Inputs: (nothing external; reads from I2C bus via I2C driver)
- Outputs: RGB color values (somehow returned to main app)
- Dependency: Needs I2C_Read/Write functions from I2C driver

Questions:
- For each module, what are its inputs, outputs, and dependencies?
- Should modules communicate directly or through a central "main" coordinator?
- Should a sensor module "push" data to main, or should main "pull" data from sensor?

QUESTION 4: INITIALIZATION SEQUENCE & STATE
My system needs initialization:

1. Initialize hardware modules (I2C, UART, PWM, WTIMER)
2. Initialize sensor drivers (detect sensors, configure them)
3. Start main loop (read sensors, update outputs)

Questions:
- What if a sensor fails to initialize? Should the whole system stop, or continue without that sensor?
- Should I have a system state? (e.g., "initializing", "running", "error")
- Do some modules depend on others being initialized first? (e.g., sensor drivers need I2C driver first)

QUESTION 5: TIMING & CONTROL FLOW
The spec requires different sampling rates:

- Sensors read "every 100ms"
- LCD updates "every 1 second"
- Servo updates "in real-time" (as fast as possible?)

Questions:
- Should I have a single main loop that does everything, or separate modules with their own loops?
- How do I implement "every 100ms" and "every 1 second" in code?
  (Counters? Timer interrupts? Separate threads?)
- What is the overall control flow? (flowchart or state machine)

QUESTION 6: ERROR HANDLING & ROBUSTNESS
What happens if something goes wrong?

- If the I2C read times out, what should the sensor driver do?
- If the LCD is disconnected, should the system still work (just without display)?
- If the servo PWM doesn't respond, should the system crash or degrade gracefully?

Questions:
- What error cases should each module handle?
- Should errors be reported to main, or should modules handle them silently?
- How do I recover from errors?

MY CURRENT ARCHITECTURE:
[Sketch: Which modules do I need? What are their responsibilities?]
[Sketch: What data is passed between modules?]
[Sketch: How do modules communicate?]
[Sketch: What is the initialization sequence?]
[Sketch: What is the main loop control flow?]

Help me verify my software design:
1. Module boundaries make sense (low coupling, high cohesion)
2. Data flow between modules is clear
3. Initialization sequence is correct
4. Control flow works for all the timing requirements
5. Error handling strategy is reasonable

[Paste your module diagram, data flow diagram, and control flow sketches]
```

**Expected AI response:** Architecture validation, module boundary feedback, data flow suggestions, control flow alternatives, error handling strategies

**Verification checklist:**
- ☐ Identified all required modules and their responsibilities
- ☐ Planned data structures for sensor data and system state
- ☐ Designed module interfaces (inputs, outputs, dependencies)
- ☐ Planned initialization sequence with error handling
- ☐ Designed main loop control flow to meet timing requirements
- ☐ Planned error handling strategy for each module
- ☐ Identified module dependencies (which modules need others)
- ☐ Sketched module interaction diagram (data flow)
- ☐ Verified module coupling is low and cohesion is high

---

## STEP 2: Module Implementation & Testing (Apr 23–May 4, 12 days)

### Goal

Implement and thoroughly test each I2C module independently. Modules must work correctly in isolation before Step 3 integration.

### AI Use Policy
- ✅ AI can help you debug sensor communication issues
- ✅ AI can explain sensor datasheets and register meanings
- ✅ AI can help you trace through timing problems
- ❌ Don't ask AI to write your module code—write it yourself

---

### Prompt 2A: Sensor Initialization & Configuration Debugging

**When to use:** Early Step 2 (days 1-4)

```
You are a helpful tutor for embedded systems debugging.

I'm implementing the ColorSensor module and having trouble initializing the TCS34725.

MY CURRENT CODE:
[Paste your ColorSensor_Init() function here]

MY PROBLEM:
- I write the configuration register, but the sensor doesn't respond
- OR I read the ID register and get 0x00 (not the expected 0x44)
- OR The sensor reads garbage data (all 0xFF or all 0x00)

HERE'S WHAT I'VE TRIED:
1. Checked the slave address: 0x29 ✓
2. Verified I2C bus works (can read other devices) ✓  
3. Added a delay after writing config ✓
4. Checked the datasheet for register addresses ✓

MY QUESTIONS:

1. INITIALIZATION SEQUENCE:
   Looking at the datasheet, initialization should be:
   Step A: [Describe what you think should happen]
   Step B: [...]
   Step C: [...]
   Is this order correct?

2. WHO_AM_I REGISTER:
   - I'm trying to read the ID register (address: ?)
   - The datasheet says the ID should be 0x44
   - I get [your value], which means...?

3. CONFIGURATION REGISTER:
   - I need to enable [specific features]
   - The datasheet shows bits [X, Y, Z] control this
   - Should I write 0x[your hex value] or 0x[different hex value]?

4. TIMING:
   - How long should I wait after writing configuration before reading?
   - Is 10ms enough? 100ms? 1 second?

5. DATA FORMAT:
   - The color output is 16 bits per channel (R, G, B)
   - Should I read 2 bytes per channel (total 6 bytes)?
   - Or does the sensor output all 8 bytes of data automatically?

WHAT I KNOW WORKS:
[Describe what parts of your initialization DO work]

WHAT I WANT TO VERIFY:
Does my initialization sequence match the datasheet? 
What am I doing wrong?

[Paste relevant datasheet excerpts for the sensor initialization section]
```

**Expected AI response:** Step-by-step verification of initialization sequence, register value explanations, timing analysis

**Verification checklist:**
- ☐ WHO_AM_I register returns correct value (0x44 for TCS34725)
- ☐ Configuration register write succeeds
- ☐ Sensor responds after initialization
- ☐ Initial sensor reads return reasonable values (not all 0x00 or 0xFF)

---

### Prompt 2B: I2C Transaction Debugging & Error Handling

**When to use:** Middle Step 2 (days 5-8)

```
You are a helpful tutor for I2C protocol debugging.

I've implemented all three sensor modules, but I2C transactions are failing intermittently.

MY ISSUE:
- Sometimes I2C_Read() returns success
- Sometimes it returns error code [X] (timeout / NACK / bus error)
- The sensors work fine individually, but fail together

MY CURRENT ERROR HANDLING:
[Paste your I2C error handling code]

MY TRANSACTIONS:

Transaction 1: ColorSensor reads color data
- Start I2C transaction to slave 0x29
- Write register address 0x16 (first color byte)
- Read 8 bytes (R high, R low, G high, G low, B high, B low, Clear high, Clear low)
- Expected: 8 bytes of color data

Transaction 2: IMU reads angle data
- Start I2C transaction to slave 0x68
- Write register address 0x3D, 0x3E, 0x3F (angle registers)
- Read 6 bytes (accel X, Y, Z)
- Expected: 6 bytes of acceleration data

MY DEBUGGING OBSERVATIONS:
[Describe when it fails, any error codes, patterns you've noticed]

MY QUESTIONS:

1. TRANSACTION TIMING:
   - How long should I wait between writing slave address and reading/writing data?
   - Is the delay in my code sufficient?

2. BUS STATE:
   - If one transaction fails, does it leave the bus in a bad state?
   - Should I reset the I2C module between transactions?

3. SENSOR CONFLICTS:
   - Are my ColorSensor and IMU transactions interfering with each other?
   - Should I add delays between reading different sensors?

4. ERROR RECOVERY:
   - When I2C_Read() returns an error, what should I do?
   - Retry immediately? Retry with delay? Skip? Reset bus?
   - How many retries are reasonable?

5. INTERRUPT TIMING:
   - Does the I2C ISR have a timeout?
   - What does error code [X] specifically mean?

WHAT I KNOW:
- Single sensor reads work: ___
- Multiple sensors: ___
- Frequency of failures: ___

[Paste your I2C transaction code and error messages]
```

**Expected AI response:** I2C protocol timing analysis, error code explanations, debugging strategies, error recovery patterns

**Verification checklist:**
- ☐ All I2C transactions complete without timeout
- ☐ Each sensor returns data in correct format
- ☐ Multiple sensors work together without conflicts
- ☐ Error handling prevents infinite loops
- ☐ Bus recovers correctly from transient errors

---

### Prompt 2C: Sensor Data Validation & Module Testing

**When to use:** Late Step 2 (days 9-12)

```
You are a helpful tutor for sensor data analysis.

I've implemented all three sensor modules and they communicate via I2C.
Now I need to verify the data they return is correct.

MY MODULES:
```
struct ColorData {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t clear;
};

struct IMUData {
    int16_t accel_x;
    int16_t accel_y;
    int16_t accel_z;
};

uint16_t servo_angle;  // 0-180 degrees
```

MY DATA VALIDATION CHALLENGES:

1. COLOR SENSOR DATA:
   - I'm reading raw 16-bit values from TCS34725
   - Should I convert these to 0-255 RGB range?
   - What's a "normal" reading? (e.g., is 500 red normal? 5000?)
   - How can I verify my color readings are correct without test equipment?

2. IMU DATA:
   - I'm reading 16-bit acceleration values
   - The datasheet mentions "sensitivity: 2g range = ±16384 LSB/g"
   - Should I convert raw values to m/s² ?
   - What's a "normal" reading? (gravity = 9.81 m/s²)
   - If sensor is still, should I read exactly 0 or 0±noise?

3. SERVO CONTROL:
   - I need to map IMU angle to servo angle (0-180 degrees)
   - The IMU gives me acceleration; how do I get angle?
   - Should I use just one axis (X or Y) or multiple?
   - What's the range of servo angles I can control?

4. MODULE TESTING:
   - How do I test ColorSensor_ReadColor() returns valid data?
   - How do I test IMU_ReadAccel() is accurate?
   - Should I create test vectors? Use known inputs?
   - What are the acceptance criteria?

MY TEST PLAN:
[Describe what "correct" data looks like]
[Describe how you'll generate test data]
[Describe acceptance criteria for each module]

Help me verify:
1. Raw sensor readings are within expected range
2. Data conversions are mathematically correct
3. Module functions return validated data
4. Integration with servo control is feasible

[Paste your data reading and conversion code]
```

**Expected AI response:** Sensor data interpretation, validation ranges, conversion formulas, testing strategies

**Verification checklist:**
- ☐ Color sensor returns values in expected range
- ☐ IMU acceleration readings make physical sense
- ☐ Data conversions are mathematically correct
- ☐ Each module returns consistent, repeatable data
- ☐ Test cases defined for each module function

---

## STEP 3: Integration, Testing & Final Submission (May 5–13, 9 days)

### Goal

Integrate all modules into a working I2C system, perform system-level testing, and deliver a robust final product.

### AI Use Policy
- ✅ AI can help you debug system-level timing and synchronization issues
- ✅ AI can help you think through integration problems
- ✅ AI can help you optimize performance
- ❌ Don't ask AI to write integration code—design and implement it yourself

---

### Prompt 3A: Multi-Module Integration & Timing Synchronization

**When to use:** Early Step 3 (days 1-3)

```
You are a helpful tutor for real-time embedded systems.

I'm integrating all modules (ColorSensor, IMU, LCD, Servo) into one main program.

MY MAIN LOOP:
[Paste your main program loop here]

MY INTEGRATION CHALLENGE:

TIMING REQUIREMENTS:
- Servo must update position every [X] ms based on IMU angle
- LCD must display color every [X] ms
- IMU and ColorSensor must be read frequently enough to not miss changes
- UART must output debug info every [X] ms

QUESTION 1: LOOP FREQUENCY
- How often should my main loop execute?
- Constraints: 
  * PWM needs 50 Hz (20 ms period) for servo
  * LCD needs ≈ 10 Hz (100 ms) for smooth display
  * I2C transactions take ≈ [your measurement] ms each
  What's the optimal loop frequency?

QUESTION 2: SAMPLING MULTIPLE SENSORS
- In each loop iteration, should I read:
  Option A: All sensors every iteration?
  Option B: Alternate sensors (Color one iteration, IMU next)?
  Option C: Read based on timing (e.g., IMU every 10ms, Color every 50ms)?
  What's the best approach?

QUESTION 3: I2C CONTENTION
- Can I read ColorSensor and IMU in the same loop without conflicts?
- They're on the same I2C bus (my chosen I2C1-3) but different addresses, so they shouldn't interfere...right?
- What if one transaction is slow? Does it block the other?

QUESTION 4: REAL-TIME CONSTRAINTS
- If an I2C read takes 50ms and my loop needs 20ms timing, what breaks?
- How should I handle slow transactions?
- Should I use interrupts? DMA? Polling with timeouts?

QUESTION 5: SYNCHRONIZATION
- The servo is controlled by PWM (interrupt-driven)
- The LCD displays via I2C (blocking transaction)
- How do I keep everything synchronized?
- What if I2C is slow and PWM falls out of sync?

MY CURRENT CODE STRUCTURE:
```c
while (1) {
    // Read Color Sensor (I2C transaction)
    // Read IMU (I2C transaction)
    // Update Servo angle based on IMU
    // Write to LCD (I2C transaction)
    // Send UART debug info
}
```

Does this work? What should I change?

[Paste your integration code and describe your timing measurements]
```

**Expected AI response:** Loop timing analysis, integration strategies, synchronization patterns, potential bottleneck identification

**Verification checklist:**
- ☐ Main loop frequency meets all timing constraints
- ☐ All sensors read with sufficient frequency
- ☐ Servo position updates smoothly
- ☐ LCD displays continuously without freezing
- ☐ No I2C contention between sensors
- ☐ System remains responsive (no lockups)

---

### Prompt 3B: System-Level Debugging & Robustness

**When to use:** Middle Step 3 (days 4-6)

```
You are a helpful tutor for embedded systems debugging.

My I2C system is mostly integrated, but I'm seeing intermittent failures.

MY OBSERVED FAILURES:
[Describe what goes wrong: LCD freezes? Sensor stops responding? Servo jitters?]
[Describe frequency: every X iterations? After Y seconds? When specific sensor reads?]

MY DEBUGGING OBSERVATIONS:

Debug Scenario 1:
- Conditions: [Describe what you were doing]
- Observation: [What happened]
- Serial output: [Any error codes or messages?]
- Hypothesis: [What do you think caused it?]

Debug Scenario 2:
- Conditions: [...]
- Observation: [...]
- Hypothesis: [...]

MY TESTING STRATEGY SO FAR:
[Describe what you've tried to isolate the problem]

MY QUESTIONS:

1. TRANSIENT FAILURES:
   - Sometimes sensor reads timeout, sometimes they work fine
   - Could this be power issues? Clock issues? I2C bus issues?
   - How do I diagnose intermittent failures?

2. ERROR RECOVERY:
   - When a sensor times out, my program should... what?
   - Retry? Use last good value? Display error? Reset I2C module?
   - How do I write graceful degradation?

3. EDGE CASES:
   - What if two I2C transactions happen simultaneously?
   - What if a sensor becomes disconnected while running?
   - What if the I2C bus gets stuck (SCL/SDA held low)?
   - How do I detect and recover from each?

4. PERFORMANCE BOTTLENECKS:
   - My loop takes [X] ms, should be [Y] ms
   - Where's the time being spent? 
   - Is I2C too slow? Is my code inefficient? Something else?
   - How do I measure where time is going?

5. RESOURCE EXHAUSTION:
   - Am I running out of memory? CPU time?
   - How do I measure stack usage, execution time?
   - What are the symptoms of resource exhaustion?

MY DEBUG CODE:
[Paste any debug prints or diagnostics you've added]

[Paste your integration code and error messages from serial output]
```

**Expected AI response:** Debugging methodology, edge case analysis, performance profiling techniques, graceful degradation strategies

**Verification checklist:**
- ☐ All transient failures diagnosed and fixed
- ☐ Error recovery strategy prevents cascading failures
- ☐ System handles sensor disconnection gracefully
- ☐ I2C bus contention resolved
- ☐ System runs reliably for extended periods (hours)
- ☐ All timing constraints met consistently

---

### Prompt 3C: Final Report & Documentation

**When to use:** Late Step 3 (days 7-9)

```
You are a helpful tutor for technical writing.

I'm writing the final report for the I2C system project.

MY REPORT OUTLINE:
1. Introduction (project overview, objectives)
2. Requirements (hardware constraints, specifications, I2C design decisions)
3. System Design (module architecture, data flow, timing analysis)
4. Implementation (sensor initialization, I2C transactions, error handling)
5. Integration (multi-module synchronization, system testing)
6. Results (verification that system meets requirements)
7. Conclusion

MY QUESTIONS:

QUESTION 1: COMPLETENESS
- Are there required sections I'm missing?
- Should I add a "Lessons Learned" or "Challenges Overcome" section?
- Should I add a "Future Improvements" section?

QUESTION 2: TECHNICAL DEPTH
- How detailed should the design explanation be?
- Should I include timing diagrams? Circuit diagrams? I2C signal captures?
- Should I include code listings? How much code?
- What about sensor datasheets—should I reference or summarize?

QUESTION 3: REQUIREMENTS VERIFICATION
- How do I show that my system actually meets the requirements?
- Should I create a requirements traceability matrix?
- Should I describe test cases that verify each requirement?

QUESTION 4: DESIGN DOCUMENTATION
- For the I2C bus design: what should I document?
  * Clock frequency choice and rationale?
  * Slave address assignments?
  * Pull-up resistor calculation?
  * All of the above?

- For module architecture: what should I document?
  * Function signatures (what goes in/out)?
  * State machines?
  * Data structures?
  * API documentation?

QUESTION 5: FIGURES & DIAGRAMS
- What diagrams are essential?
  * I2C bus block diagram (showing devices)?
  * Module interaction diagram?
  * Timing diagram?
  * State machine for main loop?
  * All of above?

QUESTION 6: RESULTS & VERIFICATION
- How do I demonstrate my system works?
  * Serial terminal screenshots?
  * Video of servo moving and LCD updating?
  * Performance measurements?
  * What evidence is most convincing?

MY CURRENT DRAFT:
[Paste your introduction and one complete section]

Help me create a PROFESSIONAL, COMPLETE, CONVINCING final report that clearly 
demonstrates how my design meets every requirement.

[Paste your outline and 1-2 draft sections]
```

**Expected AI response:** Structure suggestions, emphasis areas, visual organization, completeness feedback

**Verification checklist:**
- ☐ Report includes all required sections
- ☐ Design choices are clearly explained and justified
- ☐ Requirements traceability is demonstrated
- ☐ All modules and integration are well-documented
- ☐ Test results clearly show system meets specifications
- ☐ Report is professionally written and organized

---

## Important Reminders

### When to Use AI Tutoring
- You're stuck on a concept (not just the answer)
- You need to understand tradeoffs between designs
- You want feedback on your approach before implementing
- You need help debugging a specific problem
- You're thinking through edge cases
- You need verification that your design is sound

### When NOT to Use AI
- You ask AI to write code for you
- You ask AI to give you the answer without explaining
- You copy AI output without understanding it
- You use AI to avoid thinking through the problem
- You submit AI-generated content as your own work

### What Makes Good Tutoring Prompts
✅ Specific (not vague)  
✅ Context (show your work/design/code)  
✅ Questions (ask for help thinking, not just answers)  
✅ Honest (tell AI what you've already tried)  
✅ Reflective (use AI to verify YOUR thinking, not replace it)

### Red Flags
❌ "Just tell me the answer"  
❌ "Write code that does X"  
❌ Asking for the same thing twice  
❌ Not reading AI's response carefully  
❌ Using AI responses you don't understand

---

*Copyright © 2026, Computer Engineering Department, California State University, Long Beach.*  
*Author: Dr. Min He*  
*This document is for educational use in CECS 447 Final Project, April 20 — May 13, 2026.*