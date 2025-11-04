import serial
import time
import json
import matplotlib.pyplot as plt
from datetime import datetime

# === CONFIGURATION ===
PORT = "COM8"
BAUDRATE = 115200
STEPS = 101
DELAY = 0.2  # seconds between measurements

def main():
    duty_cycles = []
    illuminance_values = []

    # Open serial port
    with serial.Serial(PORT, BAUDRATE, timeout=2) as ser:
        print(f"Opened {PORT} at {BAUDRATE} baud.")
        time.sleep(2)  # Give device time to initialize

        for duty in range(STEPS):
            # Prepare and send command (D000–D100)
            cmd = f"D{duty:03d}"
            ser.write(cmd.encode('ascii'))
            print(f"Sent: {cmd}")
            
            # Wait for system response to settle
            time.sleep(DELAY)
            
            # Request measurement
            ser.write(b"READ")
            
            # Read until '\r' is found
            line = ser.read_until(b'\r').decode('ascii').strip()
            line = line.replace(" ", "")
            print(f"Received: {line}")

            try:
                # Parse JSON data
                data = json.loads(line)
                illum = float(data["illuminance"])
                duty_cycles.append(duty)
                illuminance_values.append(illum)
            except Exception as e:
                print(f"Error parsing response: {e}")
                duty_cycles.append(duty)
                illuminance_values.append(None)

    # === PLOT RESULTS ===
    plt.figure(figsize=(8, 5))
    plt.plot(duty_cycles, illuminance_values, marker='o', linestyle='-')
    plt.title("System Static Characteristic")
    plt.xlabel("Duty Cycle (%)")
    plt.ylabel("Illuminance (lux)")
    plt.grid(True)

    # Save figure with current date and time
    timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
    filename = f"Duty_vs_Illuminance_{timestamp}.png"
    plt.savefig(filename, dpi=300)
    print(f"\nSaved figure as: {filename}")

    plt.show()

if __name__ == "__main__":
    main()
