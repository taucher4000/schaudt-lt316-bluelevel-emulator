**[🇩🇪 Deutsche Version der Beschreibung](README_DE.md)**

# ESP32 Water Tank Sensor Emulator for Schaudt LT 316

This project emulates a standard 5-pin water tank probe for the [Schaudt LT 316](https://www.schaudt.gmbh) display panel. It allows you to replace the original mechanical rod probe with a modern, high-precision **contactless laser sensor (ToF)** like the [BlueLevel+](https://www.blue-battery.com/product-page/bluelevel).

## The Problem
Original motorhome water tanks (e.g., Knaus/Weinsberg) use simple rod probes. The Schaudt LT 316 panel detects the water level by checking which rods are shorted to ground by the water. Modern laser sensors like the BlueLevel+ output a voltage signal (0–2.5V), which is incompatible with the resistance-based Schaudt display.

## The Solution
An **ESP32** (running on an [LC-Relay-ESP32-4R-A2 board](https://amzn.eu/d/3VqQObJ)) reads the analog 0–2.5V signal from the laser sensor and converts it into four discrete levels. The on-board relays act as switches to simulate the water rods for the Schaudt panel, providing a seamless and precise integration.

![LC-Relay-ESP32-4R-A2 Board Layout](LC-Relay-ESP32-4R-A2.PNG)

## Hardware Requirements
*   **Microcontroller:** ESP32 (Form factor: [LC-Relay-ESP32-4R-A2](https://amzn.eu/d/3VqQObJ))
*   **Sensor:** [BlueLevel+](https://www.blue-battery.com/product-page/bluelevel) (Contactless Laser/ToF, 0V = Empty, 2.5V = Full)
*   **Power Supply:** 12V DC from the motorhome board net.
*   **Programming:** [FTDI USB-to-TTL Adapter](https://amzn.eu/d/bBN6eX9) (set to 3.3V for data).
*   **Housing:** A 3D-printed housing from [thingiverse](https://www.thingiverse.com/thing:7095873) was used. However, any other housing can also be used.

## Wiring
1.  **Sensor:** Connect BlueLevel+ signal output (0-2.5V) to **GPIO 34**.
2.  **Relays (to Schaudt Panel):**
    *   Connect all **COM** (Common) terminals to the Schaudt panel's GND.
    *   Connect the **NO** (Normally Open) terminals to the corresponding level pins (25%, 50%, 75%, 100%) on the Schaudt input.

## How to Flash
1.  Install the [ESP32 Core for Arduino](https://https://github.com/espressif/arduino-esp32/releases).
2.  Connect the FTDI adapter (TX to RX, RX to TX, GND to GND).
3.  Hold the **IO0** button, press **Reset**, and release **IO0** to enter download mode.
4.  Upload the code using the [Arduino IDE](https://www.arduino.cc) (Board: "ESP32 Dev Module").
