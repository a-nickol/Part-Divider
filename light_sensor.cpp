#include "light_sensor.hpp"

LightSensor::LightSensor()
{
}

void LightSensor::attach(unsigned int pin)
{
  pinMode(pin, INPUT_PULLUP);
  _pin = pin;
}

boolean LightSensor::valueDebounced()
{
  unsigned long ms = millis();
  boolean lightSensor = !digitalRead(_pin);

  if (_lightSensorFlicker != lightSensor)
  {
    // reset the debouncing timer
    _lightSensorLastChange = ms;
    // save the the last flickerable state
    _lightSensorFlicker = lightSensor;
  }

  // Debounce sensor
  if ((ms - _lightSensorLastChange) > LIGHT_SENSOR_DEBOUNCE_MS)
  {
    _lightSensorState = lightSensor;
  }

  return _lightSensorState;
}
