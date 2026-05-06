# src/ – Source Code Structure

This folder contains all firmware source code for the Embedded Systems Project.

The structure follows a layered embedded architecture model to promote modular design, clean separation of concerns, and professional development practices.

---

# 📁 Folder Structure

```
src/
├── main.c
├── ModuleTest.c
├── startup.s
├── tm4c123gh6pm.h
│
├── modules/
│   ├── module_example.c
│   ├── module_example.h
│   └── ...
│
└── drivers/
    ├── driver_example.c
    ├── driver_example.h
    └── ...
```


# 🏗 Layered Architecture Overview

The source code is organized into three layers:


---

# 🔹 main.c

`main.c` is the system entry point.

Responsibilities:

- System initialization
- Calling module initialization functions
- Running main loop or scheduler
- Switching between:
  - Module test mode (Step 3)
  - Full system integration mode (Step 4)

This file represents the **integration layer** of the system.

---

# 🔹 ModuleTest.c

`ModuleTest.c` contains:

- All module-level test functions
- Test harness logic
- Calls to individual module test cases

This file is used during:

- **Step 3 – Module Implementation & Testing**

Important:

- Test code must NOT be placed inside module `.c` files.
- Production modules must remain clean and test-independent.

Example structure:


---

# 🔹 modules/ (Application Layer)

This folder contains:

- Application logic
- Feature implementation
- State machines (FSM)
- Control logic
- System behavior decisions

Modules:

- May call drivers
- Must NOT directly manipulate hardware registers
- Must have clearly defined responsibilities
- Must follow single-responsibility principle

Example responsibilities:

- Sensor processing
- Control FSM
- Display formatting
- Communication protocol handling

---

# 🔹 drivers/ (Hardware Abstraction Layer)

This folder contains:

- Low-level hardware interaction
- GPIO control
- ADC reads
- UART configuration
- Timer setup
- Interrupt handling

Drivers:

- Directly interact with microcontroller registers
- Must NOT implement application logic
- Must remain reusable and hardware-focused

Rule:

If the code touches a register → it belongs in `drivers/`.

---

# 🔹 startup.s

This file contains:

- Interrupt vector table
- Reset handler
- Low-level MCU startup initialization

This is part of the microcontroller layer and should not be modified unless necessary.

---

# 🔹 tm4c123gh6pm.h

This is the device-specific header file for the TM4C123GH6PM microcontroller.

It provides:

- Register definitions
- Peripheral addresses
- Bit field definitions

This file supports low-level driver development.

---

# 🔍 Development Workflow Alignment

Step 3 – Module Testing:
- Implement modules inside `modules/`
- Write test functions in `ModuleTest.c`
- Store test evidence in `evidence/Step3_ModuleTests`

Step 4 – Integration:
- Integrate modules via `main.c`
- Validate full system behavior
- Perform robustness testing
- Document system-level traceability

---

# 📌 Important Rules

- Do NOT mix driver code with application logic.
- Do NOT place test code inside production modules.
- Maintain clean separation between layers.
- Follow naming conventions consistently.
- Keep code readable and modular.

---

# 🏭 Industry Alignment

This structure mirrors professional embedded firmware repositories used in:

- Automotive systems
- Medical devices
- Industrial controllers
- Aerospace firmware

Maintaining this structure improves:

- Testability
- Maintainability
- Debugging clarity
- Integration stability
