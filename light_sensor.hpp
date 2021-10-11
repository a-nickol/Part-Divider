#pragma once

#include "Arduino.h"

#define LIGHT_SENSOR_DEBOUNCE_MS 5

class LightSensor
{
public:
  LightSensor();
  void attach(unsigned int pin);
  boolean valueDebounced();

private:
  unsigned int _pin;
  boolean _lightSensorState = LOW;
  boolean _lightSensorFlicker = LOW;
  unsigned long _lightSensorLastChange = 0;
};
