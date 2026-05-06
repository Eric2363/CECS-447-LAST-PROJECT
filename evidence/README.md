# evidence/ – Validation & Demonstration Artifacts

This folder contains all verification and validation artifacts for the **3-Step Embedded Systems Workflow**.

Each subfolder corresponds to a stage of testing and system validation.

Do not rename these folders.

---

## 📁 Folder Structure

```
evidence/
├── Step2_ModuleTests/
└── Step3_SystemTests/
```

---

# 🔄 Workflow Mapping

| Workflow Step | Evidence Location |
|---------------|------------------|
| Step 2 – Module Design & Implementation | `Step2_ModuleTests/` |
| Step 3 – Integration & Validation | `Step3_SystemTests/` |

---

# 🔹 Step2_ModuleTests/

This folder contains evidence of **module-level testing**.

Examples:

- UART logs  
- Serial monitor output  
- Screenshots  
- Oscilloscope captures  
- Short test videos  

Purpose:

- Demonstrate that each module works independently  
- Support the **traceability table (Requirement → Module → Test)**  
- Verify at least **1 valid test per module**  

⚠️ Rule:
- All modules must pass testing **before integration is allowed**  

Industry Equivalent:

**Unit Testing / Component Verification**

---

# 🔹 Step3_SystemTests/

This folder contains **system-level validation and final demonstration evidence**.

Includes:

### ✅ Integration Evidence
- Multiple modules working together  
- Feature-level behavior  

### ✅ Robustness Testing
- Boundary conditions  
- Invalid inputs  
- Sensor failure / disconnection  
- Timing edge cases  

### ✅ Final Demo
- Full system demonstration (video or screenshots)  
- Output verification  

Purpose:

- Demonstrate full system functionality  
- Validate all requirements end-to-end  
- Support **CER (Claim–Evidence–Reasoning)**  

Industry Equivalent:

**System Validation & Acceptance Testing**

---

# 🔗 Evidence Naming Convention (VERY IMPORTANT)

Each file should match a **verification ID** used in the traceability table:

Examples:

```
TC-MOD-001_uart_output.txt
TC-MOD-002_timer_test.jpg
TC-SYS-001_full_system.mp4
TC-SYS-002_robustness_test.mp4
```

This ensures:
- Easy grading  
- Clear traceability  
- No missing evidence issues  

(Required for proper traceability mapping :contentReference[oaicite:0]{index=0})

---

# 📌 Important Rules

- Every requirement must have **linked evidence**
- Evidence must match entries in `traceability.csv`
- Keep module and system evidence **separate**
- Do NOT upload random or unused files
- Keep files clearly named and organized

---

# 🏗 Workflow Logic (How This Fits Together)

```
Step 1 → Define requirements
Step 2 → Test modules (evidence here)
Step 3 → Validate full system (evidence here)
```

---

# 🏭 Professional Alignment

This structure mirrors real embedded systems development:

```
Requirements → Unit Testing → System Validation
```

Maintaining clean evidence:

- Improves traceability  
- Simplifies grading  
- Reduces debugging confusion  
- Reinforces professional engineering practice  

---

This folder is the **proof that your system actually works**.
