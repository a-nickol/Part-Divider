#pragma once

#include "basin_changer.hpp"
#include "divider.hpp"
#include "light_sensor.hpp"
#include "part_counter.hpp"

#include "Arduino.h"
#include <menu.h>

class PartCounterController
{
public:
  void runApp();
  void resetApp();
  void restartApp();
  void stopApp();

  void setup(Menu::navRoot *nav, unsigned int lightSensor, Adafruit_StepperMotor *dividerStepper, Adafruit_StepperMotor *catchBasinStepper);
  void setRunning(boolean running);
  void update();

  void setNumParts(unsigned int parts);
  void setNumRepitition(unsigned int repitition);
  void setNumBasins(unsigned int basins);

private:
  Menu::navRoot *_nav;
  boolean _isRunning = false;
  DividerStepper _stepper = DividerStepper();
  BasinChanger _basinChanger = BasinChanger();
  LightSensor _sensor = LightSensor();
  PartCounter _partCounter = PartCounter();
};
