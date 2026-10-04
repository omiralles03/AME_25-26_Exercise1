#include "Thermistor.h"
#include <cmath>

Thermistor::Thermistor(PinName pin, float beta, float rb, float r0)
    : _pin(pin), _beta(beta), _rb(rb), _r0(r0) {}

// Celcius = T_K - K
float Thermistor::read_celsius() { return read_kelvin() - _k; }

// Kelvin = 1/[(log(Rtherm/R0) / β] + 1/T0
float Thermistor::read_kelvin() {
  float r_therm = calculateResistance();

  if (r_therm <= 0.0f)
    return 0.0f;

  return 1.0f / ((std::log(r_therm / _r0) / _beta) + (1.0f / _t0));
}

// Rtherm = Rb * ([ADCres / counts] - 1)
float Thermistor::calculateResistance() {
  // ADCres = 65535 if you are using read_u16(), or 1.0 if you are using read()
  float ADCres = 1.0f;
  float counts = _pin.read();

  // Avoid log error with r_therm <= 0
  if (counts <= 0.0f || counts >= 1.0f)
    return 0.0f;

  return _rb * ((ADCres / counts) - 1.0f);
}

// Conductance (G) = 1 / Rinf
float Thermistor::calculateConductance() {
  // Rinf = R0 * e^(-β/T0) => PDF LAB
  // Valor constant so idk si es aquest o no
  const float rInf = _r0 * std::exp(-_beta / _t0);
  // return 1.0f / rInf;

  // G = 1 / Rtherm => segons Gemini
  float r_therm = calculateResistance();
  return 1.0f / r_therm;
}
