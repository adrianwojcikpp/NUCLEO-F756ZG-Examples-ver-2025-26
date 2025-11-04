import serial
import json
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
from collections import deque

# --- Serial Configuration ---
PORT = 'COM8'
BAUDRATE = 115200

# --- Plot Configuration ---
WINDOW_SIZE = 100  # number of points to show on screen

# --- Data Buffer ---
x_data = deque(maxlen=WINDOW_SIZE)
y_data = deque(maxlen=WINDOW_SIZE)
counter = 0

# --- Open Serial Port ---
ser = serial.Serial(PORT, BAUDRATE, timeout=0.1)
print(f"Listening on {PORT} at {BAUDRATE} baud...")

# --- Setup Plot ---
plt.style.use('ggplot')
fig, ax = plt.subplots()
line, = ax.plot([], [], lw=2, color='blue')
ax.set_title("Real-time Counter Plot")
ax.set_xlabel("Sample")
ax.set_ylabel("Counter Value")
ax.set_xlim(0, WINDOW_SIZE - 1)
ax.set_ylim(-20, 420)

def update(frame):
    global counter
    try:
        line_bytes = ser.read_until(b'\r').decode('utf-8', errors='ignore').strip('\r\n')
        if not line_bytes:
            return line,

        # Expect a JSON line like: { "counter" : 123 }
        data = json.loads(line_bytes)
        if "encoder" in data:
            counter += 1
            x_data.append(counter)
            y_data.append(float(data["encoder"]))

            line.set_data(range(len(y_data)), y_data)
            ax.relim()
            ax.autoscale_view()
            
    except (json.JSONDecodeError, UnicodeDecodeError):
        pass  # skip bad lines silently
    except Exception as e:
        print(f"Error: {e}")
    return line,

ani = FuncAnimation(fig, update, interval=10, blit=True)
plt.show()

# --- Close serial on exit ---
ser.close()
