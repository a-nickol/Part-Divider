#include "part_counter.hpp"

PartCounter::PartCounter()
{
}

void PartCounter::reset()
{
  _parts = 0;
  _repition = 0;
}

PartDetection PartCounter::checkSensor(boolean lightSensor)
{
  boolean newPart = false;
  if (_lightSensor == HIGH && lightSensor == LOW)
  {
    _parts++;
    newPart = true;
    Serial.println("part");
  }
  _lightSensor = lightSensor;

  boolean changeBasin = false;
  if (_parts == _numParts)
  {
    _repition++;
    _parts = 0;
    changeBasin = true;
    Serial.println("basin");
  }

  return PartDetection{newPart, changeBasin};
}

boolean PartCounter::finished()
{
  return _repition >= _numRepitition;
}

void PartCounter::setNumParts(unsigned long numParts)
{
  _numParts = numParts;
}

void PartCounter::setNumRepitition(unsigned long numRepitition)
{
  _numRepitition = numRepitition;
}
