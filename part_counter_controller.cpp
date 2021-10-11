#include "part_counter_controller.hpp"

void PartCounterController::update()
{
  if (_isRunning)
  {
    PartDetection detectedPart = _partCounter.checkSensor(_sensor.valueDebounced());
    if (detectedPart.newPart)
    {
      _stepper.partSeen();
    }
    if (detectedPart.nextBasin)
    {
      _basinChanger.nextBasin();
      _stepper.setPause(true);
    }
    boolean finished = _partCounter.finished();
    if (!finished && !_basinChanger.isMoving() && _stepper.isPaused())
    {
      _stepper.setPause(false);
    }
    _stepper.update();
    _basinChanger.update();
    if (finished && !_basinChanger.isMoving())
    {
      _nav->idleOff();
    }
  }
}

void PartCounterController::resetApp()
{
  _partCounter.reset();
  _stepper.reset();
}

void PartCounterController::restartApp()
{
  resetApp();
  if (_isRunning)
  {
    _nav->exit();
  }
}

void PartCounterController::setup(Menu::navRoot *nav, unsigned int lightSensor, Adafruit_StepperMotor *dividerStepper, Adafruit_StepperMotor *catchBasinStepper)
{
  _nav = nav;
  _sensor.attach(lightSensor);
  _stepper.attach(dividerStepper);
  _basinChanger.attach(catchBasinStepper);
}

void PartCounterController::setRunning(boolean isRunning)
{
  _isRunning = isRunning;
}

void PartCounterController::runApp()
{
  resetApp();
  _nav->exit();
}

void PartCounterController::setNumParts(unsigned int parts)
{
  _partCounter.setNumParts(parts);
}

void PartCounterController::setNumRepitition(unsigned int repitition)
{
  _partCounter.setNumRepitition(repitition);
}

void PartCounterController::setNumBasins(unsigned int basins)
{
  _basinChanger.setNumBasins(basins);
}
