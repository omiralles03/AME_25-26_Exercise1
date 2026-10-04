# NTC Thermistor Driver & Monitor (AME 26-17 Optional exercise 1)

[![Framework: Mbed OS](https://img.shields.io/badge/Framework-Mbed%20OS-blue.svg)](https://os.mbed.com/)
[![Platform: STM32 Nucleo](https://img.shields.io/badge/Platform-STM32%20Nucleo-002B49.svg)](https://www.st.com/)
[![Course: AME](https://img.shields.io/badge/Course-Embedded%20%26%20Mobile%20Applications-orange.svg)](https://www.urv.cat/)

A C++ software component and test application for interfacing an NTC thermistor temperature sensor using an STM32 Nucleo board and Mbed OS[cite: 2, 4]. Developed for the *Embedded and Mobile Applications* course (Universitat Rovira i Virgili)[cite: 2, 4].

---

## Overview

This project implements a reusable hardware abstraction library to sample, calculate, and report ambient temperature from an analog NTC thermistor[cite: 2, 4]. An accompanying Mbed OS test application demonstrates continuous sampling, analog-to-digital conversion, and temperature conversion via serial output[cite: 2, 4].

### Key Specifications

| Parameter | Specification / Value |
| :--- | :--- |
| **Operating Voltage** | 3.3 V to 5 V (*3.3 V recommended*)[cite: 2] |
| **Detectable Range** | -40 °C to +125 °C[cite: 2] |
| **Measurement Accuracy** | ±1.5 °C[cite: 2] |
| **Zero-Power Resistance ($R_0$)** | 100 kΩ at 25 °C ($T_0 = 298.15\text{ K}$)[cite: 2, 3] |
| **Balancing Resistor ($R_b$)** | 100 kΩ[cite: 3] |
| **B-Constant ($\beta_{25/100}$)** | 4250 K to 4299 K[cite: 2, 3] |
| **Resistance Tolerance** | ±1%[cite: 2] |

---

## Theory & Conversion Model

The thermistor exhibits a negative temperature coefficient (NTC)—its resistance decreases non-linearly as temperature increases[cite: 2].

1. **Thermistor Resistance ($R_{therm}$):**  
   Derived from the voltage divider formed by balance resistor $R_b$ (100 kΩ) and the ADC raw counts[cite: 2, 3]:
   $$R_{therm} = R_b \cdot \left(\frac{\text{ADC}_{\text{res}}}{\text{counts}} - 1\right)$$
   *Where $\text{ADC}_{\text{res}} = 65535$ for `read_u16()` or $1.0$ for normalized `read()`[cite: 3].*

2. **Temperature in Kelvin ($T_K$):**  
   Computed via the B-parameter equation[cite: 2]:
   $$T_K = \frac{1}{\frac{1}{\beta} \ln\left(\frac{R_{therm}}{R_0}\right) + \frac{1}{T_0}}$$
   *Using $R_0 = 100\text{ k}\Omega$, $T_0 = 298.15\text{ K}$, and nominal $\beta \approx 4275\text{ K}$[cite: 2, 3].*

3. **Temperature in Celsius ($T_C$):**  
   $$T_C = T_K - 273.15$$
[cite: 2, 3]

---

## Hardware Setup

* **Microcontroller:** STM32 Nucleo board[cite: 4]
* **Expansion:** Sensor shield[cite: 4]
* **Sensor:** 100 kΩ NTC thermistor module[cite: 2, 4]
* **Connections:**
  * `VCC` $\rightarrow$ `3.3V`[cite: 2]
  * `GND` $\rightarrow$ `GND`
  * `SIG / OUT` $\rightarrow$ Target Analog Input Pin (e.g., `A0`)

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
