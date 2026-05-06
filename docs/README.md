# docs/ – Project Documentation Folder

This folder contains all documentation required for the **3-Step Embedded Systems Workflow**.

Each file corresponds directly to one phase of the engineering process.  
Do not rename or delete these files.

---

# 📁 Documentation Structure

```
docs/
├── AI_Log.md
├── Step1_Requirements.md
├── Step2_Module_Design.md
├── Step3_Integration_Report.md
├── traceability.csv
```

---

# 🔄 Workflow Mapping

| Workflow Step | File |
|---------------|------|
| Step 1 – Requirements & System Design | `Step1_Requirements.md` |
| Step 2 – Module Design & Implementation | `Step2_Module_Design.md`, `traceability.csv` |
| Step 3 – Integration & Validation | `Step3_Integration_Report.md` |
| AI Usage Tracking | `AI_Log.md` |

---

# 🔹 File Descriptions

## Step1_Requirements.md

Contains:

- Functional requirements (RQ-##, clear and testable)
- System constraints (CN-##: timing, memory, hardware limits)
- High-level system design (hardware + software modules)
- Design justification
- AI verification summary

This is equivalent to an industry **System Requirements & Design Specification**.

---

## Step2_Module_Design.md

Contains:

- Module decomposition (clear responsibilities)
- Inputs and outputs for each module
- Implementation summary
- Module testing description

Students must:

- Implement each module
- Perform at least **1 valid test per module**
- Save evidence in `/evidence/Step2_ModuleTests/`

---

## traceability.csv

Contains the **traceability table (RTM)**:

```
Requirement → Module → Test → Evidence
```

Each row must clearly answer:

- What is required?
- Where is it implemented?
- How is it verified?

This ensures:
- Clear grading
- Strong engineering reasoning
- Evidence-based validation :contentReference[oaicite:0]{index=0}  

---

## Step3_Integration_Report.md

Contains:

- Integration order and reasoning
- Final call graph
- Data flow diagram
- System-level validation

Includes:

- System-level traceability (Requirement → Test → Evidence)
- Robustness test (edge/unexpected condition)
- CER (Claim–Evidence–Reasoning)
- Final demo summary
- AI verification summary

This reflects an industry **System Integration & Validation Report**.

---

## AI_Log.md

Tracks:

- All AI usage (prompt → output → verification)
- What was accepted or rejected
- Debugging assistance

AI Policy Reminder:

- ✅ Allowed: debugging, verification, documentation improvement  
- ❌ Not allowed: generating production code  

---

# ⚠️ Key Workflow Rules

## 🔒 Module-First Rule
- You MUST complete and test all modules before integration  
- No partial integration allowed  

## 🧪 Evidence Rule
- Every requirement must have test evidence  
- Evidence must be stored in `/evidence/`  

## 🔗 Traceability Rule
- Every requirement must map to:
  - A module  
  - A test  
  - Evidence  

---

# 🏗 Industry Alignment

This workflow mirrors real embedded systems development:


Requirements → Modules → Testing → Integration → Validation


Key professional practices:

- Traceability from requirement → test evidence  
- Independent module verification before integration  
- Evidence-based reasoning (CER)  
- Structured documentation  

---

# 📌 Important Rules

- Keep documentation clear and concise  
- Do NOT include source code in `/docs`  
- Keep evidence organized and properly named  
- Update traceability when changes occur  

---

This folder represents the **engineering thinking behind your system**, not just the final result.
