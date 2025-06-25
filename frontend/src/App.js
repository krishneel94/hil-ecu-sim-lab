// src/App.js
import { useState, useEffect } from 'react';

export default function App() {
  const [rpm, setRpm] = useState(0);
  const [temp, setTemp] = useState(0);
  const [fanStatus, setFanStatus] = useState('OFF');
  const [clicks, setClicks] = useState(0);

  useEffect(() => {
    const socket = new WebSocket('ws://localhost:5000/ws');

    socket.onmessage = (event) => {
      const data = JSON.parse(event.data);
      if (data.type === 'status') {
        setRpm(data.rpm);
        setTemp(data.temp);
        setFanStatus(data.fan);
      }
    };

    return () => socket.close();
  }, []);

  return (
    <main className="min-h-screen bg-black text-white p-4 max-w-md mx-auto font-sans">
      <header className="flex items-center mb-6">
        <img src="https://cdn-icons-png.flaticon.com/512/743/743007.png" alt="Car Logo" className="h-10 w-10 mr-3" />
        <h1 className="text-2xl font-bold">ECU Status Dashboard</h1>
      </header>

      <div className="mb-4">Developed by <span className="text-blue-400 font-semibold">Krishneel Sahdeo</span></div>

      <div className="bg-gray-800 p-4 rounded mb-4">
        <div className="mb-2">RPM: <span className="font-mono text-yellow-400">{rpm}</span></div>
        <div className="mb-2">Coolant Temp: <span className="font-mono text-yellow-400">{temp} °C</span></div>
        <div className="mb-2">Fan: <span className={`font-bold ${fanStatus === 'ON' ? 'text-green-500' : 'text-red-500'}`}>{fanStatus}</span></div>
      </div>

      <button
        className="mt-2 px-4 py-2 bg-blue-600 hover:bg-blue-700 text-white font-semibold rounded"
        onClick={() => setClicks(clicks + 1)}
      >
        Click Me
      </button>
      <div className="mt-2">Button Clicked: {clicks} times</div>
    </main>
  );
}

