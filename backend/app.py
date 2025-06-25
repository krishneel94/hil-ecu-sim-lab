from flask import Flask, send_from_directory
from flask_socketio import SocketIO
import threading
import time
import random
import os

# Setup Flask app and WebSocket
app = Flask(__name__, static_folder="../frontend")
socketio = SocketIO(app, cors_allowed_origins="*")

# Serve the index.html from the frontend folder
@app.route('/')
def index():
    return send_from_directory(app.static_folder, "index.html")

# Background thread: simulate ECU RPM/temp every 2s
def simulate_ecu_data():
    while True:
        rpm = random.randint(800, 3000)
        temp = random.randint(70, 110)
        socketio.emit("update", {"rpm": rpm, "temp": temp})
        time.sleep(2)

# Start server and background thread
if __name__ == "__main__":
    threading.Thread(target=simulate_ecu_data, daemon=True).start()
    socketio.run(app, host="0.0.0.0", port=5000)
