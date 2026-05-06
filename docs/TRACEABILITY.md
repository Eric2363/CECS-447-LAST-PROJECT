# CECS 447 — I2C Bus Communication System
## Requirements Traceability Matrix

**Course:** CECS 447 Senior Embedded Systems  
**Team:** Jackie Huynh & Min He  
**Duration:** April 20 – May 13, 2026  
**Workflow:** 3-Step (Requirements → Modules → Integration)

---

## 📌 Student Instructions

> **One completed example row is provided in each section.**  
> Study the example carefully, then fill in **all remaining rows** for your project.
>
> - Replace every `[Fill in]` placeholder with real values from your implementation.
> - Update the **Status** column as you progress: 🔴 Not Started → 🟡 In Progress → 🟢 Done.
> - Add your evidence file path once you collect test results.
> - Do **not** modify the ⭐ example rows — they are reference entries.

---

## Quick Navigation

| Section | Example Row | Rows to Complete |
|---------|-------------|-----------------|
| [🔵 Functional Requirements (RQ)](#-functional-requirements-rq) | ⭐ RQ-01 | RQ-02 through RQ-20 (19 rows) |
| [🟡 Constraints (CN)](#-constraints-cn) | ⭐ CN-01 | CN-02 through CN-03 (2 rows) |
| [🟣 Design Decisions (DES)](#-design-decisions-des) | ⭐ DES-01 | DES-02 (1 row) |
| [🔴 System / Acceptance (SYS)](#-system--acceptance-sys) | ⭐ SYS-01 | SYS-02 (1 row) |
| [📋 Module Dashboard](#-module-dashboard) | ⭐ Module 1 | Modules 2–9 (update Status only) |
| [📖 Legend](#-legend) | — | — |

---

## Step Structure

| Columns | Workflow Step | Dates |
|---------|--------------|-------|
| Req ID · Type · Requirement | **Step 1** — Requirements & System Design | Apr 20–22 |
| Spec Ref · Module · Assigned · Mod TC | **Step 2** — Module Design & Implementation | Apr 23 – May 4 |
| Int TC · Sys TC · Evidence · Status · CER · Notes | **Step 3** — Integration, Validation & Submission | May 5–13 |

---

## 🔵 Functional Requirements (RQ)

> Something the system **must do**. All RQ items require implementation, a module test, and evidence.  
> ⭐ **RQ-01 is the example row. Fill in RQ-02 through RQ-20.**

| Req ID | Requirement / Constraint | Spec § | Module (file : function) | Assigned | Mod TC | Int TC | Sys TC | Evidence | Status | CER Claim | Notes / Risks |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| ⭐ `RQ-01` | WTIMER_Init() initialises 32-bit wide timer (WTIMER1–5, student choice) for 1 ms delay resolution | §5.1 | `wtimer.c : WTIMER_Init` | Jackie | `TC-MOD-001` | `TC-INT-010` | `TC-SYS-001` | `evidence/TC-MOD-001_timer_init.png` | 🔴 Not Started | Timer initialises without error; 1 ms delay confirmed by oscilloscope | WTIMER0 not allowed; student must choose WTIMER1–5. |
| `RQ-02` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-03` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-04` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-05` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-06` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-07` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-08` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-09` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-10` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-11` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-12` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-13` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-14` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-15` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-16` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-17` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-18` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-19` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `RQ-20` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [TC-MOD-???] | [TC-INT-???] | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |

---

## 🟡 Constraints (CN)

> Rules the design **must obey** — timing, process gates, hardware restrictions.  
> ⭐ **CN-01 is the example row. Fill in CN-02, CN-03.**

| Req ID | Requirement / Constraint | Spec § | Module (file : function) | Assigned | Mod TC | Int TC | Sys TC | Evidence | Status | CER Claim | Notes / Risks |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| ⭐ `CN-01` | Sensor sampling runs every 100 ms; LCD & UART output runs every 1 s (±100 ms) | §6.2 | `app.c : Main_Loop` | Both | `TC-MOD-021` | `TC-INT-024` | `TC-SYS-008` | `evidence/TC-MOD-021_timing.png` | 🔴 Not Started | Loop timer confirms 100 ms sample and 1 s output cadence | Use student-chosen WTIMER counter (not WTIMER0); do NOT busy-wait. |
| `CN-02` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [CR-???] | [TC-INT-???] | — | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |
| `CN-03` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | [CR-???] | [TC-INT-???] | — | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |

---

## 🟣 Design Decisions (DES)

> Architectural choices made in **Step 1**, justified and documented.  
> ⭐ **DES-01 is the example row. Fill in DES-02.**

| Req ID | Requirement / Constraint | Spec § | Module (file : function) | Assigned | Mod TC | Int TC | Sys TC | Evidence | Status | CER Claim | Notes / Risks |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| ⭐ `DES-01` | Multiple I2C device designs considered; single-bus shared SDA/SCL chosen with external pull-ups | §2.1, Workflow §1 | `i2c.c; hardware schematic` | Both | — | — | — | `evidence/DES-001_design_decision.pdf` | 🔴 Not Started | Shared bus minimises GPIO use; 4.7 kΩ pull-ups meet Standard Mode rise-time spec | Document trade-offs vs software I2C or separate buses. |
| `DES-02` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | — | — | — | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |

---

## 🔴 System / Acceptance (SYS)

> End-to-end tests that validate the **complete integrated system**.  
> ⭐ **SYS-01 is the example row. Fill in SYS-02.**

| Req ID | Requirement / Constraint | Spec § | Module (file : function) | Assigned | Mod TC | Int TC | Sys TC | Evidence | Status | CER Claim | Notes / Risks |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| ⭐ `SYS-01` | Full system initialises all 7 modules, detects all 3 I2C devices, and enters main loop without hang | §6.2 | `app.c : main()` | Both | — | — | `TC-SYS-009` | `evidence/TC-SYS-009_full_init.mp4` | 🔴 Not Started | UART log shows all 'OK' messages and loop starts within 3 s of power-on | Failure of any sensor init should print diagnostic; student-chosen peripherals must all initialise. |
| `SYS-02` | [Fill in requirement description from spec] | [§X.X] | [file.c : Function] | [Name] | — | — | [TC-SYS-???] | [evidence/path] | 🔴 Not Started | [CER claim] | [Notes / risks] |

---

## 📋 Module Dashboard

> Gate check: all modules must reach **🟢 Done** before Step 3 integration begins (CN-02).  
> ⭐ **Module 1 is the example row. Update the Status column for Modules 2–9 as you complete each test.**

| # | Module | File(s) | Assigned | Test IDs | Test Type | Status | Gate |
|---|--------|---------|----------|----------|-----------|--------|------|
| ⭐ `1` | Wide Timer (WTIMER1–5, student choice) | `wtimer.c` | Jackie | TC-MOD-001–004 | Unit | 🔴 Not Started | Step 2 |
| `2` | UART0 Serial Communication (baud ≠ 57600) | `uart0.c` | Min | TC-MOD-005–007 | Unit | 🔴 Not Started | Step 2 |
| `3` | I2C Bus Communication (I2C1–3, student choice) | `i2c.c` | Jackie | TC-MOD-008–010 | Unit | 🔴 Not Started | Step 2 |
| `4` | TCS34725 Color Sensor | `tcs34725.c` | Min | TC-MOD-011–012 | Unit | 🔴 Not Started | Step 2 |
| `5` | MPU6050 IMU | `mpu6050.c` | Jackie | TC-MOD-013–015 | Unit | 🔴 Not Started | Step 2 |
| `6` | 16×2 LCD Display | `lcd.c` | Min | TC-MOD-016–017 | Unit | 🔴 Not Started | Step 2 |
| `7` | Servo PWM Control (M0PWM1–7 or M1PWM0–7) | `pwm.c` | Jackie | TC-MOD-018–020 | Unit | 🔴 Not Started | Step 2 |
| `—` | Full System Integration | `app.c` + all modules | Both | TC-INT-010–025 | Integration | 🔴 Not Started | Step 3A |
| `—` | System Validation | all modules | Both | TC-SYS-001–010 | System | 🔴 Not Started | Step 3B |

---

## 📖 Legend

### Req ID Prefix & Row Type

| Prefix | Type | Row colour | Meaning |
|--------|------|------------|---------|
| `RQ-xx` | Functional | 🟩 Green | Something the system must do |
| `CN-xx` | Constraint | 🟨 Yellow | Design, timing, hardware, or process rule |
| `DES-xx` | Design | 🟪 Purple | Architectural or implementation choice |
| `SYS-xx` | System | 🟥 Red | End-to-end or integration-level requirement |

### Row Appearance

| Style | Meaning |
|-------|---------|
| ⭐ Amber border (in Excel) | Example row — provided by instructor; **do not modify** |
| 🟨 Yellow background (in Excel) | Student row — fill in every `[Fill in]` placeholder |

### Status Icons

| Icon | Meaning |
|------|---------|
| 🔴 Not Started | Work not yet begun |
| 🟡 In Progress | Implementation underway |
| 🟢 Done | Evidence collected and verified |

### Test ID Naming Convention

| Prefix | Scope | Step |
|--------|-------|------|
| `TC-MOD-xxx` | Module-level unit test | Step 2 |
| `TC-INT-xxx` | Integration test | Step 3, Phase A |
| `TC-SYS-xxx` | System / acceptance test | Step 3, Phase B |
| `CR-xxx` | Constraint review / inspection | Step 2 or 3 |
| `CMP-xxx` | Comparison / design-decision evidence | Step 1 |

### Column Band → Workflow Step

| Columns | Step |
|---------|------|
| Req ID · Type · Requirement | Step 1 — Requirements & System Design (Apr 20–22) |
| Spec Ref · Module · Assigned · Mod TC | Step 2 — Module Design & Implementation (Apr 23 – May 4) |
| Int TC · Sys TC · Evidence · Status · CER · Notes | Step 3 — Integration, Validation & Submission (May 5–13) |

---

*CECS 447 Final Project — I2C Bus Communication System. For questions contact Jackie Huynh or Dr. Min He.*
