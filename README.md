# Dual-Axis Solar Tracker (Arduino + LDR)

## Overview
This project implements a dual-axis light tracking system using an Arduino and four LDR sensors. The system continuously adjusts two servo motors (horizontal and vertical) to align with the direction of maximum light intensity.

Unlike basic LDR trackers, this implementation includes signal smoothing, noise filtering, and proportional control for stable and accurate tracking.

---

## Features
- Dual-axis tracking (Horizontal + Vertical)
- 4-LDR sensor array for directional detection
- Moving average filtering for noise reduction
- Exponential smoothing for stable control
- Proportional step-based servo adjustment
- Fault tolerance for invalid sensor readings

---

## Hardware Required
- Arduino Uno (or compatible)
- 2x Servo Motors
- 4x LDRs (Light Dependent Resistors)
- Resistors (for voltage divider)
- Power supply
- Jumper wires

---

## Pin Configuration

### Servos
- Horizontal Servo → Pin 9
- Vertical Servo → Pin 10

### LDR Sensors
- Top Left (TL) → A0
- Top Right (TR) → A3
- Bottom Left (BL) → A1
- Bottom Right (BR) → A2

---

## Working Principle

1. **Sensor Acquisition**
   - Each LDR is sampled multiple times and averaged to reduce noise.

2. **Fault Handling**
   - Extremely low values are replaced with neighboring sensor values to avoid instability.

3. **Light Direction Estimation**
   - Left vs Right → Horizontal error  
   - Top vs Bottom → Vertical error  

4. **Error Normalization**
   - Errors are scaled to percentage for consistent control response.

5. **Smoothing**
   - Exponential smoothing is applied to reduce jitter and oscillations.

6. **Control Logic**
   - Servo position is adjusted proportionally based on error magnitude.
   - Movement is constrained to avoid abrupt jumps.

7. **Output**
   - Servos move incrementally to align with maximum light intensity.

---

## Control Strategy

- **Tolerance Band**: Prevents unnecessary small movements
- **Step Limiting**: Restricts servo movement per cycle
- **Position Constraints**: Ensures mechanical safety
- **Filtering**:
  - Moving average (sensor noise)
  - Exponential smoothing (control stability)

---

## Serial Output

Real-time debugging data:
TL: xxx TR: xxx BL: xxx BR: xxx | H: xxx V: xxx


---

## Applications
- Solar panel tracking systems
- Smart lighting systems
- Robotics vision approximation
- Energy optimization systems

---

## Limitations
- No feedback from servo position (open-loop actuation)
- Sensitive to ambient lighting conditions
- Requires proper calibration of LDR placement

---

## Future Improvements
- PID control instead of proportional step control
- Integration with IoT (MQTT / WiFi monitoring)
- Feedback sensors for closed-loop servo control
- Weather adaptive tracking

---
