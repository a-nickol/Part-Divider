#pragma once

#include "Arduino.h"
#include <Adafruit_MotorShield.h>

#define STEPS_STEPPER 200
#define MOVE_STEPS_CATCHBASIN 50
#define ROUNDS_PER_MINUTE 10
#define MS_PER_STEPS (300 / ROUNDS_PER_MINUTE)

class BasinChanger
{
public:
  void attach(Adafruit_StepperMotor *motor);
  void nextBasin();
  void setPause(boolean pause);
  void update();
  boolean isMoving();
  void setNumBasins(unsigned int basins);

private:
  Adafruit_StepperMotor *_motor;

  boolean _moving = false;
  unsigned long _basin = 0;
  unsigned long _numBasins = 0;

  unsigned int _position = 0;
  boolean _pause;
  unsigned long _lastMovement = 0;
  unsigned long _pauseStarted = 0;
};
