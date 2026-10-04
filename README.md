# NTC Thermistor Driver & Monitor (Mbed OS)

[![Framework: Mbed OS](https://img.shields.io/badge/Framework-Mbed%20OS-blue.svg)](https://os.mbed.com/)
[![Platform: STM32 Nucleo](https://img.shields.io/badge/Platform-STM32%20Nucleo-002B49.svg)](https://www.st.com/)
[![Course: AME](https://img.shields.io/badge/Course-Embedded%20%26%20Mobile%20Applications-orange.svg)](https://www.urv.cat/)

A C++ software component and test application for interfacing an NTC thermistor temperature sensor using an STM32 Nucleo board and Mbed OS. Developed for the *Embedded and Mobile Applications* course (Universitat Rovira i Virgili).

---

## Overview

This project implements a reusable hardware abstraction library to sample, calculate, and report ambient temperature from an analog NTC thermistor. An accompanying Mbed OS test application demonstrates continuous sampling, analog-to-digital conversion, and temperature conversion via serial output.

### Key Specifications

| Parameter | Specification / Value |
| :--- | :--- |
| **Operating Voltage** | 3.3 V to 5 V (*3.3 V recommended*) |
| **Detectable Range** | -40 °C to +125 °C |
| **Measurement Accuracy** | ±1.5 °C |
| **Zero-Power Resistance ($R_0$)** | 100 kΩ at 25 °C ($T_0 = 298.15\text{ K}$) |
| **Balancing Resistor ($R_b$)** | 100 kΩ |
| **B-Constant ($\beta_{25/100}$)** | 4250 K to 4299 K |
| **Resistance Tolerance** | ±1% |

---

## Theory & Conversion Model

The thermistor exhibits a negative temperature coefficient (NTC)—its resistance decreases non-linearly as temperature increases.

1. **Thermistor Resistance ($R_{therm}$)**  
   Derived from the voltage divider formed by balance resistor $R_b$ (100 kΩ) and the raw ADC counts:

   $$R_{therm} = R_b \cdot \left(\frac{\mathrm{ADC}_{res}}{\mathrm{counts}} - 1\right)$$

   Where **$\mathrm{ADC}_{res}$** is $65535$ when using `read_u16()`, or $1.0$ when using normalized `read()`.

2. **Temperature in Kelvin ($T_K$)**  
   Computed using the B-parameter equation:

   $$T_K = \frac{1}{\frac{1}{\beta} \ln\left(\frac{R_{therm}}{R_0}\right) + \frac{1}{T_0}}$$

   Where **$R_0$** = $100\text{ k}\Omega$, **$T_0$** = $298.15\text{ K}$, and nominal **$\beta$** $\approx 4275\text{ K}$.

3. **Temperature in Celsius ($T_C$)**  

   $$T_C = T_K - 273.15$$


---

## Hardware Setup

* **Microcontroller:** STM32 Nucleo board
* **Expansion:** Sensor shield
* **Sensor:** 100 kΩ NTC thermistor module
* **Connections:**
  * `VCC` -> `3.3V`
  * `GND` -> `GND`
  * `SIG / OUT` -> Target Analog Input Pin (e.g., `A0`)

---

## Project Structure

```text
.
├── drivers/
│   ├── Thermistor.h          # Thermistor class interface & configuration constants
│   └── Thermistor.cpp        # ADC sampling & conversion logic
├── src/
│   └── main.cpp              # Test application & serial telemetry
├── docs/                     # Schematics and technical documentation
└── README.md
