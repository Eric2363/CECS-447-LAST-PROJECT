[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ugkGcOub)
[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=23650098)
# Embedded Systems Project Starter Repository

This repository follows the **3-Step Embedded Systems Workflow**.

⚠️ DO NOT modify the folder structure.

---

# 🔄 3-Step Workflow Overview

Step 1 → Requirements & System Design  
Step 2 → Module Design & Implementation  
Step 3 → Integration, Validation & Final Submission  

---

# 📁 Complete Folder Structure

```
Project-Name/

├── README.md
├── .gitignore
├── CECS447_Final_Project_I2C_Bus_Communication.md

├── Student Support/
│ ├── README.md
│ └── CECS447_FINAL_PROJECT_TUTORING_PROMPTS.md

├── keil/
│ └── README.md

├── docs/
│ ├── Step1_Requirements.md
│ ├── Step2_Module_Design.md
│ ├── Step3_Integration_Report.md
│ ├── TRACEABILITY.md
│ ├── traceability.csv
│ ├── ai_log_summary.csv
│ ├── ai_log_summary_examples.csv
│ └── AI_Log.md

├── src/
│ ├── main.c
│ ├── ModuleTest.c
│ ├── startup.s
│ ├── tm4c123gh6pm.h
│ ├── modules/
│ │ ├── module1_features.c
│ │ └── module1_features.h
│ └── drivers/
│ ├── module1_driver.c
│ └── module1_driver.h

├── evidence/
│ ├── Step2_ModuleTests/
│ │ └── README.md
│ └── Step3_SystemTests/
│ └── README.md

├── report/
│ └── Project_Report.md

└── .github/
└── workflows/
└── traceability-autograde.yml
```

---

# 📚 Student Support

The `Student Support/` directory provides **AI tutoring resources** to help you work through each step of the project effectively.

📄 Files:
- `Student Support/CECS447_FINAL_PROJECT_TUTORING_PROMPTS.md` — Ready-to-use tutoring prompts (organized by Step 1, 2, and 3) that you can paste into ChatGPT or Claude to get structured guidance
- `Student Support/README.md` — Overview of the support resources

⚠️ Important:
- These prompts are **guides**, not answers — you must do the engineering reasoning yourself
- All AI interactions must still be logged in `docs/AI_Log.md`
- See the [AI Usage Policy](#-ai-usage-policy) below for allowed vs. not allowed AI use

---

# 🔹 Step 1 – Requirements & System Design

What you must do:

- Define functional requirements (RQ-##)
- Identify constraints (CN-##)
- Develop system design:
  - Hardware plan (pins, peripherals, components)
  - Software modules (high-level structure)
- Justify your design decisions

📄 Files:
- `docs/Step1_Requirements.md`
- `docs/AI_Log.md`

---

# 🔹 Step 2 – Module Design & Implementation

What you must do:

- Break system into independent modules
- Implement each module in `/src/modules/`
- Implement hardware drivers in `/src/drivers/`
- Test each module (at least 1 valid test)
- Save evidence in `/evidence/Step2_ModuleTests/`
- Complete traceability table

📄 Files:
- `docs/Step2_Module_Design.md`
- `docs/traceability.csv`

⚠️ Critical Rule:
- ❌ NO integration allowed until all modules pass testing

---

# 🔹 Step 3 – Integration, Validation & Final Submission

What you must do:

### Integration
- Combine modules into a complete system
- Define and explain integration order

### Validation
- Create:
  - Call graph
  - Data flow diagram
- Perform at least one robustness test
- Complete system-level validation

### Documentation
- Write CER (Claim–Evidence–Reasoning)
- Link all evidence

### Final Submission
- Demo your system (video or live)
- Submit code + report

📄 Files:
- `docs/Step3_Integration_Report.md`
- `report/Project_Report.md`

📁 Evidence:
- `/evidence/Step3_SystemTests/`

---

# 🔗 Traceability Requirement (VERY IMPORTANT)

You must maintain:

```
Requirement → Module → Test → Evidence
```

- Stored in: `docs/traceability.csv`
- Every requirement must have:
  - Implementation
  - Test
  - Evidence

This ensures:
- Clear grading  
- Strong engineering reasoning  
- Complete validation  

---

# 🤖 AI Usage Policy

## ✅ Allowed:
- Debugging code
- Verifying results
- Improving writing clarity

## ❌ Not Allowed:
- Generating production code
- Writing full reports

⚠️ All AI usage must be documented in:
```
docs/AI_Log.md
```

---

# 🔧 Important Rules

- Write your own code
- Keep modules and drivers separate
- Keep evidence organized
- Do NOT rename or delete folders
- Follow the module-first testing rule
- Maintain traceability at all times

---

# 🏗 Workflow Logic

```
Step 1 → Define system
Step 2 → Build & test modules
Step 3 → Integrate & validate system
```

---

# 🏭 Industry Alignment

This workflow mirrors real embedded systems development:

- Requirements & Design  
- Modular Implementation  
- Unit Testing  
- System Integration  
- Validation & Demonstration  

---

# 🎯 Key Success Tips

- Start early  
- Test modules BEFORE integrating  
- Keep everything organized  
- Link all evidence clearly  
- Keep designs simple and clear  

---

This repository represents your **complete engineering process**, not just your final code.
