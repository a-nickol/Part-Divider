#pragma once

#include "Arduino.h"

struct PartDetection
{
  boolean newPart;
  boolean nextBasin;
};

class PartCounter
{
public:
  PartCounter();
  PartDetection checkSensor(boolean lightSensor);
  boolean finished();
  void reset();
  void setNumParts(unsigned long numParts);
  void setNumRepitition(unsigned long numRepitition);

private:
  boolean _lightSensor;
  unsigned long _parts = 0;
  unsigned long _numParts = 0;
  unsigned long _repition = 0;
  unsigned int _numRepitition = 0;
};
