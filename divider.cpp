#include "divider.hpp"

DividerStepper::DividerStepper()
{
}

void DividerStepper::attach(Adafruit_StepperMotor *motor)
{
  _motor = motor;
  _motor->setSpeed(ROUNDS_PER_MINUTE);
  reset();
}

boolean DividerStepper::isPaused()
{
  return _pause;
}

void DividerStepper::reset()
{
  unsigned long ms = millis();
  _dividerStepperDirection = LEFT;
  _lastDirectionChangeOrPart = ms;
  _lastMovement = ms;
  _pauseStarted = 0;
  _pause = false;
}

void DividerStepper::setPause(boolean pause)
{
  unsigned long ms = millis();
  if (!_pause && pause)
  {
    _pauseStarted = ms;
  }
  else if (_pause && !_pause)
  {
    unsigned long dt = ms - _pauseStarted;
    _lastMovement += dt;
    _lastDirectionChangeOrPart += dt;
  }
  _pause = pause;
}

void DividerStepper::partSeen()
{
  _lastDirectionChangeOrPart = millis();
}

void DividerStepper::update()
{
  if (!_pause)
  {
    checkStepperDirection();
    driveStepper();
  }
}

void DividerStepper::checkStepperDirection()
{
  unsigned long ms = millis();
  // Turn divider if no parts are coming
  if (ms - _lastDirectionChangeOrPart > NO_PARTS_CHANGE_DIRECTION)
  {
    _lastDirectionChangeOrPart = ms;
    _dividerStepperDirection = !_dividerStepperDirection;
  }
}

void DividerStepper::driveStepper()
{
  unsigned long ms = millis();
  unsigned long dt = _lastMovement - ms;
  if (dt > MS_PER_STEPS)
  {
    _lastMovement += MS_PER_STEPS;

    if (_dividerStepperDirection == LEFT)
    {
      _motor->onestep(FORWARD, SINGLE);
    }
    else
    {
      _motor->onestep(BACKWARD, SINGLE);
    }
  }
}
