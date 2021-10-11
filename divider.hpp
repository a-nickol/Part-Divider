#pragma once

#include "Arduino.h"
#include <Adafruit_MotorShield.h>

#define LEFT false
#define RIGHT true
#define NO_PARTS_CHANGE_DIRECTION 3000
#define ROUNDS_PER_MINUTE 10
#define MS_PER_STEPS (300 / ROUNDS_PER_MINUTE)

class DividerStepper
{
public:
  DividerStepper();
  void attach(Adafruit_StepperMotor *motor);
  void update();
  void reset();
  void stop();
  void partSeen();
  boolean isPaused();
  void setPause(boolean pause);

private:
  void checkStepperDirection();
  void driveStepper();

  boolean _pause = true;
  Adafruit_StepperMotor *_motor;
  boolean _dividerStepperDirection = LEFT;
  unsigned long _lastDirectionChangeOrPart = 0;
  unsigned long _lastMovement = 0;
  unsigned long _pauseStarted = 0;
};
