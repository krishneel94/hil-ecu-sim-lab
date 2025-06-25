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

┌───────────────────────────────────────────────────────────────┐
│                       HIL ECU Sim Lab                         │
│                      (System Overview)                        │
└───────────────────────────────────────────────────────────────┘

[Engine ECU]                [Climate ECU]                [Diagnostic ECU]
   └─────┬──────┐              └─────┬──────┐               └────┬────┐
   TMP36│    RPM Pot                Fan LED                     CAN + TCP
        │                            ▲                             ▲
        ▼                            │                             │
    Simulate Temp + RPM       Turns fan ON if temp > 90°C         │
                                (receives from Engine ECU)        │
        └──────────── CAN Bus (MCP2515) ────────────────┘         │
                             SPI Interface                        │
                                  ▼                               │
                       ┌────────────────────┐                     │
                       │  ESP32 / Arduino MCUs│                    │
                       └────────────────────┘                     │
                                  ▼                               ▼
                       ┌────────────────────┐         ┌────────────────────────────┐
                       │  Python Flask Server │<──────►│  TCP Client (Diagnostic ECU)│
                       │  (Flask + SocketIO) │         └────────────────────────────┘
                       └────────────────────┘
                                  │
                          WebSockets + JSON
                                  ▼
                        ┌────────────────────┐
                        │   Web Dashboard    │
                        │  (localhost:5000)  │
                        └────────────────────┘

