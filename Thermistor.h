#ifndef THERMISTOR_H
#define THERMISTOR_H

#include "mbed.h"

class Thermistor {
public:
  Thermistor(PinName pin, float beta = 4250.0f, float rb = 100000.0f,
             float r0 = 100000.0f);

  float read_celsius();
  float read_kelvin();
  float calculateResistance();
  float calculateConductance();

private:
  AnalogIn _pin;

  float _beta;
  float _rb;
  float _r0;
  const float _t0 = 298.15f;
  const float _k = 273.15f;
};

#endif
