
#include "basin_changer.hpp"

boolean BasinChanger::isMoving()
{
  return _moving;
}

void BasinChanger::attach(Adafruit_StepperMotor *motor)
{
  _motor = motor;
  _motor->setSpeed(10);
}

void BasinChanger::setPause(boolean pause)
{
  _pause = pause;
  unsigned long ms = millis();
  if (_pause)
  {
    _pauseStarted = ms;
  }
  else
  {
    unsigned long dt = ms - _pauseStarted;
    _lastMovement += dt;
  }
}

void BasinChanger::nextBasin()
{
  _basin = (_basin + 1) % _numBasins;
  _moving = true;
}

void BasinChanger::update()
{
  unsigned long ms = millis();
  unsigned long dt = _lastMovement - ms;
  if (dt > MS_PER_STEPS)
  {
    _lastMovement += MS_PER_STEPS;

    unsigned int moveToPosition = STEPS_STEPPER * _basin / _numBasins;
    signed int dt = moveToPosition - _position;
    if (abs(dt) > STEPS_STEPPER / 2)
    {
      signed int sign = 1;
      if (dt < 0)
      {
        sign = -1;
      }
      dt = (STEPS_STEPPER - abs(dt)) * -1 * sign;
    }

    if (dt != 0)
    {
      if (dt > 0)
      {
        _motor->onestep(FORWARD, SINGLE);
        _position += 1;
      }
      else
      {
        _motor->onestep(BACKWARD, SINGLE);
        _position -= 1;
      }
    }
    else
    {
      _moving = false;
    }
  }
}

void BasinChanger::setNumBasins(unsigned int basins)
{
  _numBasins = basins;
}
