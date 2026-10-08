#include "PinNameAliases.h"
#include "mbed.h"
#include "Thermistor.h"

// Specify the shield pin here (A2)
Thermistor tempSensor(A0);

int main() {
    printf("Starting Thermistor Reader...\n");

    while (true) {
        float tempC = tempSensor.read_celsius();
        float tempK = tempSensor.read_kelvin();
        float res   = tempSensor.calculateResistance();
        float cond  = tempSensor.calculateConductance();

        printf("Temp: %.2f deg C | %.2f K | Res: %.2f Ohms | Cond: %.6f S\n", 
               tempC, tempK, res, cond);

        ThisThread::sleep_for(1s);
    }
}