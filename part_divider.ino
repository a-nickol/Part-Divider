#include "part_counter_menu.hpp"
#include "part_counter_controller.hpp"
#include <Adafruit_MotorShield.h>

#define LIGHT_SENSOR 13

boolean waitForSerial = true;

// motor shield
Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_StepperMotor *dividerStepper = motorShield.getStepper(STEPS_STEPPER, 1);
Adafruit_StepperMotor *catchBasinStepper = motorShield.getStepper(STEPS_STEPPER, 2);

PartCounterController partCounterController = PartCounterController();

void setup()
{
  motorShield.begin();

  // Setup Serial
  Serial.begin(9600);

  if (waitForSerial)
  {
    while (!Serial)
      ;
  }

  Serial.println("Use keys + - * /");

  setNavController(&partCounterController);
  partCounterController.setup(&nav, LIGHT_SENSOR, dividerStepper, catchBasinStepper);
  partCounterController.setRunning(true);
}

boolean initController = true;
void loop()
{
  nav.poll();

  if (nav.sleepTask)
  {
    if (initController)
    {
      partCounterController.setNumParts(menu_numParts);
      partCounterController.setNumRepitition(menu_numRepitition);
      partCounterController.setNumBasins(menu_numBasins);
      partCounterController.setRunning(menu_running);
      partCounterController.resetApp();

      initController = false;
    }

    partCounterController.update();
  }
  else
  {
    initController = true;
  }
}
