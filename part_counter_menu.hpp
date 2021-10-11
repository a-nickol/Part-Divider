#pragma once

#include "part_counter_controller.hpp"
#include "Arduino.h"
#include <menu.h>
#include <menuIO/serialOut.h>
#include <menuIO/chainStream.h>
#include <menuIO/serialIn.h>

#define MAX_DEPTH 1

using namespace Menu;

PartCounterController *_controller = nullptr;

void setNavController(PartCounterController *controller)
{
     _controller = controller;
}

void runAction()
{
     _controller->runApp();
}

void resetAction()
{
     _controller->restartApp();
}

unsigned int menu_numParts = 8;
unsigned int menu_numRepitition = 2;
unsigned int menu_numBasins = 6;
boolean menu_running = false;

TOGGLE(menu_running, subMenuRunning, "Running: ", doNothing, noEvent, wrapStyle,
       VALUE("Yes", HIGH, runAction, noEvent),
       VALUE("No", LOW, runAction, noEvent));

MENU(mainMenu, "Teilezähler", Menu::doNothing, Menu::noEvent, Menu::noTitle,
     FIELD(menu_numParts, "Parts", " Stück", 1, 1000, 50, 1, Menu::doNothing, Menu::noEvent, Menu::noStyle),
     FIELD(menu_numRepitition, "Repitition", " x", 1, 100, 10, 1, Menu::doNothing, Menu::noEvent, Menu::noStyle),
     FIELD(menu_numBasins, "Catch Basins", " x", 1, 36, 1, 1, Menu::doNothing, Menu::noEvent, Menu::noStyle),
     SUBMENU(subMenuRunning),
     OP("Reset counter", resetAction, noEvent),
     EXIT("<Back"));

// Menu initialization

serialIn serial(Serial);
MENU_INPUTS(in, &serial);

MENU_OUTPUTS(out, MAX_DEPTH, SERIAL_OUT(Serial), NONE //must have 2 items at least
);

NAVROOT(nav, mainMenu, MAX_DEPTH, in, out);
