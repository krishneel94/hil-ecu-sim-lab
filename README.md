# HIL ECU Sim Lab

A Hardware-in-the-Loop (HIL) simulation testbench for validating automotive ECUs over **CAN**, **Ethernet**, and **TCP/IP** using Python, Arduino, and a real-time diagnostics dashboard (Flask + WebSockets). This project simulates three interacting ECUs — Engine, Climate, and Diagnostics — designed to model vehicle end-of-line (EOL) testing workflows.

---

## 🚦 Features

- 🧠 **Engine ECU** simulates RPM and coolant temperature using TMP36 + potentiometer
- ❄️ **Climate ECU** listens for coolant temp and activates a fan (LED) if overheating
- 🧪 **Diagnostics ECU** logs CAN traffic and sends TCP heartbeats to the UI backend
- 📊 **Python/Flask backend** pushes real-time sensor data via WebSockets
- 🖥️ **Live dashboard** with RPM/temp/fan status visualization
- 🛠️ Designed to be easily extended for other protocols (I2C, LIN, MQTT)

---

## 🧰 Tech Stack

- Arduino (C++) for ECU firmware
- MCP2515 CAN Bus modules for communication
- Python 3, Flask, Flask-SocketIO for backend
- HTML + JS (vanilla) for diagnostics dashboard
- Compatible with CentOS, Ubuntu, or any Linux system

---

## 📡 Architecture

```mermaid
flowchart TD
    EngineECU([Engine ECU])
    ClimateECU([Climate ECU])
    DiagnosticECU([Diagnostic ECU])
    Backend(Flask Backend)
    Dashboard(Web Dashboard)
    
    EngineECU -->|CAN| ClimateECU
    EngineECU -->|CAN| DiagnosticECU
    ClimateECU -->|CAN| DiagnosticECU
    DiagnosticECU -->|TCP/IP| Backend
    Backend -->|WebSocket| Dashboard
                        └────────────────────┘

