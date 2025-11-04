import serial
import json
import time
import matplotlib.pyplot as plt
from datetime import datetime

# === CONFIGURATION ===
PORT = "COM8"
BAUDRATE = 115200

def main():
    temperatures = []
    timestamps = []

    plt.ion()  # enable interactive mode
    fig, ax = plt.subplots(figsize=(8, 5))
    line, = ax.plot([], [], 'r-', label="Temperature [°C]")
    ax.set_xlabel("Time [s]")
    ax.set_ylabel("Temperature [°C]")
    ax.set_title("Dynamic Temperature Response")
    ax.grid(True)
    ax.legend()

    print(f"Opened {PORT} at {BAUDRATE} baud.")
    start_time = time.time()

    with serial.Serial(PORT, BAUDRATE, timeout=2) as ser:
        # Prepare and send command (D000–D100)
        cmd = "D050"
        ser.write(cmd.encode('ascii'))
        print(f"Sent: {cmd}")
        try:
            while True:
                # read until '\r'
                line_bytes = ser.read_until(b'\r')
                line_str = line_bytes.decode('ascii', errors='ignore').strip()
                if not line_str:
                    continue

                try:
                    data = json.loads(line_str)
                    temperature = float(data["temperature"])
                    t = time.time() - start_time

                    temperatures.append(temperature)
                    timestamps.append(t)

                    # update live plot
                    line.set_xdata(timestamps)
                    line.set_ydata(temperatures)
                    ax.relim()
                    ax.autoscale_view()
                    plt.pause(0.1)

                    print(f"t={t:.1f}s | Temperature={temperature:.3f}°C")

                except Exception as e:
                    print(f"Error parsing line: {line_str} | {e}")

        except KeyboardInterrupt:
            print("\nMeasurement stopped by user.")
            pass

    # === SAVE FINAL PLOT ===
    plt.ioff()
    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    filename = f"Temperature_Dynamic_Response_{timestamp}.png"
    plt.savefig(filename, dpi=300)
    print(f"Saved figure as: {filename}")

    plt.show()

if __name__ == "__main__":
    main()
