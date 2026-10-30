# DYNAMIC MEMORY MANAGEMENT PROJECTS IN C

## Project Index & File Layout

```text
.
├── Academic-Performance/
│   └── main.c               # Student performance & Academic Risk Index engine
├── IoT_Event_Monitoring/
│   └── monitoring.c                 # IoT sensor simulation & callback engine
└── Mining-Analyzer/
    └── mining.c                 # Text mining & word frequency analyzer 
```
----
### 1. Dynamic Text Mining & Linguistic Pattern Analyzer

**Purpose:** Parses raw text, tracks distinct word counts, and calculates vocabulary metrics using: Lexical Diversity Score = (Distinct Words / Total Words) * 100

**Key Features:**

- Tokenizes text and removes non-alphabetic characters.

- Dynamic memory allocation (malloc, realloc) for storing unique word frequency structs.

- Quicksort (qsort) sorting and custom word search.

**Real-World Application:** Text classification engines, document summarization tools, and natural language processing pipelines.

----
### 2. Dynamic Academic Performance & Risk Analysis Engine

**Purpose:** Manages dynamic student records and evaluates academic risk level based on grades.

**Classification:**

*Low Risk:* Grade >= 65

*Moderate Risk:* 50 <= Grade < 65

*High Risk:* Grade < 50

**Real-World Application:** Student management systems and automated academic performance tracking software in educational institutions.

----
### 3. Dynamic IoT Event Monitoring & Callback Engine

**Purpose:** Simulates IoT sensors (Temperature, Pressure, Battery) and processes readings using callback function pointers.

**Classification:**

*Temperature:* Normal range 0.0°C to 50.0°C

*Pressure:* Normal range 20 PSI to 100 PSI

*Battery Voltage:* Normal range >= 3.3V

*Sensor Drift (Custom Callback):* Triggers alert if reading shifts by > 15.0 units from previous value.

**Real-World Application:** Embedded microcontrollers, industrial telemetry monitoring systems, and automated anomaly detection platforms.

----
### HOW TO RUN THIS
Clone this repo
```text
git clone https://github.com/nIgihozo/Project-2_Assignment.git
```
**Note:** Make sure you have all the dependincies for C for you to be able to run.