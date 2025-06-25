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

```mermaid
flowchart TD
    EngineECU[Engine ECU (TMP36 + RPM)]
    ClimateECU[Climate ECU (Fan LED)]
    DiagnosticECU[Diagnostic ECU (Logger)]

    CANBus[CAN Bus MCP2515]
    TCPIP[TCP/IP Connection]

    Flask[Flask Backend]
    Dashboard[Web Dashboard (localhost:5000)]

    EngineECU -->|CAN| CANBus
    ClimateECU -->|CAN| CANBus
    DiagnosticECU -->|CAN| CANBus

    DiagnosticECU -->|TCP| TCPIP --> Flask -->|WebSocket| Dashboard


